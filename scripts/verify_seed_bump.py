# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/verify_seed_bump.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""
CI helper: ensure the PR's base_seed is exactly +1 over dev's base_seed.

If the config is absent on dev, the check is skipped (passes).
"""

from __future__ import annotations
import json
import subprocess
import sys
from pathlib import Path

CFG_PATH = "test/src/quick_fuzz_tests/fuzz_config.json"
DEFAULT_SEED = 42

def read_seed_from_string(s: str) -> int:
    try:
        return json.loads(s or "{}").get("base_seed", DEFAULT_SEED)
    except json.JSONDecodeError:
        return DEFAULT_SEED

def main() -> None:
    cfg = Path(CFG_PATH)
    if not cfg.exists():
        print("ℹ️  No fuzz_config.json in this PR – skipping seed-bump check.")
        return

    pr_seed = read_seed_from_string(cfg.read_text())

    # Try to fetch the file from origin/dev
    try:
        dev_file = subprocess.check_output(
            ["git", "show", f"origin/dev:{CFG_PATH}"],
            stderr=subprocess.DEVNULL,
            text=True,
        )
        dev_seed = read_seed_from_string(dev_file)
    except subprocess.CalledProcessError:
        print("ℹ️  No fuzz_config.json on dev branch – skipping seed-bump check.")
        return

    expected = dev_seed + 1
    if pr_seed != expected:
        print(
            f"::error title=Seed bump required::'base_seed' should be {expected} "
            f"(found {pr_seed}).\n"
            f"Please run `make bump` and commit."
        )
        sys.exit(1)

    print(f"✔️  base_seed correctly bumped ({dev_seed} → {pr_seed})")

if __name__ == "__main__":
    main()
