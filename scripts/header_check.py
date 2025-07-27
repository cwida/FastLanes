# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/header_check.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""Add or verify minimal FastLanes headers in source files,
optionally wrapping generated files in NOLINT markers for clang‑tidy,
and optionally print the recommended GitHub Actions workflow YAML.
"""

from __future__ import annotations

import argparse
import subprocess
from pathlib import Path
from fnmatch import fnmatch
import sys

#######################################################################
# Utility helpers
#######################################################################

def git_root() -> Path:
    """Return the absolute path to the git repository root."""
    out = subprocess.check_output(["git", "rev-parse", "--show-toplevel"], text=True)
    return Path(out.strip())


def list_source_files(root: Path) -> list[Path]:
    """Enumerate version‑controlled source files that need headers."""
    patterns = [
        "*.hpp", "*.h", "*.cpp", "*.cuh", "*.cu",  # C/C++/CUDA
        "Makefile", "*.mk",                             # Make
        "*.py",                                          # Python
        "CMakeLists.txt", "*.cmake",                    # CMake
        "*.yml", "*.yaml"                               # YAML
    ]

    files = subprocess.check_output(["git", "ls-files"], cwd=root, text=True)
    out: list[Path] = []
    for f in files.splitlines():
        if any(fnmatch(f, p) for p in patterns):
            out.append(root / f)
    return out


def choose_prefix(path: Path) -> str:
    """Return the line‑comment delimiter appropriate for *path*."""
    name = path.name
    suffix = path.suffix

    if name == "Makefile" or suffix in {".mk", ".py", ".yml", ".yaml"}:
        return "#"
    if name == "CMakeLists.txt" or suffix == ".cmake":
        return "#"  # treat CMake as shell style
    # default to C/C++/CUDA single‑line comment
    return "//"


def is_generated(path: Path) -> bool:
    """Heuristic: consider a file *generated* if its name contains 'generated'."""
    return "generated" in path.name.lower()


#######################################################################
# Header generation helpers
#######################################################################

def generate_header(path: Path, root: Path, include_nolint: bool = False) -> str:
    """Return the FastLanes header for *path*.

    If *include_nolint* is true, a `NOLINTBEGIN` marker is appended so that
    the body of the generated file is skipped by clang‑tidy.
    """
    prefix = choose_prefix(path)
    width = 54
    bar = f"{prefix} {'─' * (width + 2)}"
    title = f"{prefix} |{'FastLanes'.center(width)}|"
    relpath = path.relative_to(root).as_posix()

    lines: list[str] = [
        bar,
        title,
        bar,
        f"{prefix} {relpath}",
        bar,
        "",
    ]

    if include_nolint:
        lines.append(f"{prefix} NOLINTBEGIN")
        lines.append("")

    return "\n".join(lines)


def strip_existing_header(text: str, expected_header: str) -> str:
    """Remove our *expected_header* from the beginning of *text* if present."""
    if text.startswith(expected_header):
        return text[len(expected_header) :]
    return text


def strip_trailing_nolint_end(text: str, nolint_end_line: str) -> str:
    """Remove a trailing `NOLINTEND` line if it matches *nolint_end_line*."""
    if text.rstrip().endswith(nolint_end_line.rstrip()):
        # We need to locate the last occurrence safely — splitlines() is fine
        lines = text.splitlines(keepends=True)
        while lines and lines[-1].strip() == "":
            lines.pop()
        if lines and lines[-1].startswith(nolint_end_line.strip()):
            lines.pop()
        return "".join(lines)
    return text

#######################################################################
# Core processing logic
#######################################################################

def process_file(path: Path, root: Path, check: bool) -> bool:
    """Ensure *path* starts with a FastLanes header (and NOLINT markers if needed).

    If *check* is true, only validation is performed and *False* is returned
    when the file does not comply. Otherwise the file is rewritten in‑place
    to satisfy the rules.
    """
    generated = is_generated(path)
    expected_header = generate_header(path, root, include_nolint=generated)
    nolint_end_line = f"{choose_prefix(path)} NOLINTEND\n" if generated else ""

    text = path.read_text()

    # Validation path --------------------------------------------------
    if check:
        header_ok = text.startswith(expected_header)
        nolint_ok = (not generated) or text.rstrip().endswith(nolint_end_line.rstrip())
        return header_ok and nolint_ok

    # Rewrite path -----------------------------------------------------
    body = strip_existing_header(text, expected_header)
    if generated:
        body = strip_trailing_nolint_end(body, nolint_end_line)

    # Ensure body ends with a single newline before NOLINTEND (if any)
    body = body.lstrip("\n")  # avoid accidental leading blank lines
    if body and not body.endswith("\n"):
        body += "\n"

    new_text = expected_header + body
    if generated:
        new_text += nolint_end_line

    path.write_text(new_text)
    return True

#######################################################################
# GitHub Actions workflow helper
#######################################################################

def print_github_action_yml() -> None:
    """Print an opinionated GitHub Actions workflow for header checking."""
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

#######################################################################
# Entry point
#######################################################################

def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true", help="only check headers")
    parser.add_argument(
        "--github-action-yml",
        action="store_true",
        help="print GitHub Actions workflow YAML and exit",
    )
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
