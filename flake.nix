{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };

        zsaQmkRev = "2f7463bddd017600910958528a2632f26bd67a70";

        zsaQmkFW = pkgs.fetchFromGitHub {
          owner = "zsa";
          repo = "qmk_firmware";
          rev = zsaQmkRev;
          sha256 = "sha256-JQ2A7UHvClZg2PhIbIxWMW8+3qWyPZpcNsCqSqkjY28=";
          fetchSubmodules = true;
        };

        patchedQmkFW =
          pkg:
          pkgs.runCommandLocal "patched_qmk_firmware" { } ''
            mkdir -p $out
            cp -r ${pkg}/* $out/

            substituteInPlace "$out/paths.mk" --replace '.build' '/tmp/.tmp_build'

            for f in $out/builddefs/common_rules.mk $out/platforms/chibios/platform.mk
            do
              substituteInPlace "$f" \
                --replace ' $(TARGET).bin' ' $(BUILD_DIR)/$(TARGET).bin.ignore' \
                --replace ' $(TARGET).$(FIRMWARE_FORMAT)' ' $(BUILD_DIR)/$(TARGET).$(FIRMWARE_FORMAT).ignore'
            done

            for f in $out/lib/python/qmk/build_targets.py $out/lib/python/qmk/compilation_database.py
            do
              substituteInPlace "$f" \
                --replace "output_path = QMK_FIRMWARE / 'compile_commands.json'" "output_path = Path('/tmp/compile_commands.json.ignore')"
            done
          '';

        qmkDeps =
          (pkgs.fetchurl {
            url = "https://raw.githubusercontent.com/zsa/qmk_firmware/${zsaQmkRev}/requirements.txt";
            sha256 = "sha256-IrXwhbUa3r4beZI7Y57nRRfTgnOoSvIOfhR0VOv1pkY=";
          })
          |> builtins.readFile
          |> pkgs.lib.splitString "\n"
          |> builtins.filter (s: s != "" && !(builtins.match "^#" s != null))
          |> builtins.map (line: builtins.head (pkgs.lib.splitString "==" line))
          |> builtins.map (name: pkgs.python3Packages.${name} or null)
          |> builtins.filter (x: x != null);

        keymapDrawer = pkgs.python3Packages.buildPythonApplication rec {
          pname = "keymap-drawer";
          version = "0.22.0";
          pyproject = true;

          src = pkgs.fetchPypi {
            inherit version;
            pname = "keymap_drawer";
            hash = "sha256-obsWbu5MEZVx1Za+2WkKCABYwmYAyAFnC2d4GZN0rVo=";
          };

          build-system = with pkgs.python3Packages; [
            poetry-core
          ];

          dependencies = with pkgs.python3Packages; [
            pydantic
            pcpp
            pyyaml
            platformdirs
            pydantic-settings
            tree-sitter
            tree-sitter-grammars.tree-sitter-devicetree
            pyparsing
          ];

          postInstall = ''
            mkdir -p $out/bin
            cat > $out/bin/keymap <<EOF
            #!${pkgs.python3}/bin/python3
            import keymap_drawer.__main__
            keymap_drawer.__main__.main()
            EOF
            chmod +x $out/bin/keymap
          '';
        };

        pythonEnv = pkgs.python3.withPackages (ps: qmkDeps ++ [ keymapDrawer ]);
      in
      {
        devShell = pkgs.mkShell {
          buildInputs = with pkgs; [
            pythonEnv
            qmk
            dos2unix
            git
            just
            zsh
            avrdude
            gcc-arm-embedded-13
            keymapDrawer
            inkscape
            yq-go
            black
            clang-tools
          ];
          env = {
            QMK_HOME = "${patchedQmkFW zsaQmkFW}";
            PATH = "${pythonEnv}/bin:$PATH";
            SKIP_GIT = "1";
          };
          shell = "${pkgs.zsh}/bin/zsh";
          shellHook = ''
            MARKER_FILE=~/.config/qmk/.voyager_qmk_home
            CURRENT_QMK_HOME="$QMK_HOME"

            if [ ! -f "$MARKER_FILE" ] || [ "$(cat "$MARKER_FILE" 2>/dev/null)" != "$CURRENT_QMK_HOME" ]; then
              qmk config user.qmk_home="$QMK_HOME" >/dev/null
              qmk config user.overlay_dir="$PWD" >/dev/null
              qmk config compile.keyboard="zsa/voyager" >/dev/null
              qmk config compile.keymap="mine" >/dev/null
              mkdir -p ~/.config/qmk
              echo "$CURRENT_QMK_HOME" > "$MARKER_FILE"
            fi
          '';
        };
      }
    );
}
