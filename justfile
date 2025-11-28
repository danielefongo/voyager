init:
  qmk setup
  qmk config user.overlay_dir="$PWD"
  qmk config compile.keyboard=zsa/voyager
  qmk config compile.keymap=mine
  pip install -r $HOME/qmk_firmware/requirements.txt

compile:
  qmk compile -j 0;
  qmk c2json $PWD/keyboards/zsa/voyager/keymaps/mine/keymap.c --no-cpp | keymap -c ./misc/config.yaml parse -c 10 -q - > /tmp/keyboard.yaml;
  keymap draw /tmp/keyboard.yaml > /tmp/keyboard.svg;
  inkscape /tmp/keyboard.svg --export-type=png --export-filename=$PWD/misc/keyboard.png --export-dpi=300

flash: compile
  qmk flash -kb zsa/voyager -km mine;

show: compile
  firefox $PWD/misc/keyboard.png
