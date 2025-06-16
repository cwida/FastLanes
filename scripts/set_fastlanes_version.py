#!/usr/bin/env python3
"""
set_fastlanes_version.py TAG
────────────────────────────────────────────────────────────────────
• Creates / updates an annotated Git tag pointing at HEAD
• Finds every Cargo.toml that depends on `fls-rs` and rewrites the
  version string to the new tag (leading “v” is stripped).
"""
import argparse
import re
import subprocess
from pathlib import Path
from typing import List

def run(cmd: List[str], **kw):
    return subprocess.run(cmd, check=True, text=True, capture_output=kw.pop("capture_output", False), **kw)

def git_root() -> Path:
    out = run(["git", "rev-parse", "--show-toplevel"], capture_output=True).stdout.strip()
    return Path(out)

def find_cargo_toml(root: Path) -> List[Path]:
    files = run(["git", "-C", str(root), "ls-files"], capture_output=True).stdout.splitlines()
    return [root / f for f in files if f.endswith("Cargo.toml")]

def main():
    p = argparse.ArgumentParser()
    p.add_argument("tag", help="Tag to create (e.g. v0.1.4)")
    args = p.parse_args()

    tag     = args.tag
    version = tag.lstrip("v")
    root    = git_root()

    print(f"▶ Tagging current commit as '{tag}' …")
    # delete & recreate tag
    if subprocess.run(["git", "rev-parse", tag], capture_output=True).returncode == 0:
        run(["git", "tag", "-d", tag])
    run(["git", "tag", "-a", tag, "-m", f"FastLanes release {tag}"])

    print(f"▶ Updating Cargo.toml dependencies to '{version}' …")
    tomls   = find_cargo_toml(root)
    changed = []
    # match fls-rs = on any line
    pat     = re.compile(r'^\s*fls-rs\s*=', flags=re.MULTILINE)

    for toml in tomls:
        text = toml.read_text()
        if pat.search(text):
            new_text = re.sub(
                r'^\s*fls-rs\s*=.*$',
                f'fls-rs = "{version}"',
                text,
                flags=re.MULTILINE
            )
            if new_text != text:
                toml.write_text(new_text)
                changed.append(toml)

    if not changed:
        print("⚠️  No Cargo.toml with 'fls-rs' dependency found.")
    else:
        run(["git", "add", *map(str, changed)])
        run(["git", "commit", "-m", f"Bump fls-rs dependency to {version}"])
        for f in changed:
            print("✓", f.relative_to(root))

    print("\nAll done! Push with:\n  git push --follow-tags")

if __name__ == "__main__":
    main()
