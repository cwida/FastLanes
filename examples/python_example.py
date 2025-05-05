#!/usr/bin/env python3
import os

import fastlanes


def main():
    # 1) Print module docstring & version
    print(fastlanes.__doc__)
    print(f"FastLanes version: {fastlanes.get_version()}\n")

    # 2) Paths for the demo
    csv_dir = "/Users/azim/CLionProjects/FastLanes/data/generated/all_constant"  # adjust to where your CSVs live

    if os.path.exists("data.fls"):
        os.remove("data.fls")

    # 4) Use Connection as a context manager
    conn = fastlanes.connect()
    conn.read_csv(csv_dir)
    conn.inline_footer().to_fls(".")
    reader = conn.read_fls(".")
    reader.to_csv("fastlanes.csv")


if __name__ == "__main__":
    main()
