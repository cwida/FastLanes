# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/generator_helpers/byte_array_generator.py
# ────────────────────────────────────────────────────────
"""
Helper for generating fixed byte arrays.

Exports:
• `generate_bytes`   – row generator that returns a random byte array
• `byte_array_data`  – writer that materialises CSV output for byte arrays
"""

from .common import *
import base64
import random
import csv

__all__ = [
    "generate_bytes",
    "byte_array_data",
]


def generate_bytes(_faker: Faker, row_id: int) -> str:
    """
    Return a base64-encoded random byte array, simulating binary data.
    Randomly choose between byte arrays of length 4, 8, or 16.
    """
    length = random.choice([4, 8, 16])
    data = bytes(random.getrandbits(8) for _ in range(length))
    return base64.b64encode(data).decode("ascii")


def byte_array_data(size: int = 1024) -> None:
    """
    Generate *size* rows of byte array data into `data.csv` under
    `../data/generated/byte_array`, writing each row as a base64-encoded string
    in a CSV file with no header and line terminator \\n.
    """
    faker = Faker()
    output_dir = Path.cwd() / "data" / "generated" / "single_columns" / "byte_array"
    output_dir.mkdir(parents=True, exist_ok=True)

    # Write data.csv
    file_path = output_dir / "data.csv"
    logger.info("Writing CSV → %s  (%s rows)", file_path, size)
    with file_path.open("w", encoding="utf-8", newline="") as fh:
        writer = csv.writer(fh, lineterminator="\n")
        for row_id in range(size):
            writer.writerow([generate_bytes(faker, row_id)])

    # Write schema.json alongside the data
    schema = {
        "columns": [
            {
                "name": "blob",
                "type": "byte_array",
                "logical_type": "base64"
            }
        ]
    }
    schema_path = output_dir / "schema.json"
    logger.info("Writing schema JSON → %s", schema_path)
    with schema_path.open("w", encoding="utf-8") as sf:
        json.dump(schema, sf, indent=2)
