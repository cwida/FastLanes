# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/generator_helpers/struct_generator.py
# ────────────────────────────────────────────────────────
"""
generator_helpers/struct_helper.py

Helper for STRUCT type data extracted from
`scripts/generate_helpers/main_generators.py`.

Exports:
  • `generate_struct` – row generator for a STRUCT with five int64 fields
  • `struct`          – writer that materialises JSONL output as before
"""

from .common import *

from faker import Faker

__all__ = [
    "generate_struct",
    "struct",
]

logger = logging.getLogger(__name__)


def generate_struct(_faker: Faker, row_id: int) -> dict:
    """
    Return a single row containing one STRUCT column, ``COLUMN_0``.

    The STRUCT has five fields, each offset by 1e9 from *row_id*.
    """
    return {
        "COLUMN_0": {
            "FIELD_0": row_id + 0,
            "FIELD_1": row_id + 1_000_000_000,
            "FIELD_2": row_id + 2_000_000_000,
            "FIELD_3": row_id + 3_000_000_000,
            "FIELD_4": row_id + 4_000_000_000,
        }
    }


def struct(size: int = 1024) -> None:
    """
    Generate *size* rows of STRUCT data into `data.jsonl` under
    `../data/generated/struct`, mimicking the original `struct()`.
    """
    faker = Faker()
    output_dir = Path.cwd() / "data" / "generated" / "struct"
    output_dir.mkdir(parents=True, exist_ok=True)
    file_path = output_dir / "data.jsonl"
    logger.info("Writing JSONL → %s  (%s rows)", file_path, size)

    with file_path.open("w", encoding="utf-8") as fh:
        for row_id in range(size):
            fh.write(json.dumps(generate_struct(faker, row_id)) + "\n")
