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

from .write_helpers import write_csv
from .common import ROW_GROUP_SIZE, VEC_SIZE


def generate_fls_i08(_faker: Any, row_id: int) -> List[int]:
    """Return a single 8-bit integer (0–127) derived from *row_id*."""
    return [row_id % 128]


def write_fls_i08_to_file(
        sub_path: str,
        generator: Callable[[Any, int], List[int]],
        size: int,
) -> None:
    """Write *size* rows to *data/generated/<sub_path>/generated.csv* plus *schema.json*."""
    # Directory where generated.csv + schema.json should live
    dir_path = Path.cwd().parent / "data" / "generated" / sub_path

    # Let write_csv create the directory and the CSV inside it
    write_csv(dir_path, generator, size)

    # Dump schema.json with a trailing newline
    schema = {
        "columns": [
            {"name": "SYNTHETIC_DATA_I08", "type": "FLS_I08"}
        ]
    }
    (dir_path / "schema.json").write_text(json.dumps(schema, indent=2) + "\n")


def fls_i08() -> None:
    """Generate both the row-group and one-vector I08 datasets."""
    write_fls_i08_to_file("single_columns/fls_i08", generate_fls_i08, ROW_GROUP_SIZE)
    write_fls_i08_to_file("one_vector/fls_i08", generate_fls_i08, VEC_SIZE)
