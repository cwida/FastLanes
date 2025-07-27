# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/analyze_schema.py
# ────────────────────────────────────────────────────────
import json
from collections import Counter
from dataset_lib.public_bi import PublicBI

def normalize_type(column_type):
    """Normalize column types: group all VARCHAR-like and DECIMAL-like types."""
    column_type = column_type.lower()
    if "char" in column_type or "text" in column_type or "varchar" in column_type:
        return "varchar"
    if "decimal" in column_type or "numeric" in column_type:
        return "decimal"
    return column_type

def analyze_schema(schema_path):
    """Analyze a schema file and count the number of columns per normalized type."""
    with open(schema_path, "r", encoding="utf-8") as f:
        schema = json.load(f)

    column_types = [normalize_type(col["type"]) for col in schema["columns"]]

    return Counter(column_types)

def analyze_all_schemas():
    """Iterate through all tables in PublicBI and compute an overall column type count."""
    overall_counts = Counter()

    for table in PublicBI.table_list:
        schema_path = PublicBI.get_schema_file_path(table)
        type_counts = analyze_schema(schema_path)
        overall_counts.update(type_counts)

    # Print overall summary across all schemas
    print("\nOverall Column Type Counts Across All Tables in PublicBI:")
    for col_type, count in overall_counts.items():
        print(f"{col_type}: {count}")

if __name__ == "__main__":
    analyze_all_schemas()
