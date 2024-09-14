from scripts.dataset_lib.file_format import *


def combine(ccc_path, fls_path, fls_ccc_path):
    with open(ccc_path, 'r') as ccc_file, open(fls_path, 'r') as fls_file, open(fls_ccc_path, 'w') as fls_ccc_file:
        for ccc_line, fls_line in zip(ccc_file, fls_file):
            if 'INVALID' in ccc_line:
                fls_ccc_file.write(fls_line)
            else:
                fls_ccc_file.write(ccc_line)


def combine_table(table):
    ccc_path = os.path.join(ccc_result_dir_path, table + "_1.csv")
    fls_path = os.path.join(fls_result_dir_path, table + "_1.csv")
    fls_ccc_path = os.path.join(fls_ccc_result_dir_path, table + "_1.csv")

    combine(ccc_path, fls_path, fls_ccc_path)


def combine_ccc_vs_fls():
    for table in public_bi.table_list:
        combine_table(table)


if __name__ == '__main__':
    combine_ccc_vs_fls()
