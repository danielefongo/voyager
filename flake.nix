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
          default = pkgs.mkShell {
            packages = with pkgs; [
              nixpkgs-fmt
              qmk
              just
              yq-go
              python3
              python3Packages.pip
              inkscape
              hid-listen
            ];

            shellHook = ''
              set +e  
              set -o pipefail  

              FILTER_REQ="Requirement already satisfied"

              if [ ! -d .venv ]; then
                python3 -m venv .venv
              fi
              source .venv/bin/activate
              export PYTHONPATH=""

              pip install --upgrade pip | grep -v "$FILTER_REQ"
              pip install --upgrade typing_extensions pydantic pydantic-core pyparsing | grep -v "$FILTER_REQ"

              if pip list 2>/dev/null | grep -q "keymap-drawer"; then
                :
              else
                pip install keymap-drawer | grep -v "$FILTER_REQ"
              fi

              if [ -f $HOME/qmk_firmware/requirements.txt ]; then
                pip install -r $HOME/qmk_firmware/requirements.txt | grep -v "$FILTER_REQ"
              fi
            '';

          };
        }
      );
    };
}
