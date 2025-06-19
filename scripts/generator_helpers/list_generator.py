# generator_helpers/list_helper.py

"""
Helper for generating fixed lists of integers.

Exports:
  • `generate_list`    – row generator that returns a list of integers
  • `list_data`        – writer that materialises JSONL output for lists
"""

from .common import *
import random

__all__ = [
    "generate_list",
    "list_data",
]


def generate_list(_faker: Faker, row_id: int) -> list[int]:
    """
    Return a list of integers. Randomly choose between:
      - [1, 2]
      - [3]
      - [4, 5]
    """
    options: list[list[int]] = [
        [1, 2],
        [3],
        [4, 5],
    ]
    return random.choice(options)


def list_data(size: int = 1024) -> None:
    """
    Generate *size* rows of list data into `data.jsonl` under
    `../data/generated/list`, writing each row as a JSON object
    with key "numbers". Also write a schema.json file describing
    the list-of-integers structure.
    """
    faker = Faker()
    output_dir = Path.cwd() / ".." / "data" / "generated" / "list"
    output_dir.mkdir(parents=True, exist_ok=True)

    # Write data.jsonl
    file_path = output_dir / "data.jsonl"
    logger.info("Writing JSONL → %s  (%s rows)", file_path, size)
    with file_path.open("w", encoding="utf-8") as fh:
        for row_id in range(size):
            record = {"numbers": generate_list(faker, row_id)}
            fh.write(json.dumps(record) + "\n")

    # Write schema.json alongside the data
    schema = {
        "columns": [
            {
                "name": "numbers",
                "type": "list",
                "children": [
                    {"name": "child", "type": "integer"}
                ]
            }
        ]
    }
    schema_path = output_dir / "schema.json"
    logger.info("Writing schema JSON → %s", schema_path)
    with schema_path.open("w", encoding="utf-8") as sf:
        json.dump(schema, sf, indent=2)
