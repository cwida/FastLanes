#!/usr/bin/env python3
import fastlanes


def main():
    # 1) Print module docstring & version
    print(fastlanes.__doc__)
    print(f"FastLanes version: {fastlanes.get_version()}\n")

    # 2) Paths for the demo
    csv_dir = "/Users/azim/CLionProjects/FastLanes/data/generated/all_constant"  # adjust to where your CSVs live

    # 4) Use Connection as a context manager
    with fastlanes.Connection() as conn:
        # Read all CSVs in csv_dir
        conn.read_csv(csv_dir)


if __name__ == "__main__":
    main()
