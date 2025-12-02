#!/usr/bin/env python3
import sys
import re
import yaml

if len(sys.argv) < 4:
    print(
        "Usage: python combo.py combos.h keymap.yaml config.yaml > combos.yaml",
        file=sys.stderr,
    )
    sys.exit(1)

c_path, yaml_path, cfg_path = sys.argv[1:4]

with open(cfg_path) as f:
    cfg = yaml.safe_load(f)

cfg = cfg.get("parse_config", {})
kc_map = cfg.get("qmk_keycode_map", {})
kc_prefixes = cfg.get("qmk_remove_keycode_prefix", [])


def resolve_kc(kc):
    kc = kc.strip()
    for p in kc_prefixes:
        if kc.startswith(p):
            kc = kc[len(p) :]
    return kc_map.get(kc, kc)


with open(yaml_path) as f:
    layers = yaml.safe_load(f).get("layers", {})

layer_keys = {
    name: {
        k if isinstance(k, str) else k.get("t")
        for row in rows
        for k in row
        if isinstance(k, str) or "t" in k
    }
    for name, rows in layers.items()
}

with open(c_path) as f:
    code = f.read()

defs = dict(
    re.findall(r"const\s+uint16_t\s+PROGMEM\s+(\w+)\[\]\s*=\s*\{([^}]+)\};", code)
)
combos = []


def add_combo(raw_keys, out_kc):
    keys = [k.strip() for k in raw_keys.split(",") if "COMBO_END" not in k]
    labels = [resolve_kc(k) for k in keys]
    result = resolve_kc(out_kc)

    found_layer = next(
        (
            lname
            for lname, keys_set in layer_keys.items()
            if all(l in keys_set or f"KC_{l}" in keys_set for l in labels)
        ),
        None,
    )

    entry = {"trigger_keys": labels, "key": result}
    if found_layer:
        entry["layers"] = [found_layer]
    else:
        print(
            f"# ⚠️  Could not detect layer: trigger={labels}, key={result}",
            file=sys.stderr,
        )

    combos.append(entry)


for match in re.findall(r"\[\s*(\w+)\s*\]\s*=\s*COMBO\(\s*(\w+),\s*(\w+)\s*\)", code):
    name, arr, out = match
    if arr in defs:
        add_combo(defs[arr], out)

for match in re.findall(r"\[\s*(\w+)\s*\]\s*=\s*COMBO_ACTION\(\s*(\w+)\s*\)", code):
    name, arr = match
    if arr in defs:
        add_combo(defs[arr], name)

print(
    yaml.dump({"combos": combos}, sort_keys=False, default_flow_style=False, indent=2)
)
