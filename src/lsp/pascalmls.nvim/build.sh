#!/usr/bin/env bash
# Obtain the `pascalmls` language server binary for this plugin.
# Run automatically by the Neovim plugin's lazy.nvim `build` step.
#
# Primary path: download a prebuilt binary from the GitHub Release (no toolchain
# needed). Fallback: if the download fails and the Rust source is present
# alongside the plugin (in-repo checkout), build it from source.
set -euo pipefail

REPO="omurilo/pascalm" # GitHub repo that publishes the release assets

here="$(cd "$(dirname "$0")" && pwd)"
bindir="$here/bin"
mkdir -p "$bindir"

# Map the host to the release asset / Rust target triple.
os="$(uname -s)"
arch="$(uname -m)"
case "$os/$arch" in
  Darwin/arm64) target="aarch64-apple-darwin" ;;
  Darwin/x86_64) target="x86_64-apple-darwin" ;;
  Linux/x86_64) target="x86_64-unknown-linux-gnu" ;;
  Linux/aarch64) target="aarch64-unknown-linux-gnu" ;;
  *) echo "unsupported platform: $os/$arch" >&2; target="" ;;
esac

download() {
  [ -n "$target" ] || return 1
  local asset="pascalmls-$target"
  local url="https://github.com/$REPO/releases/latest/download/$asset"
  echo "downloading $asset from latest release…"
  curl -fsSL "$url" -o "$bindir/pascalmls.new"
}

build_from_source() {
  local crate="$here/.." # ../ == the pascalmls crate (src/lsp) in an in-repo checkout
  [ -f "$crate/Cargo.toml" ] || return 1
  echo "release download failed; building from source…"
  if [ -z "${LLVM_SYS_180_PREFIX:-}" ]; then
    if command -v brew >/dev/null 2>&1 && brew --prefix llvm@18 >/dev/null 2>&1; then
      export LLVM_SYS_180_PREFIX="$(brew --prefix llvm@18)"
    elif [ -d /usr/lib/llvm-18 ]; then
      export LLVM_SYS_180_PREFIX=/usr/lib/llvm-18
    else
      echo "error: LLVM 18 not found (needed to build from source)." >&2
      return 1
    fi
  fi
  if command -v brew >/dev/null 2>&1 && brew --prefix zstd >/dev/null 2>&1; then
    export RUSTFLAGS="${RUSTFLAGS:-} -L $(brew --prefix zstd)/lib"
  fi
  cargo build --release --manifest-path "$crate/Cargo.toml"
  cp "$crate/target/release/pascalmls" "$bindir/pascalmls.new"
}

if download || build_from_source; then
  chmod +x "$bindir/pascalmls.new"
  # Atomic replace: overwriting an mmap'd binary can yield "Killed: 9" on macOS.
  mv -f "$bindir/pascalmls.new" "$bindir/pascalmls"
  echo "installed: $bindir/pascalmls"
else
  echo "error: could not obtain pascalmls (no release asset and no buildable source)." >&2
  exit 1
fi
