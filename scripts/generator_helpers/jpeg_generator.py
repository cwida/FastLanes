# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/generator_helpers/jpeg_generator.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""
jpeg_generator.py – Dump Daisy JPEGs to a **pipe‑delimited** CSV with metadata
and **JetBrains‑style “natural” filename ordering**.

CLion (and other JetBrains IDEs) display files using a case‑insensitive natural
sort: numeric parts are compared by value, so ``image2.jpg`` precedes
``image10.jpg``.  This version mirrors that order when writing `data.csv` so
rows line up with what you see in the Project tool‑window.

CSV columns (pipe‑delimited)
---------------------------
1. ``id``       – 0‑based integer index (row number)
2. ``filename`` – original file name
3. ``image``    – base64‑encoded JPEG bytes

The accompanying `schema.json` is unchanged.
"""

from __future__ import annotations

import base64
import csv
import json
import logging
import re
from pathlib import Path
from typing import List, Tuple

from faker import Faker  # retained for API symmetry across generators
from .common import *  # shared logger / utilities

__all__ = [
    "generate_row",
    "jpeg_data",
]

logger = logging.getLogger(__name__)


# ---------------------------------------------------------------------------
# Internal helpers
# ---------------------------------------------------------------------------


def _natural_key(path: Path):
    """Return a list key implementing JetBrains ‘natural’ filename ordering."""
    name = path.name.lower()  # case‑insensitive like JetBrains
    return [int(part) if part.isdigit() else part for part in re.split(r"(\d+)", name)]


# --- Path resolution fix ----------------------------------------------------
# Resolve repo_root as two levels up from this file (…/scripts/generator_helpers
# → …/scripts → **repo root**).  This is stable regardless of CWD.
repo_root: Path = Path(__file__).resolve().parents[2]


def _collect_jpeg_paths() -> List[Path]:
    """Collect *.jpg / *.jpeg files and sort them with natural ordering."""
    root = repo_root / "data" / "flower_photos" / "daisy"

    paths = list(root.glob("*.jpg")) + list(root.glob("*.jpeg"))
    if not paths:
        raise FileNotFoundError(f"No JPEG files found under {root.resolve()}")
    return sorted(paths, key=_natural_key)


_JPEG_PATHS: List[Path] = _collect_jpeg_paths()  # cache


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------


def generate_row(_faker: Faker, row_id: int) -> Tuple[int, str, str]:  # noqa: D401
    """Return ``(id, filename, base64_string)`` cycling through images."""
    if not _JPEG_PATHS:
        raise RuntimeError("JPEG cache is empty – cannot generate rows.")

    path = _JPEG_PATHS[row_id % len(_JPEG_PATHS)]
    with path.open("rb") as fh:
        encoded = base64.b64encode(fh.read()).decode("ascii")
    return row_id, path.name, encoded


def jpeg_data() -> None:
    """Materialise the pipe‑delimited CSV + schema under the generated folder."""
    out_dir = repo_root / "data" / "generated" / "single_columns" / "jpeg"
    out_dir.mkdir(parents=True, exist_ok=True)

    csv_path = out_dir / "data.csv"
    logger.info("Writing pipe‑delimited CSV → %s  (%d rows)", csv_path, len(_JPEG_PATHS))
    with csv_path.open("w", encoding="utf-8", newline="") as fh:
        writer = csv.writer(fh, delimiter="|", lineterminator="\n")
        for row_id in range(len(_JPEG_PATHS)):
            writer.writerow(generate_row(Faker(), row_id))

    schema = {
        "columns": [
            {"name": "id", "type": "int"},
            {"name": "filename", "type": "string"},
            {
                "name": "image",
                "type": "jpeg",
                "logical_type": "base64",
                "content_type": "image/jpeg",
            },
        ]
    }
    schema_path = out_dir / "schema.json"
    logger.info("Writing schema JSON → %s", schema_path)
    with schema_path.open("w", encoding="utf-8") as sf:
        json.dump(schema, sf, indent=2)


if __name__ == "__main__":
    jpeg_data()
