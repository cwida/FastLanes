import csv
import pandas as pd


def generate_1(bw):
    tuple_c = 256 * 1024 * 1024

    new_column_values = []

    df = pd.DataFrame()
    for i in range(tuple_c):
        new_column_values.append(str(1) + "|")

    df['a'] = new_column_values
    df.to_csv("../data/fls/{0}_{1}.tbl".format(tuple_c, bw), index=False, header=False, quoting=csv.QUOTE_NONE)


def generate_2(bw):
    tuple_c = 256 * 1024 * 1024  # 1 GB

    new_column_values = [str(1) + "|\n"] * tuple_c

    with open("../data/fls/data_1G_32bit{0}_bw{1}.tbl".format(tuple_c, bw), 'w') as f:
        for i in range(0, tuple_c):
            f.write(new_column_values[i])


if __name__ == '__main__':
    generate_1(1)
