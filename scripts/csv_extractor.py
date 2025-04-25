import pandas as pd
import json
from public_bi import *

ALL = "ALL"
CURRENT_ISSUE = "issue_001"


def extract_columns_and_vectors(input_file_path, column_indices, vector_indices=ALL, output_file_path="extracted.csv",
                                schema_output_path="extracted_schema.json", table_name=None):
    """
    Extract specified columns and vectors from a CSV file and save them to an output file.
    Also extracts and saves the corresponding schema.
    """
    # Read CSV data
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
    elif isinstance(column_indices, tuple):
        selected_columns = data_frame.iloc[:, column_indices[0]:column_indices[1]]
    elif isinstance(column_indices, list):
        selected_columns = data_frame.iloc[:, column_indices]
    else:
        raise ValueError("Invalid column_indices. Use 'ALL', a tuple (start, end), or a list of indices.")

    # Select vectors (rows)
    if vector_indices == ALL:
        extracted_data = selected_columns
    elif isinstance(vector_indices, tuple):
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

    # Extract and save schema
    if table_name:
        extract_and_save_schema(column_indices, schema_output_path, table_name)


def extract_and_save_schema(column_indices, schema_output_path, table_name):
    """
    Extract schema for the selected columns and save it as a JSON file.
    """
    schema_path = PublicBI.get_schema_file_path(table_name)  # Correct schema file path retrieval

    try:
        with open(schema_path, "r", encoding="utf-8") as f:
            schema = json.load(f)
    except FileNotFoundError:
        print(f"Error: Schema file not found at {schema_path}")
        return

    # Filter only selected columns
    column_details = {
        col["index"]: {
            "name": table_name + "_" + col["name"],
            "type": col["type"],
            "nullability": col["nullability"],
            "index": col["index"],

        }
        for col in schema["columns"]
    }

    if column_indices == ALL:
        selected_schema = schema["columns"]
    else:
        selected_schema = [col for idx, col in column_details.items() if idx in column_indices]

    # Save extracted schema
    with open(schema_output_path, "w", encoding="utf-8") as f:
        json.dump({"columns": selected_schema}, f, indent=4)


if __name__ == "__main__":
    table_name = nyc  # Update table name as needed
    input_file_path = PublicBI.get_file_path(table_name)
    schema_file_path = PublicBI.get_schema_file_path(table_name)

    column_indices = [25, 27, 28]  # Select the required columns
    vector_indices = ALL  # Extract all vectors (rows)

    output_file_path = "../data/generated/issues/{0}/extracted.csv".format(CURRENT_ISSUE)
    schema_output_path = "../data/generated/issues/{0}/schema.json".format(CURRENT_ISSUE)

    extract_columns_and_vectors(input_file_path, column_indices, vector_indices, output_file_path, schema_output_path,
                                table_name)
