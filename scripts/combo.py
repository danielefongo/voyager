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


def parse_qmk_function(kc):
    kc = kc.strip()
    match = re.match(r"\w+\([^,]+,\s*(.+)\)", kc)
    if match:
        return match.group(1).strip()
    return kc


def resolve_kc_for_output(kc):
    kc = parse_qmk_function(kc)
    if kc in kc_map:
        return kc_map[kc] if kc_map[kc] else kc
    for p in kc_prefixes:
        if kc.startswith(p):
            kc_without_prefix = kc[len(p) :]
            if kc_without_prefix in kc_map:
                return (
                    kc_map[kc_without_prefix]
                    if kc_map[kc_without_prefix]
                    else kc_without_prefix
                )
            return kc_without_prefix
    return kc


def resolve_kc_simple(kc):
    full = resolve_kc_for_output(kc)
    if " " in full:
        return full.strip().split()[-1]
    return full


with open(yaml_path) as f:
    layers = yaml.safe_load(f).get("layers", {})

layer_keys_simple = {}
for name, rows in layers.items():
    keys_simple = set()
    for row in rows:
        for k in row:
            if isinstance(k, str):
                clean = k.strip().split()[-1] if k.strip() else k
                keys_simple.add(clean)
            elif isinstance(k, dict) and "t" in k:
                tap_key = k["t"]
                clean = tap_key.strip().split()[-1] if tap_key.strip() else tap_key
                keys_simple.add(clean)
    layer_keys_simple[name] = keys_simple

with open(c_path) as f:
    code = f.read()

defs = dict(
    re.findall(r"const\s+uint16_t\s+PROGMEM\s+(\w+)\[\]\s*=\s*\{([^}]+)\};", code)
)
combos = []


def split_combo_keys(raw_keys):
    keys = []
    current = ""
    paren_depth = 0

    for char in raw_keys:
        if char == "(":
            paren_depth += 1
            current += char
        elif char == ")":
            paren_depth -= 1
            current += char
        elif char == "," and paren_depth == 0:
            key = current.strip()
            if key and "COMBO_END" not in key:
                keys.append(key)
            current = ""
        else:
            current += char

    key = current.strip()
    if key and "COMBO_END" not in key:
        keys.append(key)

    return keys


def add_combo(raw_keys, out_kc):
    keys = split_combo_keys(raw_keys)
    labels_simple = [resolve_kc_simple(k) for k in keys]
    labels_full = [resolve_kc_for_output(k) for k in keys]
    result = resolve_kc_for_output(out_kc)

    found_layer = next(
        (
            lname
            for lname, keys_set in layer_keys_simple.items()
            if all(l in keys_set for l in labels_simple)
        ),
        None,
    )

    entry = {"trigger_keys": labels_full, "key": result}
    if found_layer:
        entry["layers"] = [found_layer]
    else:
        print(
            f"# ⚠️  Could not detect layer: trigger={labels_simple}, key={result}",
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
