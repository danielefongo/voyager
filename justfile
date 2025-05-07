init:
  qmk setup
  qmk config user.overlay_dir="$PWD"
  qmk config compile.keyboard=zsa/voyager
  qmk config compile.keymap=mine
  qmk generate-compilation-database -kb zsa/voyager -km mine

compile:
  qmk compile;
  qmk c2json $PWD/keyboards/zsa/voyager/keymaps/mine/keymap.c --no-cpp | keymap parse -c 10 -q - > $PWD/keyboard.yaml;

svg: compile
  keymap draw $PWD/keyboard.yaml > /tmp/keyboard.svg;
  firefox /tmp/keyboard.svg
