# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/generator_helpers/timestamp_generator.py
# ────────────────────────────────────────────────────────
# scripts/generate_helpers/timestamp_generator.py

import random
from datetime import datetime, timedelta


def _random_datetime_between(start: datetime, end: datetime) -> datetime:
    """
    Return a random datetime between start and end (inclusive).
    """
    total_seconds = int((end - start).total_seconds())
    # pick a random offset in seconds
    rand_seconds = random.randint(0, total_seconds)
    # pick a random offset in microseconds within that second
    rand_microseconds = random.randint(0, 999_999)
    return start + timedelta(seconds=rand_seconds, microseconds=rand_microseconds)


def generate_timestamp(faker, row_id):
    """
    Generates a single timestamp column as an ISO-8601 string
    "YYYY-MM-DDThh:mm:ss.ffffff", picking uniformly between
    1970-01-01T00:00:00 and now.
    Returned as a one-element list so it works with write_csv(...).
    """
    # We ignore faker here, but keep it in signature for consistency.
    epoch = datetime(1970, 1, 1)
    now = datetime.now()
    rnd = _random_datetime_between(epoch, now)
    # Format with microsecond precision
    iso_ts = rnd.isoformat(sep='T', timespec='microseconds')
    return [iso_ts]
