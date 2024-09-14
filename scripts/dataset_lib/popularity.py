from scripts.dataset_lib.combine_ccc_vs_fls import *


def load_result(table, ff):
    path = os.path.join(ff.get_result_dir_path(), table + "_1.csv")
    df = pd.read_csv(path)

    return df


def round_2(double):
    answer = str(round(double, 2))
    return answer


def get_list(yaml_file, given_type):
    col_idx_list = []
    with open(yaml_file, "r") as stream:
        try:
            schema = yaml.safe_load(stream)

            col_idx = 0
            for index, entry in enumerate(schema["columns"]):
                type = entry["type"]
                if type == given_type:
                    col_idx_list.append(col_idx)
                if type != "skip":
                    col_idx = col_idx + 1

        except yaml.YAMLError as exc:
            print(exc)

    return col_idx_list


def cal_popularity(ttl, type):
    result_df = pd.DataFrame(
        columns=[
            "Table",  #
            "ID",
            "Popularity",
        ])

    total_df = []

    for table_name in public_bi.get_dataset_list():
        yaml_file_path = os.path.join(public_bi_yaml_dir_path, table_name + "/" + table_name + "_1/schema.yaml")
        list = get_list(yaml_file_path, type)
        df = load_result(table_name, fls_ff)
        int_df = df.iloc[list, :]

        total_df.append(int_df)

    result = pd.concat(total_df)
    pop_df = result.groupby("EXP_ID").size().to_frame('size')
    pop_df["percentage"] = pop_df["size"] / ttl
    pop_df = pop_df.round(2)

    print(pop_df.sum())

    return pop_df


if __name__ == '__main__':
    int_pop_path = os.path.join(vs_result_dir_path, "int_pop.csv")
    cal_popularity(1022, "integer").to_csv(int_pop_path)

    str_pop_path = os.path.join(vs_result_dir_path, "str_pop.csv")
    cal_popularity(735, "string").to_csv(str_pop_path)

    dbl_pop_path = os.path.join(vs_result_dir_path, "dbl_pop.csv")
    cal_popularity(466, "double").to_csv(dbl_pop_path)
