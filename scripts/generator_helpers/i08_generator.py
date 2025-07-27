# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/generator_helpers/i08_generator.py
# ────────────────────────────────────────────────────────
"""
Module: scripts/generator_helpers/i08_generator.py
Description: Generates synthetic 8-bit integer (I08) data values and writes them to CSV files with accompanying schema definitions.
"""

from pathlib import Path
from typing import Callable, List, Any
import json

from .write_helpers import *
from .common import ROW_GROUP_SIZE, VEC_SIZE

# Figure out the project root reliably, based on this file’s location
PROJECT_ROOT = Path(__file__).resolve().parents[2]
DATA_ROOT = PROJECT_ROOT / "data" / "generated"


def generate_fls_i08(_faker: Any, row_id: int) -> List[int]:
    """Return a single 8-bit integer (0–127) derived from *row_id*."""
    return [row_id % 128]


def write_fls_i08_to_file(
        sub_path: str,
        generator: Callable[[Any, int], List[int]],
        size: int,
) -> None:
    """Write *size* rows to *data/generated/<sub_path>/generated.csv* plus *schema.json*."""
    dir_path = DATA_ROOT / sub_path

    # Make sure the directory exists before writing CSV or schema
    dir_path.mkdir(parents=True, exist_ok=True)

    # Write the CSV
    write_csv(dir_path, generator, size)

    # Dump schema.json with a trailing newline
    schema = {
        "columns": [
            {"name": "SYNTHETIC_DATA_I08", "type": "FLS_I08"}
        ]
    }
    write_schema(dir_path, schema)


def fls_i08() -> None:
    """Generate both the row-group and one-vector I08 datasets."""
    write_fls_i08_to_file("single_columns/fls_i08", generate_fls_i08, ROW_GROUP_SIZE)
    write_fls_i08_to_file("one_vector/fls_i08", generate_fls_i08, VEC_SIZE)  # generate one‑vector dataset
