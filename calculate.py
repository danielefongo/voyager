import json
import sys
from collections import defaultdict


def percentile(values, p):
    if not values:
        return None
    values = sorted(values)
    idx = int(round(p * (len(values) - 1)))
    return values[idx]


def process_log(path):
    data = defaultdict(lambda: defaultdict(list))
    max_x = defaultdict(int)
    max_y = defaultdict(int)

    with open(path, "r") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            try:
                entry = json.loads(line)
            except json.JSONDecodeError:
                continue

            if entry.get("hold") is not False:
                continue

            layer = entry.get("layer")
            x = entry.get("x")
            y = entry.get("y")
            duration = entry.get("duration")

            if None in (layer, x, y, duration):
                continue

            data[layer][(x, y)].append(duration)
            max_x[layer] = max(max_x[layer], x)
            max_y[layer] = max(max_y[layer], y)

    global_max_x = max(max_x.values()) if max_x else 0
    global_max_y = max(max_y.values()) if max_y else 0

    P = 0.95
    for layer in sorted(data.keys()):
        print(f"\nlayer {layer}")
        for x in range(0, global_max_x + 1):
            row_vals = []
            for y in range(0, global_max_y + 1):
                durations = data[layer].get((x, y))
                if durations:
                    val = percentile(durations, P)
                    row_vals.append(f"{val:4.0f}")
                else:
                    row_vals.append("   .")
            print(f"{x:2} |" + " ".join(row_vals))


def heatmap_first_layer(path):
    data = defaultdict(lambda: defaultdict(list))
    max_x = defaultdict(int)
    max_y = defaultdict(int)

    with open(path, "r") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            try:
                entry = json.loads(line)
            except json.JSONDecodeError:
                continue

            if entry.get("hold") is not False:
                continue

            layer = entry.get("layer")
            x = entry.get("x")
            y = entry.get("y")
            duration = entry.get("duration")

            if None in (layer, x, y, duration):
                continue

            data[layer][(x, y)].append(duration)
            max_x[layer] = max(max_x[layer], x)
            max_y[layer] = max(max_y[layer], y)

    if not data:
        return

    first_layer = sorted(data.keys())[0]
    layer_data = data[first_layer]

    if not layer_data:
        return

    global_max_x = max(max_x.values()) if max_x else 0
    global_max_y = max(max_y.values()) if max_y else 0

    P = 0.95
    min_val = float("inf")
    max_val = float("-inf")

    matrix = []
    for x in range(0, global_max_x + 1):
        row = []
        for y in range(0, global_max_y + 1):
            durations = layer_data.get((x, y))
            if durations:
                val = percentile(durations, P)
                row.append(val)
                min_val = min(min_val, val)
                max_val = max(max_val, val)
            else:
                row.append(None)
        matrix.append(row)

    if min_val == float("inf"):
        return

    print(f"\nheatmap for layer {first_layer}")
    for x, row in enumerate(matrix):
        row_str = ""
        for val in row:
            if val is None:
                row_str += "  . "
            else:
                norm = (val - min_val) / (max_val - min_val) if max_val > min_val else 0
                intensity = int(norm * 9)
                row_str += f"  {intensity} "
        print(f"{x:2} |" + row_str)


if __name__ == "__main__":
    process_log(sys.argv[1])
    heatmap_first_layer(sys.argv[1])
