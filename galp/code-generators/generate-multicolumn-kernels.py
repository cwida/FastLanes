# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# galp/code-generators/generate-multicolumn-kernels.py
# ────────────────────────────────────────────────────────
#!/usr/bin/env python3

import os
import sys

import argparse
import logging

FILE_HEADER = """
#include "../flsgpu/flsgpu-api.cuh"
#include "../engine/device-utils.cuh"

#ifndef MULTI_COLUMN_DEVICE_KERNELS_CUH
#define MULTI_COLUMN_DEVICE_KERNELS_CUH

namespace multi_column {
"""

FILE_FOOTER = """
}
#endif // MULTI_COLUMN_DEVICE_KERNELS_CUH
"""

def generate_global_function(n_cols: int):
    col_range = range(n_cols)
    return "\n".join(
        [
            "template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>",
            "__global__ void query_multi_column("
            + ",".join([f"const ColumnT column_{i}" for i in col_range])
            + ", const T value, bool *out) {",
            f"constexpr int32_t N_COLS = {n_cols};",
            "const auto mapping = VectorToWarpMapping<T, UNPACK_N_VECS>();",
            "const int32_t vector_index = mapping.get_vector_index();",
            "const lane_t lane = mapping.get_lane();",
            f"T registers[UNPACK_N_VALUES * UNPACK_N_VECS * {n_cols}];",
            "bool all_columns_equal = true;",
            "\n".join(
                [
                    f"DecompressorT decompressor_{i} = DecompressorT(column_{i}, vector_index, lane);"
                    for i in col_range
                ]
            ),
            "for (si_t i{0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {",
            "\n".join(
                [
                    f"decompressor_{i}.unpack_next_into(registers + {i} * (UNPACK_N_VALUES * UNPACK_N_VECS));"
                    for i in col_range
                ]
            ),
            "#pragma unroll",
            "for (int c{1}; c < N_COLS; ++c) {",
            "#pragma unroll",
            "for (int va{0}; va < UNPACK_N_VALUES; ++va) {",
            "#pragma unroll",
            "for (int v{0}; v < UNPACK_N_VECS; ++v) {",
            "all_columns_equal &= registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] == registers[va + v * UNPACK_N_VALUES + (c-1) * UNPACK_N_VECS * UNPACK_N_VALUES];",
            "}",
            "}",
            "}",
            "#pragma unroll",
            "for (int va{0}; va < UNPACK_N_VALUES; ++va) {",
            "#pragma unroll",
            "for (int v{0}; v < UNPACK_N_VECS; ++v) {",
            "all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;",
            "}",
            "}",
            "}",
            "",
            "if (all_columns_equal) {",
            "*out = true;",
            "}}",
        ]
    )


def main(args):
    n_cols = 10
    generated_str = "\n\n".join(
        [
            FILE_HEADER,
            *[generate_global_function(n) for n in range(1, n_cols + 1)],
            FILE_FOOTER,
        ]
    )

    with open("src/generated-bindings/multi-column-device-kernels.cuh", "w") as file:
        file.write(generated_str)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog="program")

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
