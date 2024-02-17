{
  description = "Controller for inverted pendulum";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      mkPackage = system: deps:
        let pkgs = import nixpkgs { inherit system; };
        in pkgs.stdenv.mkDerivation rec {
          pname = "controller";
          version = "0.1.0";

          src = ./.; # or fetch the source code from somewhere

          buildInputs = deps pkgs;

          configurePhase = ''
            mkdir build
            cd build
            cmake ..
          '';

          buildPhase = ''
            make
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp myproject $out/bin/
          '';
        };

    in {
      packages.x86_64-linux = mkPackage "x86_64-linux" (pkgs: [
        pkgs.cmake
        pkgs.llvmPackages_16.llvm
        pkgs.protobuf
        pkgs.gtest
        pkgs.spdlog
        pkgs.nlohmann_json
        pkgs.gbenchmark
      ]);
      packages.aarch64-linux = mkPackage "aarch64-linux" (pkgs: [
        pkgs.cmake
        pkgs.llvmPackages_16.llvm
        pkgs.gtest
        pkgs.spdlog
        pkgs.nlohmann_json
        pkgs.gbenchmark
      ]);
    };
}