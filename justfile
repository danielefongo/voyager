compile:
  qmk compile -j 0
  just image-gen

compile-db:
  qmk compile -j 0 --compiledb
  just image-gen

flash: compile
  qmk flash -kb zsa/voyager -km mine;

show: compile
  firefox $PWD/misc/keyboard.png

image-gen:
  qmk c2json $PWD/keyboards/zsa/voyager/keymaps/mine/keymap.c --no-cpp | keymap -c ./misc/config.yaml parse -c 10 -q - > /tmp/keymap.yaml
  python3 ./scripts/combo.py keyboards/zsa/voyager/keymaps/mine/combos.h /tmp/keymap.yaml ./misc/config.yaml > /tmp/combos.yaml
  yq eval-all 'select(fileIndex == 0) * select(fileIndex == 1)' /tmp/keymap.yaml /tmp/combos.yaml > /tmp/keyboard.yaml
  keymap draw /tmp/keyboard.yaml > /tmp/keyboard.svg
  inkscape /tmp/keyboard.svg --export-type=png --export-filename=$PWD/misc/keyboard.png --export-dpi=300
