# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/generator_helpers/common.py
# ────────────────────────────────────────────────────────
# generate_helpers/common.py

import logging
from faker import Faker
import json
from pathlib import Path
import logging

# ─────────────────────────────────────────────
# Logging setup  (INFO level to stdout)
# ─────────────────────────────────────────────
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s  %(levelname)s  %(message)s"
)

logger = logging.getLogger(__name__)

faker = Faker()

# ---------------------------
# Config
# ---------------------------

VEC_SIZE = 1024
ROW_GROUP_SIZE = 64 * VEC_SIZE
