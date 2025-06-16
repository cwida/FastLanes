import os
import pandas as pd
import json
from pathlib import Path
from public_bi import *

# ANSI color codes for terminal output
green = "\033[92m"
reset = "\033[0m"
prefix = "-- fls : csv_extractor:"

ALL = "ALL"
CURRENT_ISSUE = "issue_001"
DATASET = "NextiaJD"


def extract_columns_and_vectors(input_file_path,
                                schema_file_path,
                                column_indices,
                                vector_indices=ALL,
                                output_file_path="extracted.csv",
                                schema_output_path="extracted_schema.json"):
    """
    Extract specified columns and vectors from a CSV file and save them to an output file.
    Also extracts and saves the corresponding schema.
    """
    # Read CSV data
    print(f"{green}{prefix} Reading CSV data from {input_file_path}{reset}")
    data_frame = pd.read_csv(
        input_file_path,
        sep="|",
        quotechar='"',
        header=None,
        on_bad_lines="skip",
        low_memory=False
    )

    # Select columns
    if column_indices == ALL:
        selected_columns = data_frame
    elif isinstance(column_indices, tuple):  # (start, end)
        selected_columns = data_frame.iloc[:, column_indices[0]:column_indices[1]]
    elif isinstance(column_indices, list):
        selected_columns = data_frame.iloc[:, column_indices]
    else:
        raise ValueError("Invalid column_indices. Use 'ALL', a tuple (start, end), or a list of indices.")

    # Select vectors (rows)
    if vector_indices == ALL:
        extracted_data = selected_columns
    elif isinstance(vector_indices, tuple):  # (start_block, end_block)
        start_row = vector_indices[0] * 1024
        end_row = vector_indices[1] * 1024
        extracted_data = selected_columns.iloc[start_row:end_row]
    elif isinstance(vector_indices, list):
        extracted_data = pd.DataFrame()
        for vector_index in vector_indices:
            start_row = vector_index * 1024
            end_row = (vector_index + 1) * 1024
            extracted_data = pd.concat([extracted_data, selected_columns.iloc[start_row:end_row]])
    else:
        raise ValueError("Invalid vector_indices. Use 'ALL', a tuple (start, end), or a list of indices.")

    # Save extracted data
    extracted_data.to_csv(output_file_path, index=False, sep="|", quotechar='"', header=False, na_rep="NULL")
    print(f"{green}{prefix} Wrote extracted data to {output_file_path}{reset}")

    # Extract and save schema
    extract_and_save_schema(schema_file_path, column_indices, schema_output_path)


def extract_and_save_schema(schema_file_path, column_indices, schema_output_path):
    """
    Extract schema for the selected columns (by position) and save it as a JSON file.
    """
    # Load the full schema
    print(f"{green}{prefix} Loading schema from {schema_file_path}{reset}")
    try:
        with open(schema_file_path, "r", encoding="utf-8") as f:
            schema = json.load(f)
    except FileNotFoundError:
        print(f"Error: Schema file not found at {schema_file_path}")
        return

    all_cols = schema.get("columns", [])
    selected_schema = []

    # If user wants all columns, include them all (and add index)
    if column_indices == ALL:
        for idx, col in enumerate(all_cols):
            col_with_idx = {**col, "index": idx}
            selected_schema.append(col_with_idx)
    else:
        for idx, col in enumerate(all_cols):
            if (isinstance(column_indices, tuple) and column_indices[0] <= idx < column_indices[1]) \
                    or (isinstance(column_indices, list) and idx in column_indices):
                col_with_idx = {**col, "index": idx}
                selected_schema.append(col_with_idx)

    # Write out the pruned schema
    with open(schema_output_path, "w", encoding="utf-8") as f:
        json.dump({"columns": selected_schema}, f, indent=4)
    print(f"{green}{prefix} Wrote pruned schema to {schema_output_path}{reset}")


if __name__ == "__main__":
    # Base directory is always script's parent
    base_dir = Path(__file__).resolve().parent

    # FastLanes data directory from environment (if set)
    fastlanes_dir = os.getenv("FASTLANES_DATA_DIR")

    # Determine root for dataset: prefer FASTLANES_DATA_DIR if present, else base_dir
    if fastlanes_dir:
        data_root = Path(fastlanes_dir)
    else:
        data_root = base_dir

    # Dataset directory under data_root
    dataset_dir = data_root / DATASET

    # Relative input paths
    input_file_path = dataset_dir / "tables" / "yellow_tripdata_2019_01" / "yellow_tripdata_2019_01.csv"
    schema_file_path = dataset_dir / "tables" / "yellow_tripdata_2019_01" / "schema.json"

    # Parameters
    column_indices = ALL
    vector_indices = ALL

    # Prepare output directory under base_dir
    output_dir = base_dir /".." /"data" / "generated" / "issues" / CURRENT_ISSUE
    output_dir.mkdir(parents=True, exist_ok=True)
    print(f"{green}{prefix} Prepared output directory at {output_dir}{reset}")

    # Relative output paths
    output_file_path = output_dir / "extracted.csv"
    schema_output_path = output_dir / "schema.json"

    # Run extraction
    extract_columns_and_vectors(
        str(input_file_path),
        str(schema_file_path),
        column_indices,
        vector_indices,
        str(output_file_path),
        str(schema_output_path)
    )
