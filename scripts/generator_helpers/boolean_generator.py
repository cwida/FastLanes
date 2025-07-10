"""
Module: scripts/generate_helpers/boolean_generator.py
Description: Generates synthetic BOOLEAN data values and writes them to CSV files with accompanying schema definitions.
"""

import random
from datetime import date, timedelta
from .write_helpers import *
from .common import *
from pathlib import Path
import json


# ----------------------------------------------------------------------
# 1) Wrap generate_boolean() to match other “generate_fls_*” signatures
# ----------------------------------------------------------------------
def generate_fls_boolean(_faker, row_id):
    """Generates a list containing a single BOOLEAN value."""
    return generate_boolean(_faker, row_id)


# ----------------------------------------------------------------------
# 2) Writer for the BOOLEAN column (with schema.json)
# ----------------------------------------------------------------------
def fls_boolean():
    """
    Write a single-column CSV of BOOLEAN values (True/False).
    Creates two outputs, each with a schema.json alongside generated.csv:
      - data/generated/single_columns/fls_boolean/generated.csv   (ROW_GROUP_SIZE rows)
      - data/generated/one_vector/fls_boolean/generated.csv       (VEC_SIZE rows)
    """
    # Directory for the “rowgroup” version
    dir_rowgroup = Path.cwd() / '..' / 'data' / 'generated' / 'single_columns' / 'boolean'
    write_csv(dir_rowgroup, generate_fls_boolean, ROW_GROUP_SIZE)

    # Write schema.json in the same folder with trailing newline
    schema_rg = {
        "columns": [
            {
                "name": "SYNTHETIC_DATA_BOOLEAN",
                "type": "BOOLEAN"
            }
        ]
    }
    (dir_rowgroup / 'schema.json').write_text(json.dumps(schema_rg, indent=2) + "\n")

    # Directory for the “one_vector” (VEC_SIZE rows) version
    dir_onevec = Path.cwd() / '..' / 'data' / 'generated' / 'one_vector' / 'boolean'
    write_csv(dir_onevec, generate_fls_boolean, VEC_SIZE)

    # Write schema.json in that folder as well with trailing newline
    schema_ov = {
        "columns": [
            {
                "name": "SYNTHETIC_DATA_BOOLEAN",
                "type": "BOOLEAN"
            }
        ]
    }
    (dir_onevec / 'schema.json').write_text(json.dumps(schema_ov, indent=2) + "\n")


# ----------------------------------------------------------------------
# Core boolean generator
# ----------------------------------------------------------------------
def generate_boolean(faker, row_id):
    """
    Generates a single boolean value, returning True or False uniformly at random.
    Returned as a one-element list so it works with write_csv(...).
    """
    value = random.choice([True, False])
    return [value]
