from scripts.dataset_lib.env import *
from scripts.dataset_lib.public_bi import *
from enum import Enum
import pyarrow.orc as orc
import duckdb
import yaml


class FileFormatT(Enum):
    INVALID = 0
    FLS = 1
    PQ_DICTIONARY_SNAPPY = 2
    ORC_SNAPPY = 3
    DUCKDB = 4
    BB = 5
    PQ_DICTIONARY_ZSTD = 6
    CCC = 7
    FLS_CCC = 8
    LWC = 9
    UNCOMPRESSED = 10


def get_file_size(pq_test_file_path):
    return os.path.getsize(pq_test_file_path)


def get_index_list(yaml_file):
    col_idx_list = []
    with open(yaml_file, "r") as stream:
        try:
            schema = yaml.safe_load(stream)
            for index, entry in enumerate(schema["columns"]):
                type = entry["type"]
                if type == "skip":
                    continue
                col_idx_list.append(index)

        except yaml.YAMLError as exc:
            print(exc)

    return col_idx_list


def write_pq_d_s(csv_table, dataset, table_n, yaml_file):
    result_file_path = os.path.join(pq_dictionary_snappy_result_dir_path, dataset + "_" + str(table_n) + ".csv")
    with open(result_file_path, 'w') as f:
        f.write("DATASET,TABLE,COL_IDX,EXP_ID,EXP_T/ENCODER_T,VAR_T/COMPRESSOR,SIZE\n")
        pq_test_file_path = os.path.join(test_dir_path, "compress_bi_py.pq")
        col_idx_list = get_index_list(yaml_file)

        for col_idx in col_idx_list:
            filtered_table = csv_table.select([col_idx])
            # https://arrow.apache.org/docs/cpp/parquet.html#encodings
            # https://arrow.apache.org/docs/python/generated/pyarrow.parquet.write_table.html
            pq.write_table(filtered_table,
                           pq_test_file_path,
                           compression="SNAPPY",
                           version="2.6",
                           data_page_version="2.0",
                           use_dictionary=True,
                           data_page_size=16 * 256 * 1024)

            f.write("public_bi,{0},{1},0,{2},{3},{4}\n".format(dataset,
                                                               str(col_idx),
                                                               "DICTIONARY",
                                                               "SNAPPY",
                                                               str(get_file_size(pq_test_file_path))))

        ok(result_file_path + " has been successfully writen!")


def write_pq_d_z(csv_table, dataset, table_n, yaml_file):
    result_file_path = os.path.join(pq_dictionary_zstd_result_dir_path, dataset + "_" + str(table_n) + ".csv")
    with open(result_file_path, 'w') as f:
        f.write("DATASET,TABLE,COL_IDX,EXP_ID,EXP_T/ENCODER_T,VAR_T/COMPRESSOR,SIZE\n")
        pq_test_file_path = os.path.join(test_dir_path, "compress_bi_py.pq")
        col_idx_list = get_index_list(yaml_file)

        for col_idx in col_idx_list:
            filtered_table = csv_table.select([col_idx])
            # https://arrow.apache.org/docs/cpp/parquet.html#encodings
            # https://arrow.apache.org/docs/python/generated/pyarrow.parquet.write_table.html
            pq.write_table(filtered_table,
                           pq_test_file_path,
                           compression="ZSTD",
                           version="2.6",
                           data_page_version="2.0",
                           use_dictionary=True,
                           data_page_size=16 * 256 * 1024)

            f.write("public_bi,{0},{1},0,{2},{3},{4}\n".format(dataset,
                                                               str(col_idx),
                                                               "DICTIONARY",
                                                               "ZSTD",
                                                               str(get_file_size(pq_test_file_path))))

        ok(result_file_path + " has been successfully writen!")


def write_orc_snappy(csv_table, dataset, table_n, yaml_file):
    result_file_path = os.path.join(orc_result_dir_path, dataset + "_" + str(table_n) + ".csv")
    with open(result_file_path, 'w') as f:
        f.write("DATASET,TABLE,COL_IDX,EXP_ID,EXP_T/ENCODER_T,VAR_T/COMPRESSOR,SIZE\n")
        pq_test_file_path = os.path.join(test_dir_path, "compress_bi_py.orc")

        col_idx_list = get_index_list(yaml_file)

        for col_idx in col_idx_list:
            filtered_table = csv_table.select([col_idx])

            size = 0
            col_type = filtered_table.columns[0].type
            if col_type == "null":
                size = 0
            elif col_type == "time32[s]":  # TODO[PAPER]
                size = 0
            else:
                orc.write_table(filtered_table, pq_test_file_path, compression='SNAPPY')
                size = get_file_size(pq_test_file_path)
            # https: // pyorc.readthedocs.io / en / stable / tutorial.html

            f.write("public_bi,{0},{1},0,0,{2},{3}\n".format(dataset,
                                                             str(col_idx),
                                                             "SNAPPY",
                                                             str(size)))

        ok(result_file_path + " has been successfully writen!")


def write_orc(csv_table, dataset, table_n, yaml_file, result_dir_path):
    result_file_path = os.path.join(result_dir_path, dataset + "_" + str(table_n) + ".csv")
    with open(result_file_path, 'w') as f:
        f.write("DATASET,TABLE,COL_IDX,EXP_ID,EXP_T/ENCODER_T,VAR_T/COMPRESSOR,SIZE\n")
        pq_test_file_path = os.path.join(test_dir_path, "compress_bi_py.orc")

        col_idx_list = get_index_list(yaml_file)

        for col_idx in col_idx_list:
            filtered_table = csv_table.select([col_idx])

            size = 0
            col_type = filtered_table.columns[0].type
            if col_type == "null":
                size = 0
            elif col_type == "time32[s]":  # TODO[PAPER]
                size = 0
            else:
                orc.write_table(filtered_table, pq_test_file_path, compression='uncompressed')
                size = get_file_size(pq_test_file_path)
            # https://pyorc.readthedocs.io/en/stable/tutorial.html

            f.write("public_bi,{0},{1},0,0,{2},{3}\n".format(dataset,
                                                             str(col_idx),
                                                             "uncompressed",
                                                             str(size)))

        ok(result_file_path + " has been successfully writen!")


def write_duckdb(csv_table, dataset, table_n, yaml_file):
    result_file_path = os.path.join(duckdb_result_dir_path, dataset + "_" + str(table_n) + ".csv")
    with open(result_file_path, 'w') as f:
        f.write("DATASET,TABLE,COL_IDX,EXP_ID,EXP_T/ENCODER_T,VAR_T/COMPRESSOR,SIZE\n")
        pq_test_file_path = os.path.join(test_dir_path, "compress_bi_py.db")

        col_idx_list = get_index_list(yaml_file)

        for col_idx in col_idx_list:
            filtered_table = csv_table.select([col_idx])

            os.remove(pq_test_file_path)
            con = duckdb.connect(pq_test_file_path)
            con.sql('''CREATE TABLE tmp AS SELECT * FROM filtered_table''')
            df = con.sql('''
                SELECT 
                    block_id
                FROM 
                    pragma_storage_info('tmp')
                where 
                segment_type = 'BIGINT'
                ''').fetchdf()
            n_bigint_block = len(df['block_id'].unique())

            df = con.sql('''
                SELECT 
                    block_id
                FROM 
                    pragma_storage_info('tmp')
                where 
                segment_type = 'VARCHAR'
                ''').fetchdf()
            n_varchar_block = len(df['block_id'].unique())

            df = con.sql('''
                SELECT 
                    block_id
                FROM 
                    pragma_storage_info('tmp')
                where 
                segment_type = 'DOUBLE'
                ''').fetchdf()
            n_double_block = len(df['block_id'].unique())

            # con.sql("EXPORT DATABASE '{0}'".format(test_dir_path))
            # con.sql("PRAGMA database_size;").show()
            # con.sql("PRAGMA version").show()
            # # con.sql("CALL pragma_database_size();").show()
            # df = con.sql("CALL pragma_storage_info('tmp')").fetchdf()
            # print(df.to_string())
            # con.sql(
            #     '''
            # SELECT * EXCLUDE (column_path, segment_id, start, stats, persistent, block_id, block_offset, has_updates)
            # FROM pragma_storage_info('tmp')
            # USING SAMPLE 10 ROWS
            # ORDER BY row_group_id;
            # '''
            # ).show()
            # df = con.sql("CALL pragma_storage_info('tmp')").fetchdf()
            con.close()

            # print(df.to_string())
            size = (n_bigint_block + n_varchar_block + n_double_block) * 256 * 1024

            f.write("public_bi,{0},{1},0,{2},{2},{3}\n".format(dataset,
                                                               str(col_idx),
                                                               "DUCKDB",
                                                               str(size)))

        ok(result_file_path + " has been successfully writen!")


def write_pq_n_s(csv_table, dataset, table_n, yaml_file):
    result_file_path = os.path.join(pq_dictionary_snappy_result_dir_path, dataset + "_" + str(table_n) + ".csv")
    with open(result_file_path, 'w') as f:
        f.write("DATASET,TABLE,COL_IDX,EXP_ID,EXP_T/ENCODER_T,VAR_T/COMPRESSOR,SIZE\n")
        pq_test_file_path = os.path.join(test_dir_path, "compress_bi_py.pq")
        col_idx_list = get_index_list(yaml_file)

        for col_idx in col_idx_list:
            filtered_table = csv_table.select([col_idx])
            # https://arrow.apache.org/docs/cpp/parquet.html#encodings
            # https://arrow.apache.org/docs/python/generated/pyarrow.parquet.write_table.html
            pq.write_table(filtered_table,
                           pq_test_file_path,
                           compression="SNAPPY",
                           version="2.6",
                           data_page_version="2.0",
                           use_dictionary="DICTIONARY",
                           data_page_size=16 * 256 * 1024)

            f.write("public_bi,{0},{1},0,{2},{3},{4}\n".format(dataset,
                                                               str(col_idx),
                                                               "DICTIONARY",
                                                               "SNAPPY",
                                                               str(get_file_size(pq_test_file_path))))

        ok(result_file_path + " has been successfully writen!")


def write_fls(csv_table, dataset, table_n, yaml_file):
    raise "Bind fastlanes to python"


def write_bb(csv_table, dataset, table_n, yaml_file):
    raise "Bind bb to python"


class FileFormat:
    result_dir_path = ""

    def __init__(self, name, ff_type, result_dir_path, rg_sz, write_fun):
        self.name = name
        self.type = ff_type
        self.result_dir_path = result_dir_path
        self.rg_sz = rg_sz
        self.write_fun = write_fun

    def compress(self, dataset, table_n, yaml_file):
        sed_csv_file_path = public_bi.get_sampled_dataset_file_path(dataset, table_n, self.rg_sz)
        if not os.path.exists(sed_csv_file_path):
            raise "FILE DOES NOT EXIST"

        csv_table = csv.read_csv(sed_csv_file_path, parse_options=csv.ParseOptions(delimiter="|"),
                                 read_options=csv.ReadOptions(autogenerate_column_names=True))

        self.write_fun(csv_table, dataset, table_n, yaml_file, self.result_dir_path)

    def get_result_dir_path(self):
        return self.result_dir_path


pq_dictionary_snappy_ff = FileFormat("PQ_DICTIONARY_SNAPPY", FileFormatT.PQ_DICTIONARY_SNAPPY,
                                     pq_dictionary_snappy_result_dir_path,
                                     64 * 1024,
                                     write_orc)
orc_snappy_ff = FileFormat("ORC", FileFormatT.ORC_SNAPPY, orc_result_dir_path, 64 * 1024, write_orc_snappy)
lwc_ff = FileFormat("LWC", FileFormatT.LWC, lwc_result_dir_path, 64 * 1024, write_orc)
fls_ff = FileFormat("FLS", FileFormatT.FLS, fls_result_dir_path, 64 * 1024, write_fls)
uncompressed_ff = FileFormat("UNCOMPRESSED", FileFormatT.UNCOMPRESSED,
                             uncompressed_result_dir_path,
                             64 * 1024,
                             write_fls)

fls_ccc_ff = FileFormat("FLS_CCC", FileFormatT.FLS_CCC, fls_ccc_result_dir_path, 64 * 1024, write_fls)
duckdb_ff = FileFormat("DUCKDB", FileFormatT.DUCKDB, duckdb_result_dir_path, 64 * 1024, write_duckdb)
bb_ff = FileFormat("BB", FileFormatT.BB, bb_result_dir_path, 64 * 1024, write_bb)
pq_dictionary_zstd_ff = FileFormat("PQ_DICTIONARY_ZSTD", FileFormatT.PQ_DICTIONARY_ZSTD,
                                   pq_dictionary_zstd_result_dir_path,
                                   64 * 1024,
                                   write_orc)

file_format_list = [
    fls_ff,
    fls_ccc_ff,
    pq_dictionary_snappy_ff,
    orc_snappy_ff,
    duckdb_ff,
    bb_ff,
    pq_dictionary_zstd_ff,
    lwc_ff,
    uncompressed_ff
    # FileFormat("orc_snappy", FileFormatT.ORC_SNAPPY, orc_result_dir_path, 64 * 1024),
]
