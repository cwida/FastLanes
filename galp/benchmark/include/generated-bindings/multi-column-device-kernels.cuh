// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/include/generated-bindings/multi-column-device-kernels.cuh
// ────────────────────────────────────────────────────────
#ifndef MULTI_COLUMN_DEVICE_KERNELS_CUH
#define MULTI_COLUMN_DEVICE_KERNELS_CUH

#include "engine/device-utils.cuh"
#include "flsgpu/flsgpu-api.cuh"

namespace multi_column {

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0, const T value, bool* out) {
	constexpr int32_t N_COLS       = 1;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 1];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0, const ColumnT column_1, const T value, bool* out) {
	constexpr int32_t N_COLS       = 2;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 2];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void
query_multi_column(const ColumnT column_0, const ColumnT column_1, const ColumnT column_2, const T value, bool* out) {
	constexpr int32_t N_COLS       = 3;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 3];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0,
                                   const ColumnT column_1,
                                   const ColumnT column_2,
                                   const ColumnT column_3,
                                   const T       value,
                                   bool*         out) {
	constexpr int32_t N_COLS       = 4;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 4];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	DecompressorT     decompressor_3    = DecompressorT(column_3, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_3.unpack_next_into(registers + 3 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0,
                                   const ColumnT column_1,
                                   const ColumnT column_2,
                                   const ColumnT column_3,
                                   const ColumnT column_4,
                                   const T       value,
                                   bool*         out) {
	constexpr int32_t N_COLS       = 5;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 5];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	DecompressorT     decompressor_3    = DecompressorT(column_3, vector_index, lane);
	DecompressorT     decompressor_4    = DecompressorT(column_4, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_3.unpack_next_into(registers + 3 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_4.unpack_next_into(registers + 4 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0,
                                   const ColumnT column_1,
                                   const ColumnT column_2,
                                   const ColumnT column_3,
                                   const ColumnT column_4,
                                   const ColumnT column_5,
                                   const T       value,
                                   bool*         out) {
	constexpr int32_t N_COLS       = 6;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 6];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	DecompressorT     decompressor_3    = DecompressorT(column_3, vector_index, lane);
	DecompressorT     decompressor_4    = DecompressorT(column_4, vector_index, lane);
	DecompressorT     decompressor_5    = DecompressorT(column_5, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_3.unpack_next_into(registers + 3 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_4.unpack_next_into(registers + 4 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_5.unpack_next_into(registers + 5 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0,
                                   const ColumnT column_1,
                                   const ColumnT column_2,
                                   const ColumnT column_3,
                                   const ColumnT column_4,
                                   const ColumnT column_5,
                                   const ColumnT column_6,
                                   const T       value,
                                   bool*         out) {
	constexpr int32_t N_COLS       = 7;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 7];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	DecompressorT     decompressor_3    = DecompressorT(column_3, vector_index, lane);
	DecompressorT     decompressor_4    = DecompressorT(column_4, vector_index, lane);
	DecompressorT     decompressor_5    = DecompressorT(column_5, vector_index, lane);
	DecompressorT     decompressor_6    = DecompressorT(column_6, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_3.unpack_next_into(registers + 3 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_4.unpack_next_into(registers + 4 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_5.unpack_next_into(registers + 5 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_6.unpack_next_into(registers + 6 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0,
                                   const ColumnT column_1,
                                   const ColumnT column_2,
                                   const ColumnT column_3,
                                   const ColumnT column_4,
                                   const ColumnT column_5,
                                   const ColumnT column_6,
                                   const ColumnT column_7,
                                   const T       value,
                                   bool*         out) {
	constexpr int32_t N_COLS       = 8;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 8];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	DecompressorT     decompressor_3    = DecompressorT(column_3, vector_index, lane);
	DecompressorT     decompressor_4    = DecompressorT(column_4, vector_index, lane);
	DecompressorT     decompressor_5    = DecompressorT(column_5, vector_index, lane);
	DecompressorT     decompressor_6    = DecompressorT(column_6, vector_index, lane);
	DecompressorT     decompressor_7    = DecompressorT(column_7, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_3.unpack_next_into(registers + 3 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_4.unpack_next_into(registers + 4 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_5.unpack_next_into(registers + 5 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_6.unpack_next_into(registers + 6 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_7.unpack_next_into(registers + 7 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0,
                                   const ColumnT column_1,
                                   const ColumnT column_2,
                                   const ColumnT column_3,
                                   const ColumnT column_4,
                                   const ColumnT column_5,
                                   const ColumnT column_6,
                                   const ColumnT column_7,
                                   const ColumnT column_8,
                                   const T       value,
                                   bool*         out) {
	constexpr int32_t N_COLS       = 9;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 9];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	DecompressorT     decompressor_3    = DecompressorT(column_3, vector_index, lane);
	DecompressorT     decompressor_4    = DecompressorT(column_4, vector_index, lane);
	DecompressorT     decompressor_5    = DecompressorT(column_5, vector_index, lane);
	DecompressorT     decompressor_6    = DecompressorT(column_6, vector_index, lane);
	DecompressorT     decompressor_7    = DecompressorT(column_7, vector_index, lane);
	DecompressorT     decompressor_8    = DecompressorT(column_8, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_3.unpack_next_into(registers + 3 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_4.unpack_next_into(registers + 4 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_5.unpack_next_into(registers + 5 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_6.unpack_next_into(registers + 6 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_7.unpack_next_into(registers + 7 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_8.unpack_next_into(registers + 8 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__global__ void query_multi_column(const ColumnT column_0,
                                   const ColumnT column_1,
                                   const ColumnT column_2,
                                   const ColumnT column_3,
                                   const ColumnT column_4,
                                   const ColumnT column_5,
                                   const ColumnT column_6,
                                   const ColumnT column_7,
                                   const ColumnT column_8,
                                   const ColumnT column_9,
                                   const T       value,
                                   bool*         out) {
	constexpr int32_t N_COLS       = 10;
	const auto        mapping      = VectorToWarpMapping<T, UNPACK_N_VECS>();
	const int32_t     vector_index = mapping.get_vector_index();
	const lane_t      lane         = mapping.get_lane();
	T                 registers[UNPACK_N_VALUES * UNPACK_N_VECS * 10];
	bool              all_columns_equal = true;
	DecompressorT     decompressor_0    = DecompressorT(column_0, vector_index, lane);
	DecompressorT     decompressor_1    = DecompressorT(column_1, vector_index, lane);
	DecompressorT     decompressor_2    = DecompressorT(column_2, vector_index, lane);
	DecompressorT     decompressor_3    = DecompressorT(column_3, vector_index, lane);
	DecompressorT     decompressor_4    = DecompressorT(column_4, vector_index, lane);
	DecompressorT     decompressor_5    = DecompressorT(column_5, vector_index, lane);
	DecompressorT     decompressor_6    = DecompressorT(column_6, vector_index, lane);
	DecompressorT     decompressor_7    = DecompressorT(column_7, vector_index, lane);
	DecompressorT     decompressor_8    = DecompressorT(column_8, vector_index, lane);
	DecompressorT     decompressor_9    = DecompressorT(column_9, vector_index, lane);
	for (si_t i {0}; i < mapping.N_VALUES_IN_LANE; i += UNPACK_N_VALUES) {
		decompressor_0.unpack_next_into(registers + 0 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_1.unpack_next_into(registers + 1 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_2.unpack_next_into(registers + 2 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_3.unpack_next_into(registers + 3 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_4.unpack_next_into(registers + 4 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_5.unpack_next_into(registers + 5 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_6.unpack_next_into(registers + 6 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_7.unpack_next_into(registers + 7 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_8.unpack_next_into(registers + 8 * (UNPACK_N_VALUES * UNPACK_N_VECS));
		decompressor_9.unpack_next_into(registers + 9 * (UNPACK_N_VALUES * UNPACK_N_VECS));
#pragma unroll
		for (int c {1}; c < N_COLS; ++c) {
#pragma unroll
			for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
				for (int v {0}; v < UNPACK_N_VECS; ++v) {
					all_columns_equal &=
					    registers[va + v * UNPACK_N_VALUES + c * UNPACK_N_VECS * UNPACK_N_VALUES] ==
					    registers[va + v * UNPACK_N_VALUES + (c - 1) * UNPACK_N_VECS * UNPACK_N_VALUES];
				}
			}
		}
#pragma unroll
		for (int va {0}; va < UNPACK_N_VALUES; ++va) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECS; ++v) {
				all_columns_equal &= registers[va + v * UNPACK_N_VALUES] == value;
			}
		}
	}

	if (all_columns_equal) {
		*out = true;
	}
}

} // namespace multi_column
#endif // MULTI_COLUMN_DEVICE_KERNELS_CUH
