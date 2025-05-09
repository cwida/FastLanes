#!/usr/bin/env python3
import sys
import os
import subprocess

# # point this at your built sdist
# sdist_path = os.path.join(os.path.dirname(__file__), "../dist", "pyfastlanes-0.1.3.tar.gz")
#
# # install it into the current venv
# subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade", sdist_path])
#
# # now you can import and use it:
import pyfastlanes


def main():
    # print(dir(reader))
    # print(reader.__class__)
    # help(reader)

    # 1) Print module docstring & version
    print(pyfastlanes.__doc__)
    print(f"FastLanes version: {pyfastlanes.get_version()}\n")

    # 2) Paths for the demo
    csv_dir = "/Users/azim/CLionProjects/FastLanes/data/generated/all_constant"  # adjust to where your CSVs live

    if os.path.exists("data.fls"):
        os.remove("data.fls")
    if os.path.exists("csv.fls"):
        os.remove("decoded.csv")

    # 4) Use Connection as a context manager
    conn = pyfastlanes.connect()
    conn.inline_footer().read_csv(csv_dir).to_fls(".")

    reader = conn.read_fls(".")
    reader.to_csv("decoded.csv")


if __name__ == "__main__":
    main()
