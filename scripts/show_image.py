# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/show_image.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""show_image.py – Preview a JPEG stored in a **pipe‑delimited** CSV.

This script now aligns with the updated *jpeg_generator* output:
• CSV delimiter is a **vertical bar ("|")**.
• Base64 image lives in **column index 2** (after ``id`` and ``filename``).
• Works as PyTest test (`pytest -s show_image.py`) and as a CLI utility.

By default it loads the sample dataset generated under
``../data/generated/single_columns/jpeg/data.csv`` but you can point it to any
pipe‑delimited CSV with the same 3‑column layout.
"""

from __future__ import annotations

import argparse
import base64
import csv
import sys
from io import BytesIO
from pathlib import Path
from typing import Optional

from PIL import Image

# Allow very long base64 strings
csv.field_size_limit(sys.maxsize)

# ---------------------------------------------------------------------------
# Config / paths
# ---------------------------------------------------------------------------

DEFAULT_RELATIVE_CSV = (
        Path(__file__).resolve().parent
        / ".."
        / "data"
        / "fls"
        / "fastlanes.csv"
)


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _resolve_csv(path_str: Optional[str]) -> Path:
    """Return the absolute Path to the CSV, using default if *path_str* is None."""
    return Path(path_str).expanduser().resolve() if path_str else DEFAULT_RELATIVE_CSV


def _read_image_b64(csv_path: Path, index: int) -> str:
    """Read row *index* from *csv_path* (pipe‑delimited) and return image column."""
    if not csv_path.exists():
        raise FileNotFoundError(f"CSV not found at {csv_path}")

    with csv_path.open(encoding="utf-8", newline="") as fh:
        reader = csv.reader(fh, delimiter="|")
        for i, row in enumerate(reader):
            if i == index:
                try:
                    return row[2]  # image column
                except IndexError as exc:
                    raise ValueError(
                        f"Row {i} lacks expected 3 columns; got {row!r}"
                    ) from exc
        raise IndexError(f"CSV has only {i + 1} rows; index {index} is out of range")


def _display_image(img: Image.Image, title: str) -> None:
    """Prefer Matplotlib (if GUI backend available); fallback to OS viewer."""
    try:
        import matplotlib.pyplot as plt  # late import avoids backend issues

        plt.imshow(img)
        plt.axis("off")
        plt.title(title)
        plt.show(block=True)
    except Exception as exc:  # pragma: no cover
        print(f"Matplotlib display failed ({exc}); using PIL.Image.show()…")
        img.show(title=title)


# ---------------------------------------------------------------------------
# PyTest‑compatible test
# ---------------------------------------------------------------------------

def test_show_image_row0() -> None:  # noqa: D401 – PyTest discovery
    """Decode & display **row 0** (first image) – run with `pytest -s`."""
    b64 = _read_image_b64(DEFAULT_RELATIVE_CSV, 0)
    img = Image.open(BytesIO(base64.b64decode(b64)))

    _display_image(img, "Row 0 – JPEG preview")

    assert img.width > 0 and img.height > 0  # sanity check


# ---------------------------------------------------------------------------
# Command‑line interface
# ---------------------------------------------------------------------------

def _cli_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Preview a JPEG from a pipe‑delimited CSV")
    parser.add_argument("-i", "--index", type=int, default=0, help="Row index (0‑based)")
    parser.add_argument("--csv", type=str, default=None, help="Path to CSV file")
    return parser.parse_args()


def main(csv_path: Optional[str] = None, index: int = 0) -> None:  # noqa: D401
    path = _resolve_csv(csv_path)
    b64 = _read_image_b64(path, index)
    img = Image.open(BytesIO(base64.b64decode(b64)))
    _display_image(img, f"Row {index} – JPEG preview")


if __name__ == "__main__":
    args = _cli_args()
    main(args.csv, args.index)
