# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# benchmark/accuracy_over_rowgroups/download_and_split.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3

import urllib.request
import bz2
import os
import shutil

DOWNLOAD_URL = "http://event.cwi.nl/da/PublicBIbenchmark/USCensus/USCensus_1.csv.bz2"
COMPRESSED_FILENAME = "USCensus_1.csv.bz2"
DECOMPRESSED_FILENAME = "USCensus_1.csv"
LINES_PER_PART = 64 * 1024  # 65,536 lines per part
SCHEMA_FILE = "schema.json"

def download_file(url, out_filename):
    print(f"Downloading {url} to {out_filename}...")
    urllib.request.urlretrieve(url, out_filename)
    print("Download complete.")

def decompress_bz2(in_filename, out_filename):
    print(f"Decompressing {in_filename} to {out_filename}...")
    with bz2.open(in_filename, "rb") as src, open(out_filename, "wb") as dst:
        for chunk in iter(lambda: src.read(4096), b""):
            dst.write(chunk)
    print("Decompression complete.")

def split_file(filename, lines_per_part):
    print(f"Splitting {filename} into rowgroups with {lines_per_part} lines each...")
    rowgroup_index = 0
    line_count = 0

    # Create first rowgroup directory and file.
    rowgroup_dir = f"rowgroup_{rowgroup_index}"
    os.makedirs(rowgroup_dir, exist_ok=True)
    # Copy schema.json into the directory.
    if os.path.exists(SCHEMA_FILE):
        shutil.copy(SCHEMA_FILE, rowgroup_dir)
    else:
        print(f"Warning: {SCHEMA_FILE} not found, skipping copy.")
    output_filename = os.path.join(rowgroup_dir, f"USCensus_1_rowgroup_{rowgroup_index}.csv")
    part_file = open(output_filename, "w")

    with open(filename, "r") as f:
        for line in f:
            if line_count >= lines_per_part:
                part_file.close()
                rowgroup_index += 1
                line_count = 0
                rowgroup_dir = f"rowgroup_{rowgroup_index}"
                os.makedirs(rowgroup_dir, exist_ok=True)
                # Copy schema.json into the new directory.
                if os.path.exists(SCHEMA_FILE):
                    shutil.copy(SCHEMA_FILE, rowgroup_dir)
                else:
                    print(f"Warning: {SCHEMA_FILE} not found, skipping copy.")
                output_filename = os.path.join(rowgroup_dir, f"USCensus_1_rowgroup_{rowgroup_index}.csv")
                part_file = open(output_filename, "w")
            part_file.write(line)
            line_count += 1

    part_file.close()
    print("Splitting complete.")

def main():
    print(os.getcwd())  # Prints the full absolute path of the current directory.
    # Only download and decompress if the decompressed file doesn't exist.
    if not os.path.exists(DECOMPRESSED_FILENAME):
        if not os.path.exists(COMPRESSED_FILENAME):
            download_file(DOWNLOAD_URL, COMPRESSED_FILENAME)
        decompress_bz2(COMPRESSED_FILENAME, DECOMPRESSED_FILENAME)
    else:
        print(f"{DECOMPRESSED_FILENAME} already exists. Skipping download and decompression.")

    # Split the decompressed CSV file into rowgroups by line count.
    split_file(DECOMPRESSED_FILENAME, LINES_PER_PART)

if __name__ == "__main__":
    main()
