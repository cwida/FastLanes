#!/usr/bin/env python3
import csv
import sys
import os

######################################
# 1. Helpers to read & parse CSV rows
######################################

def extract_domain_data(csv_file_path):
    """
    Reads a CSV file that has columns (among others):
      name, data_type, bits_per_value, size(bytes)
    plus any others.

    Returns a list of tuples:
      (
        domain,        # HPC, TS, OBS, DB, or UNKNOWN
        name,          # Possibly with HPC_TS_OBS_ or DB_ prefix removed
        data_type,     # Exactly 'FLOAT' or 'DOUBLE'
        bits,          # from bits_per_value
        size_val       # from size(bytes)
      )

    The domain is assigned by row index:
      - first 10 rows => HPC
      - next 8 rows  => TS
      - next 8 rows  => OBS
      - next 7 rows  => DB
      - remaining    => UNKNOWN

    If 'name' starts with 'HPC_TS_OBS_' or 'DB_', we remove that prefix.
    """
    rows = []
    with open(csv_file_path, mode='r', newline='') as file:
        reader = csv.DictReader(file)
        for index, row in enumerate(reader):
            try:
                raw_name = row['name']
                data_type = row['data_type'].strip().upper()  # e.g. "FLOAT" or "DOUBLE"
                bits = float(row['bits_per_value'])
                size_val = float(row['size(bytes)'])

                # Only accept rows that have data_type in ("FLOAT", "DOUBLE")
                if data_type not in ("FLOAT", "DOUBLE"):
                    continue

                # Assign domain by row index
                if index < 10:
                    domain = "HPC"
                elif index < 18:
                    domain = "TS"
                elif index < 26:
                    domain = "OBS"
                elif index < 33:
                    domain = "DB"
                else:
                    domain = "UNKNOWN"

                # Remove known prefixes from the name
                for prefix in ["HPC_TS_OBS_", "DB_"]:
                    if raw_name.startswith(prefix):
                        raw_name = raw_name[len(prefix):]
                        break

                rows.append((domain, raw_name, data_type, bits, size_val))
            except (ValueError, KeyError):
                # Skip rows missing required columns or with invalid values
                continue
    return rows

########################################
# 2. Merge logic for domain-based output
########################################

def merge_rows(rows_fastlanes, rows_alp):
    """
    Merges two lists of (domain, name, data_type, bits, size)
    from fastlanes_detailed.csv and only_alp.csv.

    Key = (domain, name, data_type)
    We'll produce rows with:
      (domain, name, data_type,
       fastlanes_bits, fastlanes_size,
       alp_bits, alp_size)

    Also build domain_stats & overall_stats for HPC/TS/OBS/DB report.
    """
    merged_dict = {}

    # Insert fastlanes data
    for domain, name, dt, bits, sz in rows_fastlanes:
        key = (domain, name, dt)
        merged_dict.setdefault(key, {
            'fastlanes_bits': 0.0, 'fastlanes_size': 0.0,
            'alp_bits': 0.0,       'alp_size': 0.0
        })
        merged_dict[key]['fastlanes_bits'] += bits
        merged_dict[key]['fastlanes_size'] += sz

    # Insert alp data
    for domain, name, dt, bits, sz in rows_alp:
        key = (domain, name, dt)
        merged_dict.setdefault(key, {
            'fastlanes_bits': 0.0, 'fastlanes_size': 0.0,
            'alp_bits': 0.0,       'alp_size': 0.0
        })
        merged_dict[key]['alp_bits'] += bits
        merged_dict[key]['alp_size'] += sz

    merged_rows = []
    domain_stats = {}
    overall_fastlanes_bits = 0.0
    overall_fastlanes_size = 0.0
    overall_alp_bits = 0.0
    overall_alp_size = 0.0
    overall_count = 0

    for (domain, name, dt), val in merged_dict.items():
        fb = val['fastlanes_bits']
        fs = val['fastlanes_size']
        ab = val['alp_bits']
        asz = val['alp_size']

        merged_rows.append((domain, name, dt, fb, fs, ab, asz))

        # For HPC/TS/OBS/DB stats
        overall_fastlanes_bits += fb
        overall_fastlanes_size += fs
        overall_alp_bits += ab
        overall_alp_size += asz
        overall_count += 1

        if domain not in domain_stats:
            domain_stats[domain] = {
                'fastlanes_bits_sum': 0.0,
                'fastlanes_size_sum': 0.0,
                'alp_bits_sum': 0.0,
                'alp_size_sum': 0.0,
                'count': 0
            }
        domain_stats[domain]['fastlanes_bits_sum'] += fb
        domain_stats[domain]['fastlanes_size_sum'] += fs
        domain_stats[domain]['alp_bits_sum'] += ab
        domain_stats[domain]['alp_size_sum'] += asz
        domain_stats[domain]['count'] += 1

    # Overall stats used for the domain-based CSV
    if overall_count > 0:
        overall_stats = {
            'avg_fastlanes_bits': overall_fastlanes_bits / overall_count,
            'avg_fastlanes_size': overall_fastlanes_size / overall_count,
            'avg_alp_bits': overall_alp_bits / overall_count,
            'avg_alp_size': overall_alp_size / overall_count,
        }
    else:
        overall_stats = {
            'avg_fastlanes_bits': 0.0,
            'avg_fastlanes_size': 0.0,
            'avg_alp_bits': 0.0,
            'avg_alp_size': 0.0,
        }

    return merged_rows, overall_stats, domain_stats

def save_issue36_csv(merged_rows, overall_stats, domain_stats, output_csv):
    """
    Produces 'issue_36_from_alp_repo.csv' with domain-based info:
      domain, name, fastlanes, fastlanes, alp, alp
      "",     "",   bits_per_value, size(bytes), bits_per_value, size(bytes)
    Then each domain group + domain-avg, plus an overall-avg.
    """
    # Group by domain
    grouped = {}
    for (domain, name, dt, fb, fs, ab, asz) in merged_rows:
        # If you wish to show data_type in the CSV name field, do so here:
        # e.g. row_name = f"{name} ({dt})"
        row_name = name
        grouped.setdefault(domain, []).append((row_name, fb, fs, ab, asz))

    domain_order = ["HPC","TS","OBS","DB"]

    with open(output_csv, mode='w', newline='') as f:
        writer = csv.writer(f)
        # Write the 2 header rows
        writer.writerow(["domain", "name", "fastlanes", "fastlanes", "alp", "alp"])
        writer.writerow(["", "", "bits_per_value", "size(bytes)", "bits_per_value", "size(bytes)"])

        for dom in domain_order:
            if dom in grouped:
                domain_rows = grouped[dom]
                for (row_name, fb, fs, ab, asz) in domain_rows:
                    writer.writerow([
                        dom,
                        row_name,
                        f"{fb:.2f}",
                        f"{int(fs)}",
                        f"{ab:.2f}",
                        f"{int(asz)}"
                    ])
                # Domain-avg
                stats = domain_stats[dom]
                c = stats['count']
                avg_fb = stats['fastlanes_bits_sum']/c
                avg_fs = stats['fastlanes_size_sum']/c
                avg_ab = stats['alp_bits_sum']/c
                avg_asz = stats['alp_size_sum']/c
                writer.writerow([
                    dom,
                    "Domain-avg",
                    f"{avg_fb:.2f}",
                    f"{int(round(avg_fs))}",
                    f"{avg_ab:.2f}",
                    f"{int(round(avg_asz))}"
                ])

        # Any domain not HPC/TS/OBS/DB in alphabetical order
        for dom in sorted(grouped.keys()):
            if dom not in domain_order:
                domain_rows = grouped[dom]
                for (row_name, fb, fs, ab, asz) in domain_rows:
                    writer.writerow([
                        dom,
                        row_name,
                        f"{fb:.2f}",
                        f"{int(fs)}",
                        f"{ab:.2f}",
                        f"{int(asz)}"
                    ])
                # Domain-avg
                stats = domain_stats[dom]
                c = stats['count']
                avg_fb = stats['fastlanes_bits_sum']/c
                avg_fs = stats['fastlanes_size_sum']/c
                avg_ab = stats['alp_bits_sum']/c
                avg_asz = stats['alp_size_sum']/c
                writer.writerow([
                    dom,
                    "Domain-avg",
                    f"{avg_fb:.2f}",
                    f"{int(round(avg_fs))}",
                    f"{avg_ab:.2f}",
                    f"{int(round(avg_asz))}"
                ])

        # Overall-avg
        writer.writerow([
            "Overall-avg", "",
            f"{overall_stats['avg_fastlanes_bits']:.2f}",
            f"{int(round(overall_stats['avg_fastlanes_size']))}",
            f"{overall_stats['avg_alp_bits']:.2f}",
            f"{int(round(overall_stats['avg_alp_size']))}"
        ])

##############################################
# 3. "average.csv" from ONLY the ALP CSV data
##############################################

def create_average_csv_alp(rows_alp, output_path):
    """
    Creates 'average.csv' with 3 rows:
      1) DOUBLE
      2) FLOAT
      3) TOTAL

    and 3 columns:
      data_type, average_bits_per_value, compression_ratio

    BUT uses only the data from `only_alp.csv`.

    We gather each row's (data_type, bits).
      - domain, name are irrelevant for average
      - data_type is exactly 'FLOAT' or 'DOUBLE'
      - bits is from bits_per_value

    Then:
      average_bits_per_value = sum_of_bits_for_that_type / count_of_columns
      compression_ratio:
         - FLOAT => 32 / average_bits
         - DOUBLE => 64 / average_bits
         - TOTAL => Weighted across both
    """
    # sums and counts
    sums = {"FLOAT": 0.0, "DOUBLE": 0.0}
    counts = {"FLOAT": 0, "DOUBLE": 0}

    # Collect from rows_alp => (domain, name, data_type, bits, size)
    for (domain, name, dt, bits, sz) in rows_alp:
        # Only handle dt in ("FLOAT","DOUBLE")
        if dt not in ("FLOAT","DOUBLE"):
            continue
        sums[dt] += bits
        counts[dt] += 1

    def safe_avg(dt):
        return sums[dt] / counts[dt] if counts[dt] > 0 else 0.0

    avg_float_bits = safe_avg("FLOAT")
    avg_double_bits = safe_avg("DOUBLE")

    # compression ratio
    # For FLOAT => assume 32 bits uncompressed
    # For DOUBLE => assume 64 bits uncompressed
    float_ratio = 32.0 / avg_float_bits if avg_float_bits > 0 else 0.0
    double_ratio = 64.0 / avg_double_bits if avg_double_bits > 0 else 0.0

    total_sum = sums["FLOAT"] + sums["DOUBLE"]
    total_count = counts["FLOAT"] + counts["DOUBLE"]
    avg_total_bits = total_sum / total_count if total_count > 0 else 0.0

    uncompressed_sum = 32.0*counts["FLOAT"] + 64.0*counts["DOUBLE"]
    total_ratio = uncompressed_sum / total_sum if total_sum > 0 else 0.0

    # Write out average.csv
    with open(output_path, mode='w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(["data_type","average_bits_per_value","compression_ratio"])

        # Row 1: DOUBLE
        writer.writerow([
            "DOUBLE",
            f"{avg_double_bits:.2f}",
            f"{double_ratio:.2f}"
        ])
        # Row 2: FLOAT
        writer.writerow([
            "FLOAT",
            f"{avg_float_bits:.2f}",
            f"{float_ratio:.2f}"
        ])
        # Row 3: TOTAL
        writer.writerow([
            "TOTAL",
            f"{avg_total_bits:.2f}",
            f"{total_ratio:.2f}"
        ])

###########################
# 4. Main execution script
###########################

def main():
    fastlanes_file = "fastlanes_detailed.csv"
    alp_file = "only_alp.csv"
    merged_output = "issue_36_from_alp_repo.csv"
    average_output = "average.csv"

    # Check file existence
    for fname in [fastlanes_file, alp_file]:
        if not os.path.isfile(fname):
            print(f"Error: Missing file '{fname}'.")
            sys.exit(1)

    # Extract domain & data from BOTH CSVs
    rows_fastlanes = extract_domain_data(fastlanes_file)  # (domain, name, data_type, bits, size)
    rows_alp = extract_domain_data(alp_file)              # same structure

    # Merge them for domain-based CSV
    merged_rows, overall_stats, domain_stats = merge_rows(rows_fastlanes, rows_alp)
    if not merged_rows:
        print("No valid rows found in either CSV!")
        sys.exit(1)

    # Save the domain-based breakdown
    save_issue36_csv(merged_rows, overall_stats, domain_stats, merged_output)
    print(f"Domain-based results saved to: {merged_output}")

    # Create 'average.csv' using ONLY data from `only_alp.csv`
    create_average_csv_alp(rows_alp, average_output)
    print(f"Average bits (FLOAT/DOUBLE) from ALP only saved to: {average_output}")

if __name__ == "__main__":
    main()
