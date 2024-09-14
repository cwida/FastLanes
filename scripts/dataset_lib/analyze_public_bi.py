from file_format import *
from scripts.dataset_lib.public_bi import *
from scripts.dataset_lib.common import *

ttl_str_col = 0
ttl_int_col = 0
ttl_dbl_col = 0


def analyze(table_name, yaml_file):
    global ttl_str_col
    global ttl_dbl_col
    global ttl_int_col
    table_list = public_bi.get_table_list(table_name)

    ttl_col = 0
    str_col = 0
    int_col = 0
    dbl_col = 0

    with open(yaml_file, "r") as stream:
        try:
            schema = yaml.safe_load(stream)
            for index, entry in enumerate(schema["columns"]):
                type = entry["type"]
                if type == "skip":
                    continue

                ttl_col += 1

                if type == "integer":
                    int_col += 1
                    ttl_int_col += 1
                if type == "string":
                    str_col += 1
                    ttl_str_col += 1
                if type == "double":
                    dbl_col += 1
                    ttl_dbl_col += 1

        except yaml.YAMLError as exc:
            print(exc)

    print("{0},{1},{2},{3},{4}".format(table_name, str(ttl_col), int_col, str_col, dbl_col))


def compress_all():
    for table_name in public_bi.table_list:
        yaml_file_path = os.path.join(public_bi_yaml_dir_path, table_name + "/" + table_name + "_1/schema.yaml")
        analyze(table_name, yaml_file_path)

    print(str(ttl_int_col) + " " + str(ttl_dbl_col) + " " + str(ttl_str_col))


if __name__ == '__main__':
    compress_all()
