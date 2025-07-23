# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/analyze_datasets.py
# ────────────────────────────────────────────────────────
import pandas as pd
import json
from public_bi import *


# Function to load schema from JSON
def load_schema(schema_path):
    with open(schema_path, "r", encoding="utf-8") as f:
        schema = json.load(f)

    # Extract column names, types, and indexes
    column_details = {
        col["index"]: {"name": col["name"], "type": col["type"], "nullability": col["nullability"]}
        for col in schema["columns"]
    }

    # Sort by index to ensure correct column order
    sorted_columns = [column_details[idx]["name"] for idx in sorted(column_details.keys())]

    return column_details, sorted_columns


# Function to read CSV using schema
def read_csv_with_schema(csv_file, schema_path):
    column_details, sorted_columns = load_schema(schema_path)

    # Read the CSV file using schema-defined column names and order
    df = pd.read_csv(
        csv_file,
        sep="|",
        quotechar='"',
        header=None,  # No header in the CSV, will use schema-defined headers
        names=sorted_columns,  # Apply schema-defined column names
        on_bad_lines="skip",
        low_memory=False
    )

    # Convert column types based on schema
    for idx, col_info in column_details.items():
        col_name = col_info["name"]
        col_type = col_info["type"].lower()

        if "int" in col_type:
            df[col_name] = pd.to_numeric(df[col_name], errors="coerce").astype("Int64")  # Nullable int
        elif "float" in col_type or "double" in col_type:
            df[col_name] = pd.to_numeric(df[col_name], errors="coerce")
        elif "bool" in col_type:
            df[col_name] = df[col_name].astype("boolean")
        elif "char" in col_type or "text" in col_type or "varchar" in col_type:
            df[col_name] = df[col_name].astype(str)

    return df


# Function to analyze columns based on selected options
def analyze_columns(csv_file, schema_path, **options):
    df = read_csv_with_schema(csv_file, schema_path)

    # Results storage
    constant_columns_index = []
    equal_columns_groups = []
    equaled_columns = []
    one_to_one_pairs = []
    string_to_integer_columns = []
    shared_dictionary_groups = []
    castable_doubles = []

    # Safe range for exact integer representation in double
    SAFE_DOUBLE_INT_MIN = -9007199254740992  # -2^53
    SAFE_DOUBLE_INT_MAX = 9007199254740992  # 2^53

    # Find constant columns
    if options.get("find_constant", False):
        for idx, col in enumerate(df.columns):
            if df[col].nunique() <= 1:
                constant_columns_index.append(idx)

    # Find equal columns
    if options.get("find_equal", False):
        checked_columns = set()
        for i, col1 in enumerate(df.columns):
            if i in checked_columns:
                continue
            equal_group = [i]
            for j in range(i + 1, len(df.columns)):
                if df[col1].equals(df[df.columns[j]]):
                    equal_group.append(j)
                    checked_columns.add(j)
                    equaled_columns.append(j)
            if len(equal_group) > 1:
                equal_columns_groups.append(equal_group)

    # Check for one-to-one mapped columns
    if options.get("find_one_to_one", False):
        for i, col1 in enumerate(df.columns):
            if i in constant_columns_index or i in equaled_columns:
                continue
            for j in range(i + 1, len(df.columns)):
                if j in constant_columns_index or j in equaled_columns:
                    continue
                col2 = df.columns[j]
                group = df[[col1, col2]].drop_duplicates()
                if len(group) == len(df[col1].unique()) == len(df[col2].unique()):
                    one_to_one_pairs.append((i, j))

    # Find string columns that can be cast to integers
    if options.get("find_int_columns", False):
        for idx, col in enumerate(df.columns):
            if df[col].apply(lambda x: isinstance(x, str) and x.isdigit()).all():
                string_to_integer_columns.append(idx)

    # Find shared dictionary columns
    if options.get("find_shared_dictionary", False):
        column_domains = {
            col: frozenset(df[col].dropna().unique())
            for idx, col in enumerate(df.columns)
            if
            idx not in constant_columns_index and idx not in set([c for group in equal_columns_groups for c in group])
        }
        seen_domains = {}
        for idx, col in enumerate(df.columns):
            if idx in constant_columns_index or idx in set([c for group in equal_columns_groups for c in group]):
                continue
            domain = column_domains[col]
            if domain not in seen_domains:
                seen_domains[domain] = [idx]
            else:
                seen_domains[domain].append(idx)
        shared_dictionary_groups = [group for group in seen_domains.values() if len(group) > 1]

    # Find castable doubles
    if options.get("find_castable_doubles", False):
        for idx, col in enumerate(df.columns):
            if pd.api.types.is_numeric_dtype(df[col]) and df[col].dtype in ["float64", "float32"]:
                all_integers = df[col].dropna().apply(lambda x: x % 1 == 0).all()
                all_in_safe_range = df[col].dropna().between(SAFE_DOUBLE_INT_MIN, SAFE_DOUBLE_INT_MAX).all()

                if all_integers and all_in_safe_range:
                    castable_doubles.append(idx)

    return (
        constant_columns_index,
        equal_columns_groups,
        equaled_columns,
        one_to_one_pairs,
        string_to_integer_columns,
        shared_dictionary_groups,
        castable_doubles
    )


# Function to perform checks
def check(csv_path, schema_path, selected_checks):
    options = {check: (check in selected_checks) for check in selected_checks}

    results = analyze_columns(csv_path, schema_path, **options)

    (
        constant_cols_index,
        equal_columns_groups,
        equaled_columns,
        one_to_one_pairs,
        string_to_integer_columns,
        shared_dictionary_groups,
        castable_doubles
    ) = results

    if "find_constant" in selected_checks:
        print(f"-- Constant columns: {constant_cols_index}")
    if "find_equal" in selected_checks:
        print(f"-- Equal column groups: {equal_columns_groups}")
        print(f"-- Equaled columns (second elements only): {equaled_columns}")
    if "find_one_to_one" in selected_checks:
        print(f"-- One-to-one mapped column pairs: {one_to_one_pairs}")
    if "find_int_columns" in selected_checks:
        print(f"-- String-to-integer columns: {string_to_integer_columns}")
    if "find_shared_dictionary" in selected_checks:
        print(f"-- Shared dictionary columns: {shared_dictionary_groups}")
    if "find_castable_doubles" in selected_checks:
        print(f"-- castable_doubles: {castable_doubles}")


# Function to check a single table file
def check_file(table_file_path, schema_file_path):
    checks = [
        "find_constant",
        "find_shared_dictionary",
        "find_equal",
        "find_one_to_one",
        "find_int_columns",
    ]

    print(f"-- {table_file_path}")
    check(table_file_path, schema_file_path, checks)


# Function to process all tables in public BI
def public_bi():
    checks = [
        "find_castable_doubles",
    ]

    for table in PublicBI.table_list:
        print(f"-- {table}")
        check(PublicBI.get_file_path(table), PublicBI.get_schema_file_path(table), checks)


# Entry point of the script
if __name__ == "__main__":
    public_bi()

    # # Update with actual paths
    # your_csv_path = "/Users/azim/CLionProjects/temp/publications/expression_encoding/scripts/extracted_columns_subarrays.csv"
    # your_schema_path = "/Users/azim/CLionProjects/temp/publications/expression_encoding/scripts/schema.json"
    #
    # check_file(your_csv_path, your_schema_path)
