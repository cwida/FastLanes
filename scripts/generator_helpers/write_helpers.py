# ---------------------------
# Helper Functions
# ---------------------------

from .common import *
import json
import csv


def write_jsonl(dir_path, generate_func, size):
    """Writes data to a JSONL file using a generator function."""
    dir_path.mkdir(parents=True, exist_ok=True)
    file_path = dir_path / 'data.jsonl'
    logging.info(f"Writing JSONL → {file_path}  ({size} rows)")  # ← NEW
    with open(file_path, 'w') as jsonlfile:
        for row_id in range(size):
            jsonlfile.write(json.dumps(generate_func(faker, row_id)) + '\n')


def write_csv(dir_path, generate_func, size):
    """Writes data to a CSV file using a generator function."""
    dir_path.mkdir(parents=True, exist_ok=True)
    file_path = dir_path / "generated.csv"
    logging.info(f"Writing CSV  → {file_path}  ({size} rows)")  # ← NEW
    with open(file_path, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, delimiter='|', lineterminator='\n')
        writer.writerows(generate_func(faker, row_id) for row_id in range(size))
