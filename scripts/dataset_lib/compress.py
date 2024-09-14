from file_format import *
from scripts.dataset_lib.public_bi import *
from scripts.dataset_lib.common import *


def compress(table_name, yaml_file):
    table_list = public_bi.get_table_list(table_name)

    for table_n in table_list:
        for ff in file_format_list:
            ff.compress(table_name, table_n, yaml_file)
            ok("Table {0} is written by {1}".format(table_name, ff.name))


def compress_all():
    for table_name in public_bi.table_list:
        yaml_file_path = os.path.join(public_bi_yaml_dir_path, table_name + "/" + table_name + "_1/schema.yaml")
        compress(table_name, yaml_file_path)


if __name__ == '__main__':
    compress_all()
