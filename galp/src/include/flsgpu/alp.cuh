// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/flsgpu/alp.cuh
// ────────────────────────────────────────────────────────
#ifndef ALP_CUH
#define ALP_CUH

#include "fls.cuh"
#include "structs.cuh"
#include <cstdint>
#include <cstdio>
#include <type_traits>

namespace flsgpu { namespace device {

template <typename T, unsigned UNPACK_N_VECTORS>
struct ALPFunctor : FunctorBase<T> {
private:
	using INT_T  = typename utils::same_width_int<T>::type;
	using UINT_T = typename utils::same_width_uint<T>::type;

	UINT_T bases[UNPACK_N_VECTORS];
	INT_T  factor[UNPACK_N_VECTORS];
	T      frac10[UNPACK_N_VECTORS];

public:
	__device__ __forceinline__ ALPFunctor(const UINT_T*  a_bases,
	                                      const INT_T*   factors,
	                                      const uint8_t* factor_indices,
	                                      const T*       fractions,
	                                      const uint8_t* fraction_indices) {
#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			bases[v]  = a_bases[v];
			factor[v] = factors[factor_indices[v]];
			frac10[v] = fractions[fraction_indices[v]];
		}
	}

	__device__ __forceinline__ T operator()(const UINT_T value, const vi_t vector_index) override {
		return static_cast<T>(static_cast<INT_T>((value + bases[vector_index]) * factor[vector_index])) *
		       frac10[vector_index];
	}
};

template <typename T>
struct ALPExceptionPatcherBase {
public:
	virtual void __device__ __forceinline__ patch_if_needed(T* out);
};

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct DummyALPExceptionPatcher : flsgpu::device::ALPExceptionPatcherBase<T> {

public:
	void __device__ __forceinline__ patch_if_needed(T* out) override {
	}

	__device__ __forceinline__
	DummyALPExceptionPatcher(const flsgpu::device::ALPColumn<T> column, const vi_t vector_index, const lane_t lane) {
	}
};

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct StatelessALPExceptionPatcher : ALPExceptionPatcherBase<T> {
	using INT_T = typename utils::same_width_int<T>::type;

	si_t         start_index = 0;
	uint16_t     exceptions_count[UNPACK_N_VECTORS];
	uint16_t*    vec_exceptions_positions[UNPACK_N_VECTORS];
	T*           vec_exceptions[UNPACK_N_VECTORS];
	const lane_t lane;

public:
	void __device__ __forceinline__ patch_if_needed(T* out) override {
		constexpr auto N_LANES = utils::get_n_lanes<INT_T>();

		const int first_pos = start_index * N_LANES + lane;
		const int last_pos  = first_pos + N_LANES * (UNPACK_N_VALUES - 1);

		start_index += UNPACK_N_VALUES;

#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			for (int i {0}; i < exceptions_count[v]; i++) {
				auto position  = vec_exceptions_positions[v][i];
				auto exception = vec_exceptions[v][i];
				if (position >= first_pos) {
					if (position <= last_pos && position % N_LANES == lane) {
						out[(position - first_pos) / N_LANES + v * UNPACK_N_VALUES] = exception;
					}
					if (position + 1 > last_pos) {
						break;
					}
				}
			}
		}
	}

	__device__ __forceinline__
	StatelessALPExceptionPatcher(const ALPColumn<T> column, const vi_t first_vector_index, const lane_t lane)
	    : lane(lane) {

#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			auto vec_index              = first_vector_index + v;
			exceptions_count[v]         = column.counts[vec_index];
			vec_exceptions_positions[v] = column.positions + column.exceptions_offsets[vec_index];
			vec_exceptions[v]           = column.exceptions + column.exceptions_offsets[vec_index];
		}
	}
};

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct StatefulALPExceptionPatcher : ALPExceptionPatcherBase<T> {
	using INT_T = typename utils::same_width_int<T>::type;

	si_t         start_index = 0;
	uint16_t     exceptions_count[UNPACK_N_VECTORS];
	uint16_t*    vec_exceptions_positions[UNPACK_N_VECTORS];
	T*           vec_exceptions[UNPACK_N_VECTORS];
	const lane_t lane;
	int32_t      exception_index[UNPACK_N_VECTORS] = {0};

public:
	void __device__ __forceinline__ patch_if_needed(T* out) override {
		constexpr auto N_LANES = utils::get_n_lanes<INT_T>();

		const int first_pos = start_index * N_LANES + lane;
		const int last_pos  = first_pos + N_LANES * (UNPACK_N_VALUES - 1);
		start_index += UNPACK_N_VALUES;

#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			for (; exception_index[v] < exceptions_count[v]; exception_index[v]++) {
				auto position  = vec_exceptions_positions[v][exception_index[v]];
				auto exception = vec_exceptions[v][exception_index[v]];
				if (position >= first_pos) {
					if (position <= last_pos && position % N_LANES == lane) {
						out[(position - first_pos) / N_LANES + v * UNPACK_N_VALUES] = exception;
					}
					if (position + 1 > last_pos) {
						break;
					}
				}
			}
		}
	}

	__device__ __forceinline__
	StatefulALPExceptionPatcher(const ALPColumn<T> column, const vi_t first_vector_index, const lane_t lane)
	    : lane(lane) {

#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			auto vec_index              = first_vector_index + v;
			exceptions_count[v]         = column.counts[vec_index];
			vec_exceptions_positions[v] = column.positions + column.exceptions_offsets[vec_index];
			vec_exceptions[v]           = column.exceptions + column.exceptions_offsets[vec_index];
		}
	}
};

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct NaiveALPExceptionPatcher : ALPExceptionPatcherBase<T> {
private:
	uint16_t  count[UNPACK_N_VECTORS];
	uint16_t* positions[UNPACK_N_VECTORS];
	T*        exceptions[UNPACK_N_VECTORS];
	uint16_t  current_position;

public:
	__device__ __forceinline__
	NaiveALPExceptionPatcher(const ALPExtendedColumn<T> column, const vi_t vector_index, const lane_t lane)
	    : current_position(lane) {
#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			const vi_t current_vector_index = vector_index + v;

			const auto offset_count = column.offsets_counts[current_vector_index * utils::get_n_lanes<T>() + lane];
			count[v]                = offset_count >> 10;

			const auto offset = (offset_count & 0x3FF);
			positions[v]      = column.positions + column.exceptions_offsets[current_vector_index] + offset;
			exceptions[v]     = column.exceptions + column.exceptions_offsets[current_vector_index] + offset;
		}
	}

	void __device__ __forceinline__ patch_if_needed(T* out) override {
#pragma unroll
		for (int w {0}; w < UNPACK_N_VALUES; ++w) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
				if (count[v] > 0 && current_position == *(positions[v])) {
					out[v * UNPACK_N_VALUES + w] = *(exceptions[v]);
					++(positions[v]);
					++(exceptions[v]);
					--(count[v]);
				}
			}
			current_position += utils::get_n_lanes<T>();
		}
	}
};

template <typename ToT, typename FromT>
constexpr ToT __device__ __forceinline__ reinterpret_as(FromT value) {
	ToT* ptr = reinterpret_cast<ToT*>(&value);
	return *ptr;
}

template <typename T>
constexpr void __device__ __forceinline__
overwrite_if_true(T* __restrict buffer, const T* __restrict new_value, const bool condition) {
	using UINT_T = typename utils::same_width_uint<T>::type;
	*buffer      = reinterpret_as<T>((reinterpret_as<UINT_T>(*buffer) * (!condition)) |
                                (reinterpret_as<UINT_T>(*new_value) * condition));
}

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct NaiveBranchlessALPExceptionPatcher : ALPExceptionPatcherBase<T> {
private:
	using UINT_T = typename utils::same_width_uint<T>::type;
	uint16_t  count[UNPACK_N_VECTORS];
	uint16_t* positions[UNPACK_N_VECTORS];
	T*        exceptions[UNPACK_N_VECTORS];
	uint16_t  next_position;
	uint16_t  current_position;

public:
	__device__ __forceinline__
	NaiveBranchlessALPExceptionPatcher(const ALPExtendedColumn<T> column, const vi_t vector_index, const lane_t lane)
	    : current_position(lane) {
#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			const vi_t current_vector_index = vector_index + v;

			const auto offset_count = column.offsets_counts[current_vector_index * utils::get_n_lanes<T>() + lane];
			count[v]                = offset_count >> 10;

			const auto exceptions_offset = column.exceptions_offsets[current_vector_index];
			const auto lane_offset       = (offset_count & 0x3FF);

			positions[v]  = column.positions + exceptions_offset + lane_offset;
			exceptions[v] = column.exceptions + exceptions_offset + lane_offset;
		}
	}

	void __device__ __forceinline__ patch_if_needed(T* out) override {
#pragma unroll
		for (int w {0}; w < UNPACK_N_VALUES; ++w) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
				// It is possible to easily prefetch *positions[v] here
				bool comp = (count[v] > 0) && (current_position == (*positions[v]));
				overwrite_if_true<T>(&out[v * UNPACK_N_VALUES + w], exceptions[v], comp);
				positions[v] += comp;
				exceptions[v] += comp;
				count[v] -= comp;
			}
			current_position += utils::get_n_lanes<T>();
		}
	}
};

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct PrefetchPositionALPExceptionPatcher : ALPExceptionPatcherBase<T> {
private:
	uint16_t  count[UNPACK_N_VECTORS];
	uint16_t* positions[UNPACK_N_VECTORS];
	T*        exceptions[UNPACK_N_VECTORS];
	uint16_t  next_position[UNPACK_N_VECTORS];
	uint16_t  position;

public:
	__device__ __forceinline__ PrefetchPositionALPExceptionPatcher(const ALPExtendedColumn<T> column,
	                                                               const vi_t                 first_vector_index,
	                                                               const lane_t               lane)
	    : position(lane) {
#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			const vi_t vector_index = first_vector_index + v;
			const auto offset_count = column.offsets_counts[vector_index * utils::get_n_lanes<T>() + lane];
			count[v]                = offset_count >> 10;

			const auto exceptions_offset = column.exceptions_offsets[vector_index];
			const auto lane_offset       = (offset_count & 0x3FF);
			positions[v]                 = column.positions + exceptions_offset + lane_offset;
			exceptions[v]                = column.exceptions + exceptions_offset + lane_offset;

			next_position[v] = *positions[v];
		}
	}

	void __device__ __forceinline__ patch_if_needed(T* out) override {
#pragma unroll
		for (int w {0}; w < UNPACK_N_VALUES; ++w) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
				if (count[v] > 0 && position == next_position[v]) {
					out[v * UNPACK_N_VALUES + w] = *exceptions[v];
					++positions[v];
					++exceptions[v];
					--count[v];
					next_position[v] = *positions[v];
				}
			}
			position += utils::get_n_lanes<T>();
		}
	}
};

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct PrefetchAllALPExceptionPatcher : ALPExceptionPatcherBase<T> {
private:
	uint16_t  count[UNPACK_N_VECTORS];
	uint16_t* positions[UNPACK_N_VECTORS];
	T*        exceptions[UNPACK_N_VECTORS];

	uint16_t index[UNPACK_N_VECTORS] = {0};
	uint16_t next_position[UNPACK_N_VECTORS];
	T        next_exception[UNPACK_N_VECTORS];
	uint16_t current_position;

public:
	void __device__ __forceinline__ read_next_exception(vi_t v) {
		if (index[v] < count[v]) {
			next_position[v]  = *positions[v];
			next_exception[v] = *exceptions[v];
			++positions[v];
			++exceptions[v];
			++index[v];
		} else {
			next_position[v] = consts::VALUES_PER_VECTOR;
		}
	}

	__device__ __forceinline__
	PrefetchAllALPExceptionPatcher(const ALPExtendedColumn<T> column, const vi_t first_vector_index, const lane_t lane)
	    : current_position(lane) {
		// Parse the data from the column
#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			const auto vector_index = first_vector_index + v;
			const auto offset_count = column.offsets_counts[vector_index * utils::get_n_lanes<T>() + lane];
			count[v]                = offset_count >> 10;

			const auto exceptions_offset = column.exceptions_offsets[vector_index];
			const auto lane_offset       = (offset_count & 0x3FF);
			positions[v]                 = column.positions + exceptions_offset + lane_offset;
			exceptions[v]                = column.exceptions + exceptions_offset + lane_offset;

			next_position[v]  = *positions[v];
			next_exception[v] = *exceptions[v];

			// This might be avoided to avoid a branch
			read_next_exception(v);
		}
	}

	void __device__ __forceinline__ patch_if_needed(T* out) override {
#pragma unroll
		for (int w {0}; w < UNPACK_N_VALUES; ++w) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
				if (current_position == next_position[v]) {
					out[v * UNPACK_N_VALUES + w] = next_exception[v];
					read_next_exception(v);
				}
			}
			current_position += utils::get_n_lanes<T>();
		}
	}
};

template <typename T, unsigned UNPACK_N_VECTORS, unsigned UNPACK_N_VALUES>
struct PrefetchAllBranchlessALPExceptionPatcher : ALPExceptionPatcherBase<T> {
private:
	uint16_t  count[UNPACK_N_VECTORS];
	uint16_t* positions[UNPACK_N_VECTORS];
	T*        exceptions[UNPACK_N_VECTORS];

	uint16_t index[UNPACK_N_VECTORS] = {0};
	uint16_t next_position[UNPACK_N_VECTORS];
	T        next_exception[UNPACK_N_VECTORS];
	uint16_t current_position;

public:
	void __device__ __forceinline__ read_next_exception() {
	}

	__device__ __forceinline__ PrefetchAllBranchlessALPExceptionPatcher(const ALPExtendedColumn<T> column,
	                                                                    const vi_t                 first_vector_index,
	                                                                    const lane_t               lane)
	    : current_position(lane) {
#pragma unroll
		for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
			const vi_t vector_index = first_vector_index + v;
			const auto offset_count = column.offsets_counts[vector_index * utils::get_n_lanes<T>() + lane];
			count[v]                = offset_count >> 10;

			const auto exceptions_offset = column.exceptions_offsets[vector_index];
			const auto lane_offset       = (offset_count & 0x3FF);
			positions[v]                 = column.positions + exceptions_offset + lane_offset;
			exceptions[v]                = column.exceptions + exceptions_offset + lane_offset;

			next_position[v]  = *positions[v];
			next_exception[v] = *exceptions[v];

			bool comparison = count[v] > 0;
			next_position[v] += (!comparison) * consts::VALUES_PER_VECTOR;
		}
	}

	void __device__ __forceinline__ patch_if_needed(T* out) override {
		// NOTES: It is probably possible to remove the next_position variable
		// as well as the next_exception, if you use prefetching. This would make
		// it easier to do multiple vectors.

#pragma unroll
		for (int w {0}; w < UNPACK_N_VALUES; ++w) {
#pragma unroll
			for (int v {0}; v < UNPACK_N_VECTORS; ++v) {
				bool comparison = current_position == next_position[v];
				overwrite_if_true<T>(out + v * UNPACK_N_VALUES + w, &next_exception[v], comparison);

				positions[v] += comparison;
				exceptions[v] += comparison;
				next_position[v]  = *positions[v];
				next_exception[v] = *exceptions[v];
				index[v] += comparison;

				comparison = index[v] < count[v];
				next_position[v] += (!comparison) * consts::VALUES_PER_VECTOR;
			}
			current_position += utils::get_n_lanes<T>();
		}
	}
};

template <typename T, unsigned UNPACK_N_VECTORS, typename UnpackerT, typename PatcherT, typename ColumnT>
struct ALPDecompressor : DecompressorBase<T> {
	UnpackerT unpacker;
	PatcherT  patcher;

	__device__ __forceinline__ ALPDecompressor(const ColumnT column, const vi_t vector_index, const lane_t lane)
	    : unpacker(column.ffor.bp.packed_array + column.ffor.bp.vector_offsets[vector_index],
	               lane,
	               column.ffor.bp.bit_widths[vector_index],
	               ALPFunctor<T, UNPACK_N_VECTORS>(column.ffor.bases + vector_index,
	                                               column.factors,
	                                               column.factor_indices + vector_index,
	                                               column.fractions,
	                                               column.fraction_indices + vector_index))
	    , patcher(PatcherT(column, vector_index, lane)) {
	}

	__device__ __forceinline__ void unpack_next_into(T* __restrict out) {
		unpacker.unpack_next_into(out);
		patcher.patch_if_needed(out);
	}
};

}}     // namespace flsgpu::device
#endif // ALP_CUH
