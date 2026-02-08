{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?rev=33d1e753c82ffc557b4a585c77de43d4c922ebb5";
  };

  outputs = { self, nixpkgs }:
    let pkgs = nixpkgs.legacyPackages.x86_64-linux;

    in {
      devShell.x86_64-linux = with pkgs; mkShell rec {
        KERNEL_PATH = "${linuxPackages.kernel.dev}";
        KERNEL_DEV_VERSION = linuxPackages.kernel.dev.version;
        CPATH = "${KERNEL_PATH}/lib/modules/${KERNEL_DEV_VERSION}/source/include";
      };
    };
}
