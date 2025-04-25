#!/usr/bin/env python3

import csv
import sys
import os

def extract_bits_and_size(csv_file_path):
    """
    Reads a CSV file and returns a list of tuples:
      (domain, cleaned_name, bits, size)
    where bits are extracted from "bits_per_value" and size from "size(bytes)".
    Domains are assigned based on row index:
      - first 10 rows: HPC
      - next 8 rows: TS
      - next 8 rows: OBS
      - next 7 rows: DB
      - remaining rows: UNKNOWN
    Also removes the prefixes "HPC_TS_OBS_" or "DB_" from the name if present.
    """
    rows = []
    with open(csv_file_path, mode='r', newline='') as file:
        reader = csv.DictReader(file)
        for index, row in enumerate(reader):
            try:
                raw_name = row['name']
                bits = float(row['bits_per_value'])
                size_val = float(row['size(bytes)'])

                # Assign domain based on the row index
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

                # Remove prefix from the name if present
                cleaned_name = raw_name
                for prefix in ["HPC_TS_OBS_", "DB_"]:
                    if cleaned_name.startswith(prefix):
                        cleaned_name = cleaned_name[len(prefix):]
                        break

                rows.append((domain, cleaned_name, bits, size_val))
            except (ValueError, KeyError):
                continue  # Skip invalid or incomplete rows
    return rows

def merge_rows(rows_fastlanes, rows_alp):
    """
    Merge two lists of rows from the two CSV files.
    For each key (domain, name), store:
      - fastlanes_bits and fastlanes_size (from fastlanes_detailed.csv)
      - alp_bits and alp_size (from only_alp.csv)
    Missing values are assumed to be 0.
    Returns a list of tuples:
      (domain, name, fastlanes_bits, fastlanes_size, alp_bits, alp_size)
    Also computes per-domain and overall statistics.
    """
    merged = {}
    # Process fastlanes rows
    for domain, name, bits, size_val in rows_fastlanes:
        key = (domain, name)
        merged.setdefault(key, {'fastlanes_bits': 0.0, 'fastlanes_size': 0.0,
                                'alp_bits': 0.0, 'alp_size': 0.0})
        merged[key]['fastlanes_bits'] += bits
        merged[key]['fastlanes_size'] += size_val

    # Process alp rows
    for domain, name, bits, size_val in rows_alp:
        key = (domain, name)
        merged.setdefault(key, {'fastlanes_bits': 0.0, 'fastlanes_size': 0.0,
                                'alp_bits': 0.0, 'alp_size': 0.0})
        merged[key]['alp_bits'] += bits
        merged[key]['alp_size'] += size_val

    merged_rows = []
    domain_stats = {}
    overall_fastlanes_bits = 0.0
    overall_fastlanes_size = 0.0
    overall_alp_bits = 0.0
    overall_alp_size = 0.0
    overall_count = 0

    for (domain, name), values in merged.items():
        fb = values['fastlanes_bits']
        fs = values['fastlanes_size']
        ab = values['alp_bits']
        asz = values['alp_size']
        merged_rows.append((domain, name, fb, fs, ab, asz))

        overall_fastlanes_bits += fb
        overall_fastlanes_size += fs
        overall_alp_bits += ab
        overall_alp_size += asz
        overall_count += 1

        if domain not in domain_stats:
            domain_stats[domain] = {
                'fastlanes_bits_sum': 0.0, 'fastlanes_size_sum': 0.0,
                'alp_bits_sum': 0.0, 'alp_size_sum': 0.0,
                'count': 0
            }
        domain_stats[domain]['fastlanes_bits_sum'] += fb
        domain_stats[domain]['fastlanes_size_sum'] += fs
        domain_stats[domain]['alp_bits_sum'] += ab
        domain_stats[domain]['alp_size_sum'] += asz
        domain_stats[domain]['count'] += 1

    overall_stats = {
        'avg_fastlanes_bits': overall_fastlanes_bits / overall_count if overall_count else 0.0,
        'avg_fastlanes_size': overall_fastlanes_size / overall_count if overall_count else 0.0,
        'avg_alp_bits': overall_alp_bits / overall_count if overall_count else 0.0,
        'avg_alp_size': overall_alp_size / overall_count if overall_count else 0.0,
    }
    return merged_rows, overall_stats, domain_stats

def save_issue36_csv(merged_rows, overall_stats, domain_stats, output_path):
    """
    Save the merged rows into a CSV file.
    The header is written as two rows:
      Row1: domain,name,fastlanes,fastlanes,alp,alp
      Row2: , ,bits_per_value,size(bytes),bits_per_value,size(bytes)
    Rows are grouped by domain and a Domain-avg row is added per group.
    Finally, an Overall-avg row is added.
    Size values are output as integers.
    """
    # Group rows by domain
    grouped = {}
    for domain, name, fb, fs, ab, asz in merged_rows:
        grouped.setdefault(domain, []).append((name, fb, fs, ab, asz))

    # Define desired domain order
    domain_order = ['HPC', 'TS', 'OBS', 'DB']

    with open(output_path, mode='w', newline='') as file:
        writer = csv.writer(file)
        # Two header rows:
        writer.writerow(['domain', 'name', 'fastlanes', 'fastlanes', 'alp', 'alp'])
        writer.writerow(['', '', 'bits_per_value', 'size(bytes)', 'bits_per_value', 'size(bytes)'])

        # Write groups in desired order
        for domain in domain_order:
            if domain in grouped:
                for name, fb, fs, ab, asz in grouped[domain]:
                    writer.writerow([domain, name, f"{fb:.2f}", f"{int(fs)}", f"{ab:.2f}", f"{int(asz)}"])
                avg_fb = domain_stats[domain]['fastlanes_bits_sum'] / domain_stats[domain]['count']
                avg_fs = domain_stats[domain]['fastlanes_size_sum'] / domain_stats[domain]['count']
                avg_ab = domain_stats[domain]['alp_bits_sum'] / domain_stats[domain]['count']
                avg_asz = domain_stats[domain]['alp_size_sum'] / domain_stats[domain]['count']
                writer.writerow([domain, "Domain-avg", f"{avg_fb:.2f}", f"{int(round(avg_fs))}", f"{avg_ab:.2f}", f"{int(round(avg_asz))}"])

        # Write any additional domains (like UNKNOWN) in sorted order
        for domain in sorted(grouped.keys()):
            if domain not in domain_order:
                for name, fb, fs, ab, asz in grouped[domain]:
                    writer.writerow([domain, name, f"{fb:.2f}", f"{int(fs)}", f"{ab:.2f}", f"{int(asz)}"])
                avg_fb = domain_stats[domain]['fastlanes_bits_sum'] / domain_stats[domain]['count']
                avg_fs = domain_stats[domain]['fastlanes_size_sum'] / domain_stats[domain]['count']
                avg_ab = domain_stats[domain]['alp_bits_sum'] / domain_stats[domain]['count']
                avg_asz = domain_stats[domain]['alp_size_sum'] / domain_stats[domain]['count']
                writer.writerow([domain, "Domain-avg", f"{avg_fb:.2f}", f"{int(round(avg_fs))}", f"{avg_ab:.2f}", f"{int(round(avg_asz))}"])

        # Write overall average row
        writer.writerow([
            "Overall-avg", "",
            f"{overall_stats['avg_fastlanes_bits']:.2f}",
            f"{int(round(overall_stats['avg_fastlanes_size']))}",
            f"{overall_stats['avg_alp_bits']:.2f}",
            f"{int(round(overall_stats['avg_alp_size']))}"
        ])

def print_html_table(merged_rows, overall_stats, domain_stats):
    """
    Print an HTML table with the merged rows.
    The header is structured as follows:
      <table>
        <tr>
          <th rowspan="2">domain</th>
          <th rowspan="2">name</th>
          <th colspan="2">fastlanes</th>
          <th colspan="2">alp</th>
        </tr>
        <tr>
          <th>bits_per_value</th>
          <th>size(bytes)</th>
          <th>bits_per_value</th>
          <th>size(bytes)</th>
        </tr>
      </table>
    Data rows are then printed, followed by domain average rows and an overall average row.
    Size values are output as integers.
    """
    # Group rows by domain
    grouped = {}
    for domain, name, fb, fs, ab, asz in merged_rows:
        grouped.setdefault(domain, []).append((name, fb, fs, ab, asz))

    print("<table>")
    print("  <tr>")
    print("    <th rowspan=\"2\">domain</th>")
    print("    <th rowspan=\"2\">name</th>")
    print("    <th colspan=\"2\">fastlanes</th>")
    print("    <th colspan=\"2\">alp</th>")
    print("  </tr>")
    print("  <tr>")
    print("    <th>bits_per_value</th>")
    print("    <th>size(bytes)</th>")
    print("    <th>bits_per_value</th>")
    print("    <th>size(bytes)</th>")
    print("  </tr>")

    domain_order = ['HPC', 'TS', 'OBS', 'DB']
    for domain in domain_order:
        if domain in grouped:
            for name, fb, fs, ab, asz in grouped[domain]:
                print("  <tr>")
                print(f"    <td>{domain}</td>")
                print(f"    <td>{name}</td>")
                print(f"    <td>{fb:.2f}</td>")
                print(f"    <td>{int(fs)}</td>")
                print(f"    <td>{ab:.2f}</td>")
                print(f"    <td>{int(asz)}</td>")
                print("  </tr>")
            avg_fb = domain_stats[domain]['fastlanes_bits_sum'] / domain_stats[domain]['count']
            avg_fs = domain_stats[domain]['fastlanes_size_sum'] / domain_stats[domain]['count']
            avg_ab = domain_stats[domain]['alp_bits_sum'] / domain_stats[domain]['count']
            avg_asz = domain_stats[domain]['alp_size_sum'] / domain_stats[domain]['count']
            print("  <tr>")
            print(f"    <td>{domain}</td>")
            print("    <td>Domain-avg</td>")
            print(f"    <td>{avg_fb:.2f}</td>")
            print(f"    <td>{int(round(avg_fs))}</td>")
            print(f"    <td>{avg_ab:.2f}</td>")
            print(f"    <td>{int(round(avg_asz))}</td>")
            print("  </tr>")

    for domain in sorted(grouped.keys()):
        if domain not in domain_order:
            for name, fb, fs, ab, asz in grouped[domain]:
                print("  <tr>")
                print(f"    <td>{domain}</td>")
                print(f"    <td>{name}</td>")
                print(f"    <td>{fb:.2f}</td>")
                print(f"    <td>{int(fs)}</td>")
                print(f"    <td>{ab:.2f}</td>")
                print(f"    <td>{int(asz)}</td>")
                print("  </tr>")
            avg_fb = domain_stats[domain]['fastlanes_bits_sum'] / domain_stats[domain]['count']
            avg_fs = domain_stats[domain]['fastlanes_size_sum'] / domain_stats[domain]['count']
            avg_ab = domain_stats[domain]['alp_bits_sum'] / domain_stats[domain]['count']
            avg_asz = domain_stats[domain]['alp_size_sum'] / domain_stats[domain]['count']
            print("  <tr>")
            print(f"    <td>{domain}</td>")
            print("    <td>Domain-avg</td>")
            print(f"    <td>{avg_fb:.2f}</td>")
            print(f"    <td>{int(round(avg_fs))}</td>")
            print(f"    <td>{avg_ab:.2f}</td>")
            print(f"    <td>{int(round(avg_asz))}</td>")
            print("  </tr>")

    print("  <tr>")
    print("    <td>Overall-avg</td>")
    print("    <td></td>")
    print(f"    <td>{overall_stats['avg_fastlanes_bits']:.2f}</td>")
    print(f"    <td>{int(round(overall_stats['avg_fastlanes_size']))}</td>")
    print(f"    <td>{overall_stats['avg_alp_bits']:.2f}</td>")
    print(f"    <td>{int(round(overall_stats['avg_alp_size']))}</td>")
    print("  </tr>")
    print("</table>")

def main():
    # Input file names
    fastlanes_file = "fastlanes_detailed.csv"
    alp_file = "only_alp.csv"
    output_csv = "issue_36_from_alp_repo.csv"

    # Check that both input files exist
    for file in [fastlanes_file, alp_file]:
        if not os.path.isfile(file):
            print(f"Error: File '{file}' not found.")
            sys.exit(1)

    # Extract rows from each file (including bits_per_value and size(bytes))
    rows_fastlanes = extract_bits_and_size(fastlanes_file)
    rows_alp = extract_bits_and_size(alp_file)

    # Merge rows from the two files
    merged_rows, overall_stats, domain_stats = merge_rows(rows_fastlanes, rows_alp)

    if not merged_rows:
        print("No valid rows found in either file.")
        sys.exit(1)

    # Save merged results to CSV
    save_issue36_csv(merged_rows, overall_stats, domain_stats, output_csv)
    print(f"Issue36 results saved to: {output_csv}")

    # Print the merged results as an HTML table
    print("\nHTML Table:")
    print_html_table(merged_rows, overall_stats, domain_stats)

if __name__ == '__main__':
    main()
