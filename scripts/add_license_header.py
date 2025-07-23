# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/add_license_header.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""Add or verify license headers in source files.

This script prepends a license header to various source files or verifies
that the header is present. The repository root is detected via Git and
the license text is read from the repository's LICENSE file.
"""

from __future__ import annotations

import argparse
import subprocess
from pathlib import Path
from fnmatch import fnmatch
import sys


def git_root() -> Path:
    out = subprocess.check_output(["git", "rev-parse", "--show-toplevel"], text=True)
    return Path(out.strip())


def list_source_files(root: Path) -> list[Path]:
    patterns = ["*.hpp", "*.cpp", "*.cuh", "*.cu", "Makefile", "*.mk"]
    files = subprocess.check_output(["git", "ls-files"], cwd=root, text=True)
    out: list[Path] = []
    for f in files.splitlines():
        if any(fnmatch(f, p) for p in patterns):
            out.append(root / f)
    return out


def generate_header(path: Path, root: Path, license_lines: list[str]) -> str:
    if path.name == "Makefile" or path.suffix == ".mk":
        prefix = "#"
    else:
        prefix = "//"

    lines = [f"{prefix} {path.relative_to(root).as_posix()}", prefix]
    for line in license_lines:
        if line:
            lines.append(f"{prefix} {line}")
        else:
            lines.append(prefix)
    return "\n".join(lines) + "\n\n"


def strip_existing_header(text: str, prefix: str) -> str:
    lines = text.splitlines()
    idx = 0
    while idx < len(lines) and lines[idx].startswith(prefix):
        idx += 1
    if idx < len(lines) and lines[idx].strip() == "":
        idx += 1
    return "\n".join(lines[idx:]) + ("\n" if text.endswith("\n") else "")


def process_file(path: Path, root: Path, license_lines: list[str], check: bool) -> bool:
    expected = generate_header(path, root, license_lines)
    text = path.read_text()
    if text.startswith(expected):
        return True

    if check:
        return False

    prefix = "#" if path.name == "Makefile" or path.suffix == ".mk" else "//"
    body = strip_existing_header(text, prefix)
    path.write_text(expected + body)
    return True


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true", help="only check headers")
    args = parser.parse_args()

    root = git_root()
    license_lines = (root / "LICENSE").read_text().splitlines()
    files = list_source_files(root)

    ok = True
    for f in files:
        if not process_file(f, root, license_lines, args.check):
            print(f"Missing or incorrect header: {f}")
            ok = False

    if args.check and not ok:
        sys.exit(1)


if __name__ == "__main__":
    main()
