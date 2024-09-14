import os
from dataset_lib.log import *

sample_dir_path = "../FastLanes_Data/"
nextia_jd_dir_path = os.path.join(sample_dir_path, "NextiaJD")

# TEST_DIR_PATH
if "TEST_DIR_PATH" in os.environ:
    test_dir_path = os.environ['TEST_DIR_PATH']
else:
    error("TEST_DIR_PATH is not set!")
    exit()

# PQ_RESULT_DIR_PATH
if "PQ_D_S_RESULT_DIR_PATH" in os.environ:
    pq_dictionary_snappy_result_dir_path = os.environ['PQ_D_S_RESULT_DIR_PATH']
else:
    error("PQ_D_S_RESULT_DIR_PATH is not set!")
    exit()

# PQ_RESULT_DIR_PATH
if "PQ_D_Z_RESULT_DIR_PATH" in os.environ:
    pq_dictionary_zstd_result_dir_path = os.environ['PQ_D_Z_RESULT_DIR_PATH']
else:
    error("PQ_D_Z_RESULT_DIR_PATH is not set!")
    exit()

# FLS_RESULT_DIR_PATH
if "FLS_RESULT_DIR_PATH" in os.environ:
    fls_result_dir_path = os.environ['FLS_RESULT_DIR_PATH']
else:
    error("FLS_RESULT_DIR_PATH is not set!")
    exit()

# FLS_CCC_RESULT_DIR_PATH
if "FLS_CCC_RESULT_DIR_PATH" in os.environ:
    fls_ccc_result_dir_path = os.environ['FLS_CCC_RESULT_DIR_PATH']
else:
    error("FLS_CCC_RESULT_DIR_PATH is not set!")
    exit()

# FLS_CCC_RESULT_DIR_PATH
if "CCC_RESULT_DIR_PATH" in os.environ:
    ccc_result_dir_path = os.environ['CCC_RESULT_DIR_PATH']
else:
    error("CCC_RESULT_DIR_PATH is not set!")
    exit()

# ORC_RESULT_DIR_PATH
if "ORC_RESULT_DIR_PATH" in os.environ:
    orc_result_dir_path = os.environ['ORC_RESULT_DIR_PATH']
else:
    error("ORC_RESULT_DIR_PATH is not set!")
    exit()

# DUCKDB_RESULT_DIR_PATH
if "DUCKDB_RESULT_DIR_PATH" in os.environ:
    duckdb_result_dir_path = os.environ['DUCKDB_RESULT_DIR_PATH']
else:
    error("DUCKDB_RESULT_DIR_PATH is not set!")
    exit()

# BB_RESULT_DIR_PATH
if "BB_RESULT_DIR_PATH" in os.environ:
    bb_result_dir_path = os.environ['BB_RESULT_DIR_PATH']
else:
    error("BB_RESULT_DIR_PATH is not set!")
    exit()

# LWC_RESULT_DIR_PATH
if "LWC_RESULT_DIR_PATH" in os.environ:
    lwc_result_dir_path = os.environ['LWC_RESULT_DIR_PATH']
else:
    error("LWC_RESULT_DIR_PATH is not set!")
    exit()

# VS_RESULT_DIR_PATH
if "VS_RESULT_DIR_PATH" in os.environ:
    vs_result_dir_path = os.environ['VS_RESULT_DIR_PATH']
else:
    error("VS_RESULT_DIR_PATH is not set!")
    exit()

# UNCOMPRESSED_RESULT_DIR_PATH
if "UNCOMPRESSED_RESULT_DIR_PATH" in os.environ:
    uncompressed_result_dir_path = os.environ['UNCOMPRESSED_RESULT_DIR_PATH']
else:
    error("UNCOMPRESSED_RESULT_DIR_PATH is not set!")
    exit()

# FLS_VS_PQ_RESULT_DIR_PATH
if "FLS_VS_PQ_RESULT_DIR_PATH" in os.environ:
    fls_vs_pq_result_dir_path = os.environ['FLS_VS_PQ_RESULT_DIR_PATH']
else:
    error("FLS_VS_PQ_RESULT_DIR_PATH is not set!")
    exit()
