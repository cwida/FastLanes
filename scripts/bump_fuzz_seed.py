#!/usr/bin/env python3
"""
Bump the `base_seed` in test/src/quick_fuzz_tests/fuzz_config.json by +1.

Usage:
    python scripts/bump_fuzz_seed.py
"""
from __future__ import annotations
import json
from pathlib import Path
import sys
import tempfile

CFG = Path("test/src/quick_fuzz_tests/fuzz_config.json")
DEFAULT_SEED = 42

def main() -> None:
    if not CFG.exists():
        print(f"⚠️  {CFG} not found; creating with base_seed={DEFAULT_SEED}")
        CFG.parent.mkdir(parents=True, exist_ok=True)
        data = {"base_seed": DEFAULT_SEED}
    else:
        data = json.loads(CFG.read_text())

    old = data.get("base_seed", DEFAULT_SEED)
    new = old + 1
    data["base_seed"] = new

    with tempfile.NamedTemporaryFile("w", delete=False) as tmp:
        json.dump(data, tmp, indent=2)
        tmp.write("\n")
    Path(tmp.name).replace(CFG)

    print(f"✅  base_seed bumped: {old} → {new}")

if __name__ == "__main__":
    sys.exit(main())
