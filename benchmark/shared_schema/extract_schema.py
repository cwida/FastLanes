# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# benchmark/shared_schema/extract_schema.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
import pandas as pd
import re
import sys
import os

def main():
    input_csv = "../result/compression_ratio/public_bi/fastlanes_detailed.csv"

    # Check if the file exists
    if not os.path.exists(input_csv):
        print(f"Error: File '{input_csv}' does not exist.", file=sys.stderr)
        sys.exit(1)

    # Use pandas to read the CSV file and skip lines with tokenization errors
    try:
        df = pd.read_csv(input_csv, encoding="utf-8", on_bad_lines='skip')
    except Exception as e:
        print(f"Error reading CSV: {e}", file=sys.stderr)
        sys.exit(1)

    # Filter DataFrame for rows where 'name' equals "USCensus"
    if "name" in df.columns:
        df = df[df["name"] == "USCensus"]
    else:
        print("Error: Column 'name' not found in CSV file.", file=sys.stderr)
        sys.exit(1)

    all_bracket_contents = []

    # Iterate over each row in the filtered DataFrame
    for index, row in df.iterrows():
        expression = row.get("expression", "")
        # Extract text within square brackets from the expression
        bracket_contents = re.findall(r"\[(.*?)\]", str(expression))
        all_bracket_contents.extend(bracket_contents)

    counter = 0
    # Print the aggregated results as a single C++ vector
    print("std::vector<OperatorToken> bracket_values = {")
    for content in all_bracket_contents:
        if counter % 2 != 0:
            counter += 1
            continue
        # Escape quotes and backslashes
        safe_content = content.replace("\\", "\\\\").replace("\"", "\\\"")
        print(f'    OperatorToken::{safe_content},')
        counter += 1
    print("};")

if __name__ == "__main__":
    main()
