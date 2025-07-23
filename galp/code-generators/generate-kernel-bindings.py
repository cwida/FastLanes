# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# galp/code-generators/generate-kernel-bindings.py
# ────────────────────────────────────────────────────────
#!/usr/bin/python3

import os
import sys

import argparse
import logging

GENERATED_BINDINGS_DIR = "./src/generated-bindings/"

FILE_HEADER = """
#include <stdexcept>

#include "kernel-bindings.cuh"
#include "../engine/kernels.cuh"
#include "../engine/multi-column-host-kernels.cuh"

namespace bindings{
"""

FILE_FOOTER = """
}
"""


DATA_TYPES = [
    "uint32_t",
    "uint64_t",
    "float",
    "double",
]

FUNCTIONS = [
    "decompress_column",
    "query_column",
    "compute_column",
    "query_multi_column",
]

ENCODINGS = [
    "BP",
    "FFOR",
    "ALP",
    "ALPExtended",
]

UNPACKERS = [
    "Dummy",
    "OldFls",
    #"SwitchCase",
    #"Stateless",
    #"StatelessBranchless",
    #"StatefulCache",
    #"StatefulLocal1",
    #"StatefulLocal2",
    #"StatefulLocal4",
    #"StatefulShared1",
    #"StatefulShared2",
    #"StatefulShared4",
    #"StatefulRegister1",
    #"StatefulRegister2",
    #"StatefulRegister4",
    #"StatefulRegisterBranchless1",
    #"StatefulRegisterBranchless2",
    #"StatefulRegisterBranchless4",
    "StatefulBranchless",
]
MULTI_COLUMN_UNPACKERS = [
    UNPACKERS[1],
    UNPACKERS[2],
]

PATCHERS = [
    "None",
    "Dummy",
    "Stateless",
    "Stateful",
    "Naive",
    "NaiveBranchless",
    "PrefetchAll",
    "PrefetchAllBranchless",
]
MULTI_COLUMN_PATCHERS = [
    PATCHERS[0],
    PATCHERS[3],
    PATCHERS[4],
    PATCHERS[5],
    PATCHERS[6],
    PATCHERS[7],
]


def get_column_t(
    encoding: str, data_type: str, function: str, for_decompressor: bool = False
) -> str:
    column_t = f"BPColumn<{data_type}>"
    if "FFOR" in encoding:
        column_t = f"FFORColumn<{data_type}>"
    elif "ALPExtended" in encoding:
        column_t = f"ALPExtendedColumn<{data_type}>"
    elif "ALP" in encoding:
        column_t = f"ALPColumn<{data_type}>"
    return (
        "flsgpu::device::"
        if function != "query_multi_column" or for_decompressor
        else "flsgpu::host::"
    ) + column_t


def get_decompressor_type(
    encoding: str,
    data_type: str,
    function: str,
    unpacker: str,
    patcher: str,
    n_vec: int,
    n_val: int,
) -> str:
    column_t = get_column_t(encoding, data_type, function, True)
    functor = f"BPFunctor<{data_type}>"
    patcher_t = f""
    decompressor_t = f"{encoding}Decompressor"
    if "FFOR" in encoding:
        functor = f"FFORFunctor<{data_type}, {n_vec}>"
    elif "ALPExtended" in encoding:
        functor = f"ALPFunctor<{data_type}, {n_vec}>"
        patcher_t = f"flsgpu::device::{patcher}ALPExceptionPatcher<{data_type}, {n_vec}, {n_val}>,"
        decompressor_t = "ALPDecompressor"
    elif "ALP" in encoding:
        functor = f"ALPFunctor<{data_type}, {n_vec}>"
        patcher_t = f"flsgpu::device::{patcher}ALPExceptionPatcher<{data_type}, {n_vec}, {n_val}>,"

    loader_t = ""
    if "Stateful" in unpacker and "StatefulBranchless" not in unpacker:
        loader_t = ", flsgpu::device::"
        if "Cache" in unpacker:
            loader_t += f"CacheLoader<{data_type}, {n_vec}>"
        elif "Local" in unpacker:
            loader_t += f"LocalMemoryLoader<{data_type}, {n_vec}, {unpacker[-1]}>"
        elif "Shared" in unpacker:
            loader_t += f"SharedMemoryLoader<{data_type}, {n_vec}, {unpacker[-1]}>"
        elif "RegisterBranchless" in unpacker:
            loader_t += (
                f"RegisterBranchlessLoader<{data_type}, {n_vec}, {unpacker[-1]}>"
            )
        elif "Register" in unpacker:
            loader_t += f"RegisterLoader<{data_type}, {n_vec}, {unpacker[-1]}>"
        unpacker = "Stateful"

    unpacker_t = f"flsgpu::device::BitUnpacker{unpacker}<{data_type}, {n_vec}, {n_val},  flsgpu::device::{functor} {loader_t}>"

    return f"flsgpu::device::{decompressor_t}<{data_type}, {n_vec}, {unpacker_t}, {patcher_t} {column_t}>"


def get_if_statement(
    encoding: str,
    data_type: str,
    function: str,
    n_vec: int,
    n_val: int,
    unpacker: str,
    patcher: str,
    is_query_column: bool = False,
    n_columns: int | None = None,
    n_repetitions: int | None = None,
) -> str:
    assert data_type in DATA_TYPES
    assert function in FUNCTIONS
    assert n_vec in [1, 2, 4, 8]
    assert n_val in [1, 32]
    assert unpacker in UNPACKERS
    assert patcher in PATCHERS

    column_t = get_column_t(encoding, data_type, function)
    decompressor_t = get_decompressor_type(
        encoding, data_type, function, unpacker, patcher, n_vec, n_val
    )
    extra_param = (
        "," + str(n_columns)
        if n_columns
        else ", magic_value" if is_query_column else ""
    )
    return (
        f"if (unpack_n_vectors == {n_vec} && unpack_n_values == {n_val} && unpacker == enums::Unpacker::{unpacker} && patcher == enums::Patcher::{patcher} {'&& n_columns == ' + str(n_columns) if n_columns else ''}) "
        + "{"  # }
        f"return kernels::host::{function}<{data_type}, {n_vec}, {n_val}, {decompressor_t}, {column_t} {',' + str(n_repetitions) if n_repetitions else ''}>(column {extra_param}, n_samples);"
        "}"
    )


def get_function(
    encoding: str,
    data_type: str,
    function: str,
    return_type: str,
    content: list[str],
    is_query_column: bool = False,
    is_multi_column: bool = False,
    is_compute_column: bool = False,
) -> str:
    assert not (is_multi_column and is_compute_column)
    column_t = get_column_t(encoding, data_type, function)
    return (
        f"template<> {return_type} {function}<{data_type},{column_t}>(const {column_t} column, const unsigned unpack_n_vectors, const unsigned unpack_n_values, const enums::Unpacker unpacker, const enums::Patcher patcher {', const ' + data_type + ' magic_value' if is_query_column or is_multi_column else ''}{', const unsigned n_repetitions' if is_compute_column else ''}, const uint32_t n_samples)"
        + "{"
        + "\n".join(content)
        + f'throw std::invalid_argument("Could not find correct binding in {function} {encoding}<{data_type}>");'
        + "}"
    )


def write_file(
    file_name: str,
    functions: list[str],
):
    logging.info(f"Writing file {file_name}")
    with open(os.path.join(GENERATED_BINDINGS_DIR, file_name), "w") as f:
        f.write("\n".join([FILE_HEADER] + functions + [FILE_FOOTER]))


def get_if_statement_check_wrapper(
    disable_unnecessary: bool,
    encoding: str,
    data_type: str,
    function: str,
    n_vec: int,
    n_val: int,
    unpacker: str,
    patcher: str,
    is_query_column: bool = False,
    n_columns: int | None = None,
    n_repetitions: int | None = None,
) -> str:
    # du handling
    is_necessary = (
        data_type == "float"
        and function == "decompress_column"
        and unpacker == "OldFls"
    )

    # OldFls handling
    if unpacker == "OldFls":
        n_val = 32

    # Filters
    unnessary_filter = disable_unnecessary and not is_necessary
    switch_case_filter = unpacker == "SwitchCase" and (
        n_vec != 1
        or n_val != 1
        or "uint" not in data_type
        or function == "compute_column"
    )
    multi_column_filter = function == "query_multi_column" and (
        unpacker not in MULTI_COLUMN_UNPACKERS
        or patcher not in MULTI_COLUMN_PATCHERS
        or args.disable_multi_column
    )
    old_fls_filter = unpacker == "OldFls" and (
        n_vec != 1 or data_type not in ["uint32_t", "float"]
    )

    is_filtered = (
        unnessary_filter or switch_case_filter or multi_column_filter or old_fls_filter
    )
    if is_filtered:
        return ""

    return get_if_statement(
        encoding,
        data_type,
        function,
        n_vec,
        n_val,
        unpacker,
        patcher,
        is_query_column,
        n_columns,
        n_repetitions,
    )


def main(args):
    for encoding in ["BP", "FFOR"]:
        for data_type in ["uint32_t", "uint64_t"]:
            for binding, is_query_column in zip(
                ["decompress_column", "query_column"], [False, True]
            ):
                write_file(
                    f"{encoding.lower()}-{data_type}-{binding}-bindings.cu",
                    [
                        get_function(
                            encoding,
                            data_type,
                            binding,
                            "bool" if is_query_column else data_type + "*",
                            [
                                get_if_statement_check_wrapper(
                                    args.disable_unnecessary,
                                    encoding,
                                    data_type,
                                    binding,
                                    n_vec,
                                    n_val,
                                    unpacker,
                                    "None",
                                    is_query_column=is_query_column,
                                )
                                for n_vec in [1, 4]
                                for n_val in [1]
                                for unpacker in UNPACKERS
                            ],
                            is_query_column=is_query_column,
                        )
                    ],
                )

    for encoding in ["FFOR"]:
        for data_type in ["uint32_t", "uint64_t"]:
            for binding in ["query_multi_column", "compute_column"]:
                is_compute_column = binding == "compute_column"
                is_multi_column = binding == "query_multi_column"
                write_file(
                    f"{encoding.lower()}-{data_type}-{binding}-bindings.cu",
                    [
                        get_function(
                            encoding,
                            data_type,
                            binding,
                            "bool",
                            [
                                get_if_statement_check_wrapper(
                                    args.disable_unnecessary,
                                    encoding,
                                    data_type,
                                    binding,
                                    n_vec,
                                    n_val,
                                    unpacker,
                                    "None",
                                    n_repetitions=10 if is_compute_column else None,
                                    is_query_column=is_multi_column,
                                )
                                for n_vec in [1, 4]
                                for n_val in [1]
                                for unpacker in UNPACKERS
                            ],
                            is_multi_column=is_multi_column,
                            is_compute_column=is_compute_column,
                        )
                    ],
                )

    for encoding, patchers_per_encoding in zip(
        ["ALP", "ALPExtended"], [PATCHERS[1:4], PATCHERS[4:]]
    ):
        for data_type in ["float", "double"]:
            for binding in ["decompress_column", "query_column", "query_multi_column"]:
                is_query_column = binding == "query_column"
                is_multi_column = binding == "query_multi_column"
                write_file(
                    f"{encoding.lower()}-{data_type}-{binding}-bindings.cu",
                    [
                        get_function(
                            encoding,
                            data_type,
                            binding,
                            (
                                "bool"
                                if is_query_column or is_multi_column
                                else data_type + "*"
                            ),
                            [
                                get_if_statement_check_wrapper(
                                    args.disable_unnecessary,
                                    encoding,
                                    data_type,
                                    binding,
                                    n_vec,
                                    n_val,
                                    unpacker,
                                    patcher,
                                    is_query_column=is_query_column or is_multi_column,
                                    n_repetitions=None,
                                )
                                for n_vec in [1, 4]
                                for n_val in [1]
                                for unpacker in UNPACKERS[1:]
                                for patcher in patchers_per_encoding
                            ],
                            is_query_column=is_query_column,
                            is_multi_column=is_multi_column,
                        )
                    ],
                )


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog="program")

    parser.add_argument(
        "-du",
        "--disable-unnecessary",
        type=bool,
        default=False,
        action=argparse.BooleanOptionalAction,
    )
    parser.add_argument(
        "-dmc",
        "--disable-multi-column",
        type=bool,
        default=False,
        action=argparse.BooleanOptionalAction,
    )
    parser.add_argument(
        "-ll",
        "--logging-level",
        type=int,
        default=logging.INFO,
        choices=[logging.CRITICAL, logging.ERROR, logging.INFO, logging.DEBUG],
        help=f"logging level to use: {logging.CRITICAL}=CRITICAL, {logging.ERROR}=ERROR, {logging.INFO}=INFO, "
        + f"{logging.DEBUG}=DEBUG, higher number means less output",
    )

    args = parser.parse_args()
    logging.basicConfig(level=args.logging_level)  # filename='program.log',
    logging.info(
        f"Started {os.path.basename(sys.argv[0])} with the following args: {args}"
    )
    main(args)
