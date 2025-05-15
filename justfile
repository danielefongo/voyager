init:
  qmk setup
  qmk config user.overlay_dir="$PWD"
  qmk config compile.keyboard=zsa/voyager
  qmk config compile.keymap=mine
  qmk generate-compilation-database -kb zsa/voyager -km mine

compile:
  qmk compile;
  qmk c2json $PWD/keyboards/zsa/voyager/keymaps/mine/keymap.c --no-cpp | keymap -c ./misc/config.yaml parse -c 10 -q - > /tmp/keyboard.yaml;
  keymap draw /tmp/keyboard.yaml > $PWD/misc/keyboard.svg;

flash:
  qmk flash -kb zsa/voyager -km mine;

show-svg: compile
  firefox $PWD/misc/keyboard.svg
