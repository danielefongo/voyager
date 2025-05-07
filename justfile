init:
  qmk setup
  qmk config user.overlay_dir="$PWD"
  qmk config compile.keyboard=zsa/voyager
  qmk config compile.keymap=mine
  qmk generate-compilation-database -kb zsa/voyager -km mine
  qmk compile
