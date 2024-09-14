from pyarrow.types import is_int64, is_string
from scripts.dataset_lib.public_bi import *
from scripts.dataset_lib.common import *
from scripts.dataset_lib.log import ok
from scripts.dataset_lib.file_format import *
from scripts.dataset_lib.combine_ccc_vs_fls import *


def load_result(table, ff):
    path = os.path.join(ff.get_result_dir_path(), table + "_1.csv")
    df = pd.read_csv(path)

    return df


def round_2(double):
    answer = str(round(double, 2))
    return answer


def generate_col_n_and_res():
    result_df = pd.DataFrame(
        columns=[ \
            "Table",  #
            "FLS_COL_N", "FLS",  #
            "PQ_DICTIONARY_SNAPPY_COL_N", "PQ_DICTIONARY_SNAPPY",  #
            "ORC_COL_N", "ORC",  #
            "DUCKDB_COL_N", "DUCKDB",  #
            "BB_COL_N", "BB",  #
            "PQ_DICTIONARY_ZSTD_COL_N", "PQ_DICTIONARY_ZSTD",  #
            "FLS_CCC_COL_N", "FLS_CCC",  #
        ])

    result_path = os.path.join(vs_result_dir_path, "result.csv")

    for table in public_bi.get_dataset_list():

        combine_table(table)  # FOR FLS_CCC

        row = [table]
        for ff in FileFormat:
            if ff is FileFormat.CCC:  # not a file format
                continue
            df = load_result(table, ff)
            ttl_sz = df["SIZE"].sum()
            row.append(len(df))
            row.append(ttl_sz)
        result_df.loc[len(result_df)] = row

    fls_ttl_sz = result_df["FLS"].sum()
    fls_ttl_col = result_df["FLS_COL_N"].sum()
    pq_dictionary_snappy_ttl_sz = result_df["PQ_DICTIONARY_SNAPPY"].sum()
    pq_dictionary_snappy_ttl_col = result_df["PQ_DICTIONARY_SNAPPY_COL_N"].sum()
    orc_ttl_sz = result_df["ORC"].sum()
    orc_ttl_col = result_df["ORC_COL_N"].sum()
    duckdb_ttl_sz = result_df["DUCKDB"].sum() * 64 / 1000
    duckdb_ttl_col = result_df["DUCKDB_COL_N"].sum()
    bb_ttl_sz = result_df["BB"].sum()
    bb_ttl_col = result_df["BB_COL_N"].sum()
    pq_dictionary_zstd_ttl_sz = result_df["PQ_DICTIONARY_ZSTD"].sum()
    pq_dictionary_zstd_ttl_col = result_df["PQ_DICTIONARY_ZSTD_COL_N"].sum()
    fls_ccc_ttl_sz = result_df["FLS_CCC"].sum()
    fls_ccc_ttl_col = result_df["FLS_CCC_COL_N"].sum()

    result_df.loc[len(result_df)] = ["TTL_SZ",  #
                                     fls_ttl_col, fls_ttl_sz,  #
                                     pq_dictionary_snappy_ttl_col, pq_dictionary_snappy_ttl_sz,  #
                                     orc_ttl_col, orc_ttl_sz,  #
                                     duckdb_ttl_col, duckdb_ttl_sz,  #
                                     bb_ttl_col, bb_ttl_sz,  #
                                     pq_dictionary_zstd_ttl_col, pq_dictionary_zstd_ttl_sz,  #
                                     fls_ccc_ttl_sz, fls_ccc_ttl_col  #
                                     ]

    result_df.loc[len(result_df)] = ["RATIO",  #
                                     round_2(fls_ttl_col / fls_ccc_ttl_col - 1),  #
                                     round_2(fls_ttl_sz / fls_ccc_ttl_sz - 1),  #
                                     round_2(pq_dictionary_snappy_ttl_col / fls_ccc_ttl_col - 1),  #
                                     round_2(pq_dictionary_snappy_ttl_sz / fls_ccc_ttl_sz - 1),  #
                                     round_2(orc_ttl_col / fls_ccc_ttl_col - 1),  #
                                     round_2(orc_ttl_sz / fls_ccc_ttl_sz - 1),  #
                                     round_2(duckdb_ttl_col / fls_ccc_ttl_col - 1),  #
                                     round_2(duckdb_ttl_sz / fls_ccc_ttl_sz - 1),  #
                                     round_2(bb_ttl_col / fls_ccc_ttl_col - 1),  #
                                     round_2(bb_ttl_sz / fls_ccc_ttl_sz - 1),  #
                                     round_2(pq_dictionary_zstd_ttl_col / fls_ccc_ttl_col - 1),  #
                                     round_2(pq_dictionary_zstd_ttl_sz / fls_ccc_ttl_sz - 1),  #
                                     round_2(fls_ccc_ttl_col / fls_ccc_ttl_col - 1),  #
                                     round_2(fls_ccc_ttl_sz / fls_ccc_ttl_sz - 1),  #
                                     ]

    result_df.loc[len(result_df)] = ["RATIO",  #
                                     round_2(fls_ttl_col / fls_ttl_col - 1),  #
                                     round_2(fls_ttl_sz / fls_ttl_sz - 1),  #
                                     round_2(pq_dictionary_snappy_ttl_col / fls_ttl_col - 1),  #
                                     round_2(pq_dictionary_snappy_ttl_sz / fls_ttl_sz - 1),  #
                                     round_2(orc_ttl_col / fls_ttl_col - 1),  #
                                     round_2(orc_ttl_sz / fls_ttl_sz - 1),  #
                                     round_2(duckdb_ttl_col / fls_ttl_col - 1),  #
                                     round_2(duckdb_ttl_sz / fls_ttl_sz - 1),  #
                                     round_2(bb_ttl_col / fls_ttl_col - 1),  #
                                     round_2(bb_ttl_sz / fls_ttl_sz - 1),  #
                                     round_2(pq_dictionary_zstd_ttl_col / fls_ttl_col - 1),  #
                                     round_2(pq_dictionary_zstd_ttl_sz / fls_ttl_sz - 1),  #
                                     round_2(fls_ccc_ttl_col / fls_ttl_col - 1),  #
                                     round_2(fls_ccc_ttl_sz / fls_ttl_sz - 1),  #
                                     ]
    return result_df


def generate_result():
    result_df = pd.DataFrame(
        columns=[
            "Table",  #
            "FLS_CCC",
            "FLS",  #
            "PQ_DICTIONARY_SNAPPY",  #
            "ORC",  #
            "DUCKDB",  #
            "BB",  #
            "PQ_DICTIONARY_ZSTD",  #
            "LWC",  #
            "UNCOMPRESSED",
        ])

    for table in public_bi.get_dataset_list():
        combine_table(table)  # FOR FLS_CCC

        row = [table]

        df = load_result(table, fls_ccc_ff)
        uncompressed_sz = df["SIZE"].sum()

        for ff in file_format_list:
            df = load_result(table, ff)
            ttl_sz = 0
            if ff.type is FileFormatT.DUCKDB:
                ttl_sz = df["SIZE"].sum() * 64 / 1000
            else:
                ttl_sz = df["SIZE"].sum()

            row.append(ttl_sz / uncompressed_sz)

        result_df.loc[len(result_df)] = row

    uncompressed_ttl_sz = result_df["UNCOMPRESSED"].sum() / public_bi.get_n_table()
    fls_ccc_ttl_sz = result_df["FLS_CCC"].sum() / public_bi.get_n_table()
    fls_ttl_sz = result_df["FLS"].sum() / public_bi.get_n_table()
    pq_dictionary_snappy_ttl_sz = result_df["PQ_DICTIONARY_SNAPPY"].sum() / public_bi.get_n_table()
    orc_ttl_sz = result_df["ORC"].sum() / public_bi.get_n_table()
    duckdb_ttl_sz = result_df["DUCKDB"].sum() / public_bi.get_n_table()
    bb_ttl_sz = result_df["BB"].sum() / public_bi.get_n_table()
    pq_dictionary_zstd_ttl_sz = result_df["PQ_DICTIONARY_ZSTD"].sum() / public_bi.get_n_table()
    lwc_ttl_sz = result_df["LWC"].sum() / public_bi.get_n_table()

    result_df.loc[len(result_df)] = [
        "TTL_SZ",  #
        fls_ttl_sz,  #
        fls_ccc_ttl_sz,  #
        pq_dictionary_snappy_ttl_sz,  #
        orc_ttl_sz,  #
        duckdb_ttl_sz,  #
        bb_ttl_sz,  #
        pq_dictionary_zstd_ttl_sz,  #
        lwc_ttl_sz,  #
        uncompressed_ttl_sz,  #
    ]

    result_df = result_df.round(2)
    return result_df


def generate_new():
    result_df = pd.DataFrame(
        columns=[
            "Table",  #
            "FLS",  #
            "FLS_CCC",
            "PQ_DICTIONARY_SNAPPY",  #
            "ORC",  #
            "DUCKDB",  #
            "BB",  #
            "PQ_DICTIONARY_ZSTD",  #
            "LWC",  #
            "UNCOMPRESSED",
        ])

    for table in public_bi.get_dataset_list():
        combine_table(table)  # FOR FLS_CCC

        row = [table]

        df = load_result(table, uncompressed_ff)
        uncompressed_sz = df["SIZE"].sum()

        tmp_size = 0
        for ff in file_format_list:
            df = load_result(table, ff)
            ttl_sz = 0
            if ff.type is FileFormatT.DUCKDB:
                ttl_sz = df["SIZE"].sum() * 64 / 1000
            else:
                ttl_sz = df["SIZE"].sum()

            if ff.type is FileFormatT.FLS:
                tmp_size = ttl_sz

            if ff.type is FileFormatT.FLS_CCC and tmp_size < ttl_sz:
                ttl_sz = tmp_size

            row.append(ttl_sz)

        result_df.loc[len(result_df)] = row

    uncompressed_ttl_sz = result_df["UNCOMPRESSED"].sum()
    fls_ccc_ttl_sz = result_df["FLS_CCC"].sum()
    fls_ttl_sz = result_df["FLS"].sum()
    pq_dictionary_snappy_ttl_sz = result_df["PQ_DICTIONARY_SNAPPY"].sum()
    orc_ttl_sz = result_df["ORC"].sum()
    duckdb_ttl_sz = result_df["DUCKDB"].sum()
    bb_ttl_sz = result_df["BB"].sum()
    pq_dictionary_zstd_ttl_sz = result_df["PQ_DICTIONARY_ZSTD"].sum()
    lwc_ttl_sz = result_df["LWC"].sum()

    result_df.loc[len(result_df)] = [
        "TTL_SZ",  #
        uncompressed_ttl_sz / fls_ttl_sz,  #
        uncompressed_ttl_sz / fls_ccc_ttl_sz,  #
        uncompressed_ttl_sz / pq_dictionary_snappy_ttl_sz,  #
        uncompressed_ttl_sz / orc_ttl_sz,  #
        uncompressed_ttl_sz / duckdb_ttl_sz,  #
        uncompressed_ttl_sz / bb_ttl_sz,  #
        uncompressed_ttl_sz / pq_dictionary_zstd_ttl_sz,  #
        uncompressed_ttl_sz / lwc_ttl_sz,  #
        uncompressed_ttl_sz / uncompressed_ttl_sz,  #
    ]

    result_df.loc[len(result_df)] = [
        "TTL_SZ",  #
        uncompressed_ttl_sz / fls_ccc_ttl_sz,  #
        uncompressed_ttl_sz / fls_ttl_sz,  #
        uncompressed_ttl_sz / pq_dictionary_snappy_ttl_sz,  #
        uncompressed_ttl_sz / orc_ttl_sz,  #
        uncompressed_ttl_sz / duckdb_ttl_sz,  #
        uncompressed_ttl_sz / bb_ttl_sz,  #
        uncompressed_ttl_sz / pq_dictionary_zstd_ttl_sz,  #
        uncompressed_ttl_sz / lwc_ttl_sz,  #
        uncompressed_ttl_sz / uncompressed_ttl_sz,  #
    ]

    result_df = result_df.round(2)
    return result_df


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


def generate_type(type):
    result_df = pd.DataFrame(
        columns=[
            "Table",  #
            "FLS",  #
            "FLS_CCC",
            "PQ_DICTIONARY_SNAPPY",  #
            "ORC",  #
            "DUCKDB",  #
            "BB",  #
            "PQ_DICTIONARY_ZSTD",  #
            "LWC",  #
            "UNCOMPRESSED",
        ])

    for table in public_bi.get_dataset_list():
        yaml_file_path = os.path.join(public_bi_yaml_dir_path, table + "/" + table + "_1/schema.yaml")

        combine_table(table)  # FOR FLS_CCC

        row = [table]

        df = load_result(table, uncompressed_ff)
        list = get_list(yaml_file_path, type)
        int_df = df.iloc[list, :]
        uncompressed_sz = int_df["SIZE"].sum()

        tmp_size = 0
        for ff in file_format_list:
            list = get_list(yaml_file_path, type)
            df = load_result(table, ff)
            int_df = df.iloc[list, :]
            ttl_sz = 0
            if ff.type is FileFormatT.DUCKDB:
                ttl_sz = int_df["SIZE"].sum() * 64 / 1000
            else:
                ttl_sz = int_df["SIZE"].sum()

            if ff.type is FileFormatT.FLS:
                tmp_size = ttl_sz

            if ff.type is FileFormatT.FLS_CCC and tmp_size < ttl_sz:
                ttl_sz = tmp_size

            row.append(ttl_sz)

        result_df.loc[len(result_df)] = row

    uncompressed_ttl_sz = result_df["UNCOMPRESSED"].sum()
    fls_ttl_sz = result_df["FLS"].sum()
    fls_ccc_ttl_sz = result_df["FLS_CCC"].sum()
    pq_dictionary_snappy_ttl_sz = result_df["PQ_DICTIONARY_SNAPPY"].sum()
    orc_ttl_sz = result_df["ORC"].sum()
    duckdb_ttl_sz = result_df["DUCKDB"].sum()
    bb_ttl_sz = result_df["BB"].sum()
    pq_dictionary_zstd_ttl_sz = result_df["PQ_DICTIONARY_ZSTD"].sum()
    lwc_ttl_sz = result_df["LWC"].sum()

    result_df.loc[len(result_df)] = [
        "TTL_SZ",  #
        uncompressed_ttl_sz / fls_ttl_sz,  #
        uncompressed_ttl_sz / fls_ccc_ttl_sz,  #
        uncompressed_ttl_sz / pq_dictionary_snappy_ttl_sz,  #
        uncompressed_ttl_sz / orc_ttl_sz,  #
        uncompressed_ttl_sz / duckdb_ttl_sz,  #
        uncompressed_ttl_sz / bb_ttl_sz,  #
        uncompressed_ttl_sz / pq_dictionary_zstd_ttl_sz,  #
        uncompressed_ttl_sz / lwc_ttl_sz,  #
        uncompressed_ttl_sz / uncompressed_ttl_sz,  #
    ]

    result_df = result_df.round(2)
    return result_df


if __name__ == '__main__':
    # generate_col_n_and_res()
    final_path = os.path.join(vs_result_dir_path, "final.csv")
    generate_new().to_csv(final_path)

    result_path = os.path.join(vs_result_dir_path, "result.csv")
    generate_result().to_csv(result_path)

    str_result_path = os.path.join(vs_result_dir_path, "str.csv")
    generate_type("string").to_csv(str_result_path)

    dbl_result_path = os.path.join(vs_result_dir_path, "dbl.csv")
    generate_type("double").to_csv(dbl_result_path)

    int_result_path = os.path.join(vs_result_dir_path, "int.csv")
    generate_type("integer").to_csv(int_result_path)
