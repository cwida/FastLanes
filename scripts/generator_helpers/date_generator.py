# scripts/generate_helpers/date_generator.py

import random
from datetime import date, timedelta


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
