#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"

qmk setup
qmk config user.overlay_dir="$SCRIPT_DIR"
qmk config compile.keyboard=zsa/voyager
qmk config compile.keymap=mine
qmk generate-compilation-database -kb zsa/voyager -km mine
