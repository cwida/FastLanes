# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/header_check.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""Add or verify minimal FastLanes headers in source files,
and optionally print the recommended GitHub Actions workflow YAML.
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
    patterns = [
        "*.hpp", "*.cpp", "*.cuh", "*.cu",
        "Makefile", "*.mk",
        "*.py",
        "CMakeLists.txt", "*.cmake",
        "*.yml", "*.yaml"
    ]
    files = subprocess.check_output(["git", "ls-files"], cwd=root, text=True)
    out: list[Path] = []
    for f in files.splitlines():
        if any(fnmatch(f, p) for p in patterns):
            out.append(root / f)
    return out


def choose_prefix(path: Path) -> str:
    name = path.name
    suffix = path.suffix
    if (
            name == "Makefile"
            or suffix == ".mk"
            or suffix == ".py"
            or name == "CMakeLists.txt"
            or suffix == ".cmake"
            or suffix == ".yml"
            or suffix == ".yaml"
    ):
        return "#"
    return "//"


def generate_header(path: Path, root: Path) -> str:
    prefix = choose_prefix(path)
    width = 54
    bar = f"{prefix} {'─' * (width + 2)}"
    title = f"{prefix} |{'FastLanes'.center(width)}|"
    relpath = path.relative_to(root).as_posix()
    lines = [
        bar,
        title,
        bar,
        f"{prefix} {relpath}",
        bar,
        ""
    ]
    return "\n".join(lines)


def strip_existing_header(text: str, expected_header: str) -> str:
    """
    If the file already starts with *exactly* our auto‑generated header,
    strip it; otherwise leave everything intact.
    """
    if text.startswith(expected_header):
        return text[len(expected_header):]
    return text


def process_file(path: Path, root: Path, check: bool) -> bool:
    expected = generate_header(path, root)
    text = path.read_text()
    if text.startswith(expected):
        return True

    if check:
        return False

    # strip only an existing FastLanes header, leave all other comments
    body = strip_existing_header(text, expected)
    path.write_text(expected + body)
    return True


def print_github_action_yml():
    yml = """\
name: FastLanes Header Check

on:
  pull_request:
  push:
    branches: [ main, master, dev ]

jobs:
  check-header:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - name: Set up Python
        uses: actions/setup-python@v5
        with:
          python-version: '3.x'

      - name: Set up virtual environment
        run: python -m venv .venv

      - name: Check FastLanes file headers
        run: .venv/bin/python scripts/header_check.py --check
"""
    print(yml)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true", help="only check headers")
    parser.add_argument("--github-action-yml", action="store_true",
                        help="print GitHub Actions workflow YAML and exit")
    args = parser.parse_args()

    if args.github_action_yml:
        print_github_action_yml()
        return

    root = git_root()
    files = list_source_files(root)

    ok = True
    for f in files:
        if not process_file(f, root, args.check):
            print(f"Missing or incorrect header: {f}")
            ok = False

    if args.check and not ok:
        sys.exit(1)


if __name__ == "__main__":
    main()
