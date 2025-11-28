{
  inputs = {
    flake-schemas.url = "https://flakehub.com/f/DeterminateSystems/flake-schemas/*";
    nixpkgs.url = "https://flakehub.com/f/NixOS/nixpkgs/*";
  };
  outputs =
    {
      self,
      flake-schemas,
      nixpkgs,
    }:
    let
      supportedSystems = [ "x86_64-linux" ];
      forEachSupportedSystem =
        f:
        nixpkgs.lib.genAttrs supportedSystems (
          system:
          f {
            pkgs = import nixpkgs { inherit system; };
          }
        );
    in
    {
      schemas = flake-schemas.schemas;
      devShells = forEachSupportedSystem (
        { pkgs }:
        {
          default = pkgs.mkShell rec {
            allowUnfree = true;
            packages = with pkgs; [
              nixpkgs-fmt
              qmk
              just
              python3
              python3Packages.pip
              bear
              clang-tools
              inkscape
              gcc
              gnumake
            ];
            shellHook = ''
              unset LD_LIBRARY_PATH
              export GLIBC_LOCALE_ARCHIVE=${pkgs.glibcLocales}/lib/locale/locale-archive
              if [ ! -d .venv ]; then
                python3 -m venv .venv
              fi
              source .venv/bin/activate

              if ! pip list | grep -q "keymap-drawer"; then
                pip install keymap-drawer
              fi

              if [ -f $HOME/qmk_firmware/requirements.txt ]; then
                pip install -r $HOME/qmk_firmware/requirements.txt
              fi

              echo "QMK environment ready!"
            '';
          };
        }
      );
    };
}
