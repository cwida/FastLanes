# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/generator_helpers/u08_generator.py
# ────────────────────────────────────────────────────────
"""
Module: scripts/generator_helpers/u08_generator.py
Description: Generates synthetic **unsigned** 8-bit integer (U08) data values and writes them to CSV files with accompanying schema definitions.
"""

from pathlib import Path
from typing import Callable, List, Any
import json

from .write_helpers import write_csv
from .common import ROW_GROUP_SIZE, VEC_SIZE


# ----------------------------------------------------------------------
# Row-value generator
# ----------------------------------------------------------------------

def generate_fls_u08(_faker: Any, row_id: int) -> List[int]:
    """Return a single **unsigned** 8-bit integer (0–255) derived from *row_id*."""
    return [row_id % 256]


# ----------------------------------------------------------------------
# CSV + schema writer helper
# ----------------------------------------------------------------------

def write_fls_u08_to_file(
        sub_path: str,
        generator: Callable[[Any, int], List[int]],
        size: int,
) -> None:
    """Write *size* rows to *data/generated/<sub_path>/generated.csv* plus *schema.json*."""
    # Target directory where generated.csv and schema.json will reside
    dir_path = Path.cwd().parent / "data" / "generated" / sub_path

    # Let *write_csv* create the directory and CSV
    write_csv(dir_path, generator, size)

    # Emit schema.json (with trailing newline for POSIX friendliness)
    schema = {
        "columns": [
            {
                "name": "SYNTHETIC_DATA_U08",
                "type": "UTINYINT"
            }
        ]
    }
    (dir_path / "schema.json").write_text(json.dumps(schema, indent=2) + "\n")


# ----------------------------------------------------------------------
# Public entry point used by scripts/generate_synthetic_data.py
# ----------------------------------------------------------------------

def fls_u08() -> None:
    """Generate the row-group (ROW_GROUP_SIZE) and one-vector (VEC_SIZE) U08 datasets."""
    write_fls_u08_to_file("single_columns/fls_u08", generate_fls_u08, ROW_GROUP_SIZE)
    write_fls_u08_to_file("one_vector/fls_u08", generate_fls_u08, VEC_SIZE)
