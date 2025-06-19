# scripts/generate_helpers/date_generator.py

import random
from datetime import date, timedelta
from .write_helpers import *
from .common import *
from pathlib import Path
import json


# ----------------------------------------------------------------------
# 1) Wrap generate_date() to match other “generate_fls_*” signatures
# ----------------------------------------------------------------------
def generate_fls_date(_faker, row_id):
    """Generates a list containing a single DATE value as 'YYYY-MM-DD'."""
    return generate_date(_faker, row_id)


# ----------------------------------------------------------------------
# 2) Writer for the DATE column (with schema.json)
# ----------------------------------------------------------------------
def fls_date():
    """
    Write a single-column CSV of DATE values ("YYYY-MM-DD").
    Creates two outputs, each with a schema.json alongside generated.csv:
      - data/generated/single_columns/fls_date/generated.csv   (ROW_GROUP_SIZE rows)
      - data/generated/one_vector/fls_date/generated.csv       (VEC_SIZE rows)
    """
    # Directory for the “rowgroup” version
    dir_rowgroup = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'fls_date'
    write_csv(dir_rowgroup, generate_fls_date, ROW_GROUP_SIZE)

    # Write schema.json in the same folder with trailing newline
    schema_rg = {
        "columns": [
            {
                "name": "SYNTHETIC_DATA_DATE",
                "type": "DATE"
            }
        ]
    }
    (dir_rowgroup / 'schema.json').write_text(json.dumps(schema_rg, indent=2) + "\n")

    # Directory for the “one_vector” (VEC_SIZE rows) version
    dir_onevec = Path.cwd() / '..' / 'data' / 'generated' / 'one_vector' / 'fls_date'
    write_csv(dir_onevec, generate_fls_date, VEC_SIZE)

    # Write schema.json in that folder as well with trailing newline
    schema_ov = {
        "columns": [
            {
                "name": "SYNTHETIC_DATA_DATE",
                "type": "DATE"
            }
        ]
    }
    (dir_onevec / 'schema.json').write_text(json.dumps(schema_ov, indent=2) + "\n")


def _random_date_between(start: date, end: date) -> date:
    """
    Return a random date between start and end (inclusive).
    """
    delta_days = (end - start).days
    offset = random.randint(0, delta_days)
    return start + timedelta(days=offset)


def generate_date(faker, row_id):
    """
    Generates a single-date column as an ISO-8601 string "YYYY-MM-DD",
    picking uniformly between 1970-01-01 and today.
    Returned as a one-element list so it works with write_csv(...).
    """
    # We ignore faker here, but keep it in signature for consistency.
    start = date(1970, 1, 1)
    today = date.today()
    rnd = _random_date_between(start, today)
    return [rnd.isoformat()]
