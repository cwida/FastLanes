#!/usr/bin/env python3
import os

import fastlanes
import sys

sys.settrace(lambda *a, **k: None)  # forces trace hooks


def main():
    # print(dir(reader))
    # print(reader.__class__)
    # help(reader)

    # 1) Print module docstring & version
    print(fastlanes.__doc__)
    print(f"FastLanes version: {fastlanes.get_version()}\n")

    # 2) Paths for the demo
    csv_dir = "/Users/azim/CLionProjects/FastLanes/data/generated/all_constant"  # adjust to where your CSVs live

    if os.path.exists("data.fls"):
        os.remove("data.fls")
    if os.path.exists("csv.fls"):
        os.remove("decoded.csv")

    # 4) Use Connection as a context manager
    conn = fastlanes.connect()
    conn.inline_footer().read_csv(csv_dir).to_fls(".")

    reader = conn.read_fls(".")
    reader.to_csv("decoded.csv")


if __name__ == "__main__":
    main()
