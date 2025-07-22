"""
Module: scripts/generate_helpers/galp_generator.py
Description: For three fields—one random two‑decimal GALP, one constant 1.00,
             and one POSITIVE_INF—writes each as its own single‑column CSV +
             schema.json, in both ROW_GROUP_SIZE and VEC_SIZE variants,
             and for both FLOAT and DOUBLE schema types.
"""

import random
from decimal import Decimal, ROUND_HALF_UP
from pathlib import Path
import json

from .write_helpers import write_csv
from .common import ROW_GROUP_SIZE, VEC_SIZE


def _gen_galp(_faker, row_id):
    """Random number in [0.0,100.0], two decimals."""
    raw = random.uniform(0.0, 100.0)
    return [
        float(
            Decimal(str(raw))
            .quantize(Decimal("0.01"), rounding=ROUND_HALF_UP)
        )
    ]


def _gen_constant(_faker, row_id):
    """Constant = 1.00."""
    return [1.00]


def _gen_inf(_faker, row_id):
    """Constant = +infinity."""
    return [float("inf")]


def fls_galp():
    """
    For each of three fields—GALP, CONSTANT, POSITIVE_INF—and for each precision
    (FLOAT vs DOUBLE), write:

      data/generated/galp/<precision>/<field>/single_column/generated.csv   (ROW_GROUP_SIZE rows)
      data/generated/galp/<precision>/<field>/single_column/schema.json

      data/generated/galp/<precision>/<field>/one_vector/generated.csv     (VEC_SIZE rows)
      data/generated/galp/<precision>/<field>/one_vector/schema.json
    """
    base_dir = Path.cwd() / "../data" / "generated" / "galp"

    # the three fields we want to generate
    tasks = [
        ("galp", "SYNTHETIC_DATA_GALP", _gen_galp),
        ("constant", "SYNTHETIC_DATA_CONSTANT", _gen_constant),
        ("positive_inf", "SYNTHETIC_DATA_POSITIVE_INF", _gen_inf),
    ]

    # emit both FLOAT and DOUBLE versions
    precisions = [
        ("float", "FLOAT"),
        ("double", "DOUBLE"),
    ]

    for prec_key, prec_type in precisions:
        for field_key, column_name, gen_fn in tasks:
            # 1) Row‑group (single_column)
            dir_rg = base_dir / prec_key / field_key / "single_column"
            write_csv(dir_rg, gen_fn, ROW_GROUP_SIZE)
            schema = {"columns": [{"name": column_name, "type": prec_type}]}
            (dir_rg / "schema.json").write_text(json.dumps(schema, indent=2) + "\n")

            # 2) One‑vector version
            dir_ov = base_dir / prec_key / field_key / "one_vector"
            write_csv(dir_ov, gen_fn, VEC_SIZE)
            (dir_ov / "schema.json").write_text(json.dumps(schema, indent=2) + "\n")
