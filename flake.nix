{
  description = "Minesweeper with AI, as it seems to be all the buzz nowadays";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
      };
    in {
      devShells.default = pkgs.mkShell {
        name = "minesweeper-devshell";
        nativeBuildInputs = [ pkgs.gnumake ];
        buildInputs = with pkgs; [
          gcc
          gdb
          glfw-wayland
          pkg-config
          wayland
        ];
      };
    });
}
