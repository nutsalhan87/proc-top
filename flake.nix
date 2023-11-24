{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?rev=970a59bd19eff3752ce552935687100c46e820a5";
  };

  outputs = { self, nixpkgs }:
    let pkgs = nixpkgs.legacyPackages.x86_64-linux;

    in {
      devShell.x86_64-linux = with pkgs; mkShell {
        KERNEL_PATH = "${linuxPackages.kernel.dev}";
      };
    };
}
