#!/usr/bin/env bash
# scripts/publish-crate.sh
set -euo pipefail

################################################################################
# helper: reproducibly archive the minimal C++ tree to a tmp file and echo its
# path. (`gzip -9n` strips mtime and filename → deterministic)
################################################################################
make_tarball() {
  local tmp
  tmp="$(mktemp)"
  git -C "$REPO_ROOT" archive --format=tar \
      HEAD CMakeLists.txt include src alp primitives |
      gzip -9n > "$tmp"
  echo "$tmp"
}

################################################################################
# locate repo root, then work from there
################################################################################
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && git rev-parse --show-toplevel)"
cd "$REPO_ROOT"

echo "── Step 1: package & commit fresh tarball ────────────────────────────"
new_tar="$(make_tarball)"

if ! cmp -s "$new_tar" rust/fastlanes-src.tar.gz 2>/dev/null; then
  mv "$new_tar" rust/fastlanes-src.tar.gz
  git add rust/fastlanes-src.tar.gz
  git commit -m "embed FastLanes sources for crates.io"
  echo "✔ tarball updated & committed"
else
  rm "$new_tar"
  echo "✔ tarball already up-to-date – nothing to commit"
fi

echo
echo "── Step 2: build & dry-run publish ───────────────────────────────────"
#  If you *really* want to keep using the Makefile, uncomment the next two
#  lines and set SKIP_PACKAGE=1 in your Makefile to bypass packaging.
#   make -e SKIP_PACKAGE=1 build-rust
#   make -e SKIP_PACKAGE=1 dry-run-rust

cargo build   --manifest-path rust/Cargo.toml --release
cargo publish --manifest-path rust/Cargo.toml --dry-run --allow-dirty

echo
echo "── Step 3: publish for real 🎉 ───────────────────────────────────────"
cargo publish --manifest-path rust/Cargo.toml --allow-dirty

echo
echo "✅  Crate published – all done!"
