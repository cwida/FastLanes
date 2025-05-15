#!/usr/bin/env python3
import sys
import os
import subprocess
import pyfastlanes


def main():
    # 1) Print module docstring & version
    print(pyfastlanes.__doc__)
    print(f"FastLanes version: {pyfastlanes.get_version()}\n")

    # 2) Paths for the demo
    csv_dir = "../data/generated/issues/issue_000"  # adjust to where your CSVs live

    if os.path.exists("data.fls"):
        os.remove("data.fls")
    if os.path.exists("csv.fls"):
        os.remove("decoded.csv")

    # 4) Use Connection as a context manager
    conn = pyfastlanes.connect()
    conn.inline_footer().read_csv(csv_dir).to_fls("data.fls")

    reader = conn.read_fls("data.fls")
    reader.to_csv("decoded.csv")


if __name__ == "__main__":
    main()
