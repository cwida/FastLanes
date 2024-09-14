#!/usr/bin/env python

from dataset_lib.datasets import *


def to_dir(dataset):
    dirs_string = ""

    for table in dataset.table_list:
        dirs_string = dirs_string + '''	static constexpr string_view {0} {{{1}}}; //NOLINT
            '''.format(table, dataset.get_dir_path(table))

    return dirs_string


def write_header_file(dataset):
    dirs_string = to_dir(dataset)

    output = ""
    with open("template/dataset_header.cpp") as template_file:
        template_file_string = template_file.read()
        output = output + template_file_string.format(dataset.name.upper(), dataset.name, dirs_string)

    footer_dir_path = "../data/include/data/footer"
    header_file_name = "{0}.hpp".format(dataset.name)
    header_file_path = os.path.join(footer_dir_path, header_file_name)

    print(header_file_path)

    with open(header_file_path, 'w+') as header_file:
        header_file.write(output)
        header_file.close()


def main():
    for dataset in datasets:
        write_header_file(dataset)


if __name__ == "__main__":
    main()
