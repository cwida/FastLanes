# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/check_fastlanes_result_history.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3
"""
Script: compare_ratios_including_base.py

This script:
1. Finds all Git commits whose message starts with '[result]' (across all branches),
   ignoring file changes.
2. For each commit (in chronological order):
   - Parses {description, Y} from its message as 'description'.
   - Attempts to retrieve a CSV (fastlanes.csv) from that commit.
   - Inserts any parsed rows into DuckDB with (sequence_id, description, commit_id, table_name, file_size).
3. After insertion, identifies the earliest commit's 'description' as the 'base'.
4. Pivots the table so rows=table_name, columns=description, cells=file_size.
5. Converts *all* columns, including the base column, to ratios = (base_size / current_size).
   Thus, the base column is always 1.0, and other columns > 1.0 if they are smaller than base.

If you want the ratio = current / base, simply replace the final division logic with row[col] / row[base_desc].

Usage:
    python compare_ratios_including_base.py
"""

import os
import subprocess
import re
import csv
import numpy as np
from io import StringIO
import duckdb
from tabulate import tabulate
import pandas as pd
from colorama import init, Fore, Style

# Initialize colorama for cross-platform compatibility
init(autoreset=True)

pd.set_option('display.max_rows', None)  # Show all rows
pd.set_option('display.max_columns', None)  # Show all columns
pd.set_option('display.width', 1000)  # Adjust column width
pd.set_option('display.colheader_justify', 'center')  # Center align headers

import pandas as pd
from tabulate import tabulate
from colorama import Fore, Style


def print_df(df):
    def colorize_row(row):
        """
        Highlight all occurrences of the maximum value in bold green.
        """
        max_value = row.max()  # Find the maximum value in the row
        colored_row = []

        for value in row:
            if value == max_value:
                # Highlight all occurrences of the max value
                colored_row.append(f"{Style.BRIGHT}{Fore.GREEN}{value:.2f}{Style.RESET_ALL}")
            else:
                # Default white text for other values
                colored_row.append(f"{Fore.WHITE}{value:.2f}{Style.RESET_ALL}")
        return colored_row

    # Create a mapping of integer indices to column names
    column_map = {i + 1: col for i, col in enumerate(df.columns)}

    # Replace column names with integer indices
    df.columns = [i + 1 for i in range(len(df.columns))]

    # Apply row-wise coloring
    df_colorized = df.apply(colorize_row, axis=1)

    # Convert the DataFrame back to string-based cells
    df_colorized = pd.DataFrame(df_colorized.tolist(), columns=df.columns, index=df.index)

    # Print the reference for column names
    print("Column Reference:")
    for idx, original_name in column_map.items():
        print(f"{idx} -> {original_name}")

    # Pretty print the DataFrame using tabulate
    print("\nDataFrame:")
    print(tabulate(df_colorized, headers='keys', tablefmt='pretty'))


def find_result_commits(repo_path):
    """
    Return a list of commit hashes (newest->oldest) whose message starts with '[result]'.
    We do not filter by file changes or branches. We use:
      git log --all --pretty=format:%H --grep=^\\[result\\] --extended-regexp
    """
    cmd = [
        "git", "log",
        "--all",
        "--pretty=format:%H",
        "--grep=^\\[rr\\]",
        "--extended-regexp"
    ]
    old_cwd = os.getcwd()
    try:
        os.chdir(repo_path)
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            print(f"Error finding commits: {result.stderr}")
            return []
        commits = result.stdout.strip().split("\n")
        commits = [c for c in commits if c]  # remove empty lines
        return commits
    finally:
        os.chdir(old_cwd)


def get_commit_message(repo_path, commit_hash):
    """
    Retrieve the commit message (subject + body) using:
      git show --no-patch --pretty=format:%B <commit_hash>
    """
    cmd = ["git", "show", "--no-patch", "--pretty=format:%B", commit_hash]
    old_cwd = os.getcwd()
    try:
        os.chdir(repo_path)
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            return ""
        return result.stdout.strip()
    finally:
        os.chdir(old_cwd)


def parse_description_from_msg(msg):
    """
    Look for a pattern like {description, Y} in the commit message.
    If found, return 'Y' (stripped). Otherwise return "UNKNOWN".
    """
    pattern = r"\{description,\s*([^}]+)\}"
    match = re.search(pattern, msg)
    if match:
        return match.group(1).strip()
    return "UNKNOWN"


def get_file_content_at_commit(repo_path, commit_hash, file_path):
    """
    Use 'git show <commit>:<file_path>' to retrieve the file at that commit.
    Returns the file content as a string, or None if retrieval fails.
    """
    cmd = ["git", "show", f"{commit_hash}:{file_path}"]
    old_cwd = os.getcwd()
    try:
        os.chdir(repo_path)
        result = subprocess.run(cmd, capture_output=True, text=True)
        if result.returncode != 0:
            return None  # Means file doesn't exist in that commit
        return result.stdout
    finally:
        os.chdir(old_cwd)


def parse_csv(content):
    """
    Given CSV content as a string, parse it into a list of (table_name, FileSize).
    Assumes CSV has headers: table_name,FileSize
    """
    if not content:
        return []
    reader = csv.DictReader(StringIO(content))
    rows = []
    for row in reader:
        table_name = row.get("table_name")
        file_size_str = row.get("file_size", "0")
        try:
            file_size = int(file_size_str)
        except ValueError:
            file_size = 0
        rows.append((table_name, file_size))
    return rows


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Path to local Git repo (example: parent folder is your repo)
    repo_path = os.path.join(script_dir, "..")

    # The CSV path (relative to repo). We'll attempt to retrieve from each commit.
    file_path = os.path.join(
        "publications", "expression_encoding", "result", "compression_ratio",
        "public_bi", "fastlanes.csv"
    )

    # 1. Find all commits (newest->oldest) that start with [result]
    commits_desc = find_result_commits(repo_path)
    if not commits_desc:
        print("No commits with [result] found.")
        return

    # Reverse => oldest->newest
    commits = list(reversed(commits_desc))

    # 2. Create an in-memory DuckDB table
    con = duckdb.connect(database=':memory:')
    con.execute("""
        CREATE TABLE fastlanes (
            sequence_id  BIGINT,
            description  VARCHAR,
            commit_id    VARCHAR,
            table_name   VARCHAR,
            file_size    BIGINT
        )
    """)

    # 3. Insert data for each commit
    for i, commit_hash in enumerate(commits, start=1):
        full_msg = get_commit_message(repo_path, commit_hash)
        desc_value = parse_description_from_msg(full_msg)

        content = get_file_content_at_commit(repo_path, commit_hash, file_path)
        if content is None:
            print(f"Commit {commit_hash[:7]}: '{file_path}' not found. (No rows inserted.)")
            continue

        rows = parse_csv(content)
        if not rows:
            print(f"Commit {commit_hash[:7]}: CSV empty/invalid. (No rows inserted.)")
            continue

        insert_data = [(i, desc_value, commit_hash, t_name, f_size) for (t_name, f_size) in rows]
        con.executemany("INSERT INTO fastlanes VALUES (?, ?, ?, ?, ?)", insert_data)

    # 4. Identify earliest commit's description => base
    base_desc_sql = """
    SELECT description
    FROM fastlanes
    ORDER BY sequence_id
    LIMIT 1
    """
    result = con.execute(base_desc_sql).fetchone()
    if not result:
        print("No rows in the table. Exiting.")
        return
    base_desc = result[0]
    print(f"Base description is: {base_desc}")

    # 5. Pivot: row=table_name, col=description, cell=file_size
    pivot_sql = """
    SELECT table_name, description, file_size
    FROM fastlanes
    ORDER BY table_name, sequence_id
    """
    df = con.execute(pivot_sql).fetchdf()
    if df.empty:
        print("No data to pivot. Exiting.")
        return

    df_pivot = df.pivot(index='table_name', columns='description', values='file_size')

    # Sort columns based on sequence_id
    sequence_order_sql = """
    SELECT description
    FROM fastlanes
    GROUP BY description
    ORDER BY MIN(sequence_id)
    """
    sequence_order = con.execute(sequence_order_sql).fetchdf()['description'].tolist()

    # Reorder columns in df_pivot to match sequence order
    df_pivot = df_pivot[sequence_order]

    # 6. Convert *every* column, including base, to ratio = (base_size / col_size)
    if base_desc not in df_pivot.columns:
        print(f"Warning: base description '{base_desc}' not found in columns. No ratio conversion done.")
    else:
        def ratio_func(row):
            base_val = row[base_desc]
            out = {}
            for col in df_pivot.columns:
                val = row[col]
                if pd.isna(val) or val == 0:
                    out[col] = np.nan  # avoid / zero or / NaN
                else:
                    out[col] = base_val / val
            return pd.Series(out)

        # Apply row-wise
        df_pivot = df_pivot.apply(ratio_func, axis=1)

    # Hide all but the last 25 columns
    df_pivot = df_pivot.iloc[:, -20:]
    print_df(df_pivot)


if __name__ == "__main__":
    main()
