# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# benchmark/result/compression_ratio/public_bi/cal_averag.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""
Report total sizes **and** the *average* compression ratio.

* Sum `csv_size` and `fls_size`   → totals
* Compute the per-row ratio       → r_i = csv_size_i / fls_size_i
* Report the **mean** of those r_i (≈ 7.5 in your file)

We never add the ratios together, because that number (≈ 398) is meaningless.
"""

import csv
from collections import defaultdict
from pathlib import Path

CSV_PATH = Path("compression_summary.csv")

def read_stats(csv_path: Path):
    sums   = defaultdict(float)   # sums for numeric size columns
    ratio_sum = 0.0               # running sum of per-row ratios
    row_count = 0

    with csv_path.open(newline="") as f:
        rdr = csv.DictReader(f)
        # columns we **do** want to treat as byte counts
        size_cols = {"csv_size", "fls_size"}

        for row in rdr:
            try:
                csv_sz = float(row["csv_size"])
                fls_sz = float(row["fls_size"])
            except (KeyError, ValueError):
                # bad or missing numbers → skip row
                continue

            # accumulate the totals
            sums["csv_size"] += csv_sz
            sums["fls_size"] += fls_sz

            # per-row compression ratio
            if fls_sz:                         # avoid div-by-zero
                ratio_sum += csv_sz / fls_sz
                row_count += 1

    return sums, ratio_sum, row_count

def main():
    sums, ratio_sum, n = read_stats(CSV_PATH)

    total_csv = sums["csv_size"]
    total_fls = sums["fls_size"]
    avg_ratio = ratio_sum / n if n else float("nan")

    print(f"Rows processed          : {n}")
    print(f"Total csv_size (bytes)  : {total_csv:,.0f}")
    print(f"Total fls_size (bytes)  : {total_fls:,.0f}")
    print(f"Average compression r   : {avg_ratio:.2f}")

if __name__ == "__main__":
    main()
