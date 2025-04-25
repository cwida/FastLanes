#!/usr/bin/env python3
import sys

def filter_and_print(csv_file):
    try:
        with open(csv_file, 'r', encoding='utf-8') as file:
            for line in file:
                if 'EXP_ALP_DBL' in line:
                    columns = line.strip().split(',')
                    if len(columns) >= 3:  # Ensure there are enough columns
                        print(f"{columns[2]}, {columns[3]}, {columns[4]}")  # Adjust index based on actual CSV format
    except Exception as e:
        print(f"Error reading file: {e}")
        sys.exit(1)

# Example usage
if __name__ == "__main__":
    csv_file = "fastlanes_detailed.csv"
    filter_and_print(csv_file)
