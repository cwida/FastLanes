#!/usr/bin/env python3
import csv
from collections import defaultdict

# Hard-coded path to your CSV file
CSV_PATH = "compression_summary.csv"

def compute_averages(csv_path):
    ignore = {'table_name', 'version'}
    sums = defaultdict(float)
    counts = defaultdict(int)

    with open(csv_path, newline='') as f:
        reader = csv.DictReader(f)
        numeric_fields = [fn for fn in reader.fieldnames if fn not in ignore]

        for row in reader:
            for field in numeric_fields:
                try:
                    val = float(row[field])
                except (ValueError, TypeError):
                    continue
                sums[field] += val
                counts[field] += 1

    return {f: (sums[f] / counts[f]) if counts[f] else None
            for f in numeric_fields}

def main():
    averages = compute_averages(CSV_PATH)
    print("Average values:")
    for field, avg in averages.items():
        if avg is not None:
            print(f"  {field}: {avg:.2f}")
        else:
            print(f"  {field}: no data")

if __name__ == "__main__":
    main()
