// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/flsgpu/structs.cuh
// ────────────────────────────────────────────────────────
#ifndef STRUCTS_CUH
#define STRUCTS_CUH

#include "alp.hpp"
#include "device-types.cuh"
#include "host-utils.cuh"
#include "utils.cuh"
#include <cstddef>
#include <cstdint>
#include <tuple>

namespace flsgpu {

namespace device {

template <typename T>
struct FunctorBase {
	using UINT_T = typename utils::same_width_uint<T>::type;

	virtual __device__ __forceinline__ T operator()(const UINT_T value, [[maybe_unused]] const vi_t vector_index);
};

template <typename T>
struct DecompressorBase {
	/* Constructor, cannot be enforced
  __device__ DecompressorBase(const ColumnT column,
  const vi_t vector_index, const lane_t lane)
  */

	virtual void __device__ unpack_next_into(T* __restrict out);
};

template <typename T>
struct BPColumn {
	using UINT_T = typename utils::same_width_uint<T>::type;
	size_t n_values;
	size_t n_vecs;

	UINT_T* packed_array;
	vbw_t*  bit_widths;
	size_t* vector_offsets;
};

template <typename T>
struct FFORColumn {
	using UINT_T = typename utils::same_width_uint<T>::type;
	size_t      n_values;
	BPColumn<T> bp;
	UINT_T*     bases;
};

template <typename T>
struct ALPColumn {
	using INT_T  = typename utils::same_width_int<T>::type;
	using UINT_T = typename utils::same_width_uint<T>::type;
	size_t             n_values;
	FFORColumn<UINT_T> ffor;

	INT_T*   factors;
	T*       fractions;
	uint8_t* factor_indices;
	uint8_t* fraction_indices;

	size_t    n_exceptions;
	size_t*   exceptions_offsets;
	T*        exceptions;
	uint16_t* positions;
	uint16_t* counts;
};

template <typename T>
struct ALPExtendedColumn {
	using INT_T  = typename utils::same_width_int<T>::type;
	using UINT_T = typename utils::same_width_uint<T>::type;
	size_t             n_values;
	FFORColumn<UINT_T> ffor;

	INT_T*   factors;
	T*       fractions;
	uint8_t* factor_indices;
	uint8_t* fraction_indices;

	size_t    n_exceptions;
	size_t*   exceptions_offsets;
	T*        exceptions;
	uint16_t* positions;
	uint16_t* offsets_counts;
};
} // namespace device

namespace host {

template <typename T>
struct BPColumn {
	using UINT_T        = typename utils::same_width_uint<T>::type;
	using DeviceColumnT = typename device::BPColumn<T>;

	size_t n_values;
	size_t n_packed_values;

	size_t get_n_values() const {
		return n_values;
	}
	size_t get_n_vecs() const {
		return utils::get_n_vecs_from_size(n_values);
	}

	UINT_T* packed_array;
	vbw_t*  bit_widths;
	size_t* vector_offsets;

	device::BPColumn<T> copy_to_device() const {
		const size_t branchless_extra_access_buffer = sizeof(T) * utils::get_n_lanes<T>() * 4;
		return device::BPColumn<T> {
		    n_values,
		    get_n_vecs(),
		    GPUArray<UINT_T>(n_packed_values, branchless_extra_access_buffer, packed_array).release(),
		    GPUArray<vbw_t>(get_n_vecs(), bit_widths).release(),
		    GPUArray<size_t>(get_n_vecs(), vector_offsets).release()};
	}
};

template <typename T>
struct FFORColumn {
	using UINT_T        = typename utils::same_width_uint<T>::type;
	using DeviceColumnT = typename device::FFORColumn<T>;

	BPColumn<T> bp;
	UINT_T*     bases;

	size_t get_n_values() const {
		return bp.n_values;
	}
	size_t get_n_vecs() const {
		return bp.get_n_vecs();
	}

	device::FFORColumn<T> copy_to_device() const {
		return device::FFORColumn<T> {
		    get_n_values(), bp.copy_to_device(), GPUArray<UINT_T>(bp.get_n_vecs(), bases).release()};
	}
};

template <typename T>
struct ALPExtendedColumn {
	using INT_T         = typename utils::same_width_int<T>::type;
	using UINT_T        = typename utils::same_width_uint<T>::type;
	using DeviceColumnT = typename device::ALPExtendedColumn<T>;

	FFORColumn<UINT_T> ffor;

	uint8_t* factor_indices;
	uint8_t* fraction_indices;

	size_t    n_exceptions;
	size_t*   exceptions_offsets;
	T*        exceptions;
	uint16_t* positions;
	uint16_t* offsets_counts;

	size_t compressed_size_bytes_alp_extended;

	size_t get_n_values() const {
		return ffor.bp.n_values;
	}
	size_t get_n_vecs() const {
		return ffor.bp.get_n_vecs();
	}

	double get_compression_ratio() const {
		return static_cast<double>(ffor.bp.n_values * sizeof(T)) /
		       static_cast<double>(compressed_size_bytes_alp_extended);
	}

	device::ALPExtendedColumn<T> copy_to_device() const {
		size_t branchless_and_prefetch_buffer = consts::MAX_UNPACK_N_VECS;
		return device::ALPExtendedColumn<T> {
		    get_n_values(),
		    ffor.copy_to_device(),
		    GPUArray<INT_T>(consts::as<T>::FACT_ARR_COUNT, alp::Constants<T>::FACT_ARR.data()).release(),
		    GPUArray<T>(consts::as<T>::FRAC_ARR_COUNT, alp::Constants<T>::FRAC_ARR.data()).release(),
		    GPUArray<uint8_t>(ffor.bp.get_n_vecs(), factor_indices).release(),
		    GPUArray<uint8_t>(ffor.bp.get_n_vecs(), fraction_indices).release(),
		    n_exceptions,
		    GPUArray<size_t>(ffor.bp.get_n_vecs(), exceptions_offsets).release(),
		    GPUArray<T>(n_exceptions, branchless_and_prefetch_buffer, exceptions).release(),
		    GPUArray<uint16_t>(n_exceptions, branchless_and_prefetch_buffer, positions).release(),
		    GPUArray<uint16_t>(ffor.bp.get_n_vecs() * utils::get_n_lanes<T>(), offsets_counts).release(),
		};
	}
};

template <typename T>
struct ALPColumn {
	using INT_T         = typename utils::same_width_int<T>::type;
	using UINT_T        = typename utils::same_width_uint<T>::type;
	using DeviceColumnT = typename device::ALPColumn<T>;

	FFORColumn<UINT_T> ffor;

	uint8_t* factor_indices;
	uint8_t* fraction_indices;

	size_t    n_exceptions;
	size_t*   exceptions_offsets;
	T*        exceptions;
	uint16_t* positions;
	uint16_t* counts;

	size_t compressed_size_bytes_alp;
	size_t compressed_size_bytes_alp_extended;

	size_t get_n_values() const {
		return ffor.bp.n_values;
	}
	size_t get_n_vecs() const {
		return ffor.bp.get_n_vecs();
	}

	double get_compression_ratio() const {
		return static_cast<double>(ffor.bp.n_values * sizeof(T)) / static_cast<double>(compressed_size_bytes_alp);
	}

	device::ALPColumn<T> copy_to_device() const {
		return device::ALPColumn<T> {
		    get_n_values(),
		    ffor.copy_to_device(),
		    GPUArray<INT_T>(consts::as<T>::FACT_ARR_COUNT, alp::Constants<T>::FACT_ARR.data()).release(),
		    GPUArray<T>(consts::as<T>::FRAC_ARR_COUNT, alp::Constants<T>::FRAC_ARR.data()).release(),
		    GPUArray<uint8_t>(ffor.bp.get_n_vecs(), factor_indices).release(),
		    GPUArray<uint8_t>(ffor.bp.get_n_vecs(), fraction_indices).release(),
		    n_exceptions,
		    GPUArray<size_t>(ffor.bp.get_n_vecs(), exceptions_offsets).release(),
		    GPUArray<T>(n_exceptions, exceptions).release(),
		    GPUArray<uint16_t>(n_exceptions, positions).release(),
		    GPUArray<uint16_t>(ffor.bp.get_n_vecs(), counts).release(),
		};
	}

	std::tuple<T*, uint16_t*, uint16_t*> convert_exceptions_to_lane_divided_format() const {
		constexpr auto N_LANES         = utils::get_n_lanes<T>();
		constexpr auto VALUES_PER_LANE = utils::get_values_per_lane<T>();

		// New exception allocations
		T*        out_exceptions = reinterpret_cast<T*>(malloc(sizeof(T) * n_exceptions));
		uint16_t* out_positions  = reinterpret_cast<uint16_t*>(malloc(sizeof(uint16_t) * n_exceptions));
		uint16_t* out_offsets_counts =
		    reinterpret_cast<uint16_t*>(malloc(sizeof(uint16_t) * ffor.get_n_vecs() * N_LANES));

		// Intermediate arrays for reordering positions and exceptions
		T        vec_exceptions[consts::VALUES_PER_VECTOR];
		T        vec_exceptions_positions[consts::VALUES_PER_VECTOR];
		uint16_t lane_counts[N_LANES];

		// Copies of pointers for pointer arithmetic
		T*        c_exceptions         = exceptions;
		uint16_t* c_positions          = positions;
		T*        c_out_exceptions     = out_exceptions;
		uint16_t* c_out_positions      = out_positions;
		uint16_t* c_out_offsets_counts = out_offsets_counts;

		for (size_t vec_index {0}; vec_index < ffor.get_n_vecs(); ++vec_index) {
			uint32_t vec_exception_count = counts[vec_index];

			// Reset counts
			for (size_t j {0}; j < N_LANES; ++j) {
				lane_counts[j] = 0;
			}

			// Split all exceptions into lanes
			for (size_t exception_index {0}; exception_index < vec_exception_count; ++exception_index) {
				T        exception = c_exceptions[exception_index];
				uint16_t position  = c_positions[exception_index];

				uint32_t lane                 = position % N_LANES;
				uint32_t lane_exception_count = lane_counts[lane];
				++lane_counts[lane];
				vec_exceptions[lane * VALUES_PER_LANE + lane_exception_count]           = exception;
				vec_exceptions_positions[lane * VALUES_PER_LANE + lane_exception_count] = position;
			}

			// Merge and concatenate all exceptions per lane into single contiguous
			// array
			uint32_t vec_exceptions_counter = 0;
			for (size_t lane {0}; lane < N_LANES; ++lane) {
				uint32_t exc_in_lane_count = lane_counts[lane];
				for (size_t exc_in_lane {0}; exc_in_lane < exc_in_lane_count; ++exc_in_lane) {

					c_out_exceptions[vec_exceptions_counter] = vec_exceptions[lane * VALUES_PER_LANE + exc_in_lane];
					c_out_positions[vec_exceptions_counter] =
					    vec_exceptions_positions[lane * VALUES_PER_LANE + exc_in_lane];
					++vec_exceptions_counter;
				}

				c_out_offsets_counts[lane] = (exc_in_lane_count << 10) | (vec_exceptions_counter - exc_in_lane_count);
			}

			c_exceptions += vec_exception_count;
			c_positions += vec_exception_count;
			c_out_exceptions += vec_exception_count;
			c_out_positions += vec_exception_count;
			c_out_offsets_counts += utils::get_n_lanes<T>();
		}

		return std::make_tuple(out_exceptions, out_positions, out_offsets_counts);
	}

	ALPExtendedColumn<T> create_extended_column() const {
		auto [e_exceptions, e_positions, e_offsets_counts] = convert_exceptions_to_lane_divided_format();
		return ALPExtendedColumn<T> {FFORColumn<UINT_T> {
		                                 BPColumn<UINT_T> {
		                                     ffor.bp.n_values,
		                                     ffor.bp.n_packed_values,
		                                     utils::copy_array(ffor.bp.packed_array, ffor.bp.n_packed_values),
		                                     utils::copy_array(ffor.bp.bit_widths, get_n_vecs()),
		                                     utils::copy_array(ffor.bp.vector_offsets, get_n_vecs()),
		                                 },
		                                 utils::copy_array(ffor.bases, get_n_vecs()),
		                             },
		                             utils::copy_array(factor_indices, get_n_vecs()),
		                             utils::copy_array(fraction_indices, get_n_vecs()),
		                             n_exceptions,
		                             utils::copy_array(exceptions_offsets, get_n_vecs()),
		                             e_exceptions,
		                             e_positions,
		                             e_offsets_counts,
		                             compressed_size_bytes_alp_extended};
	}
};

template <typename T>
void free_column(BPColumn<T> column) {
	delete[] column.packed_array;
	delete[] column.bit_widths;
	delete[] column.vector_offsets;
}

template <typename T>
void free_column(FFORColumn<T> column) {
	free_column(column.bp);
	delete[] column.bases;
}

template <typename T>
void free_column(ALPColumn<T> column) {
	free_column(column.ffor);
	delete[] column.factor_indices;
	delete[] column.fraction_indices;
	delete[] column.exceptions_offsets;
	delete[] column.exceptions;
	delete[] column.positions;
	delete[] column.counts;
}

template <typename T>
void free_column(ALPExtendedColumn<T> column) {
	free_column(column.ffor);
	delete[] column.factor_indices;
	delete[] column.fraction_indices;
	delete[] column.exceptions_offsets;
	delete[] column.exceptions;
	delete[] column.positions;
	delete[] column.offsets_counts;
}

// Structs that are passed to the GPU cannot contain methods,
// that is why there is a separate method for the destructors
template <typename T>
void free_column(device::BPColumn<T> column) {
	free_device_pointer(column.packed_array);
	free_device_pointer(column.bit_widths);
	free_device_pointer(column.vector_offsets);
}

template <typename T>
void free_column(device::FFORColumn<T> column) {
	free_column(column.bp);
	free_device_pointer(column.bases);
}

template <typename T>
void free_column(device::ALPColumn<T> column) {
	free_column(column.ffor);
	free_device_pointer(column.factors);
	free_device_pointer(column.fractions);
	free_device_pointer(column.factor_indices);
	free_device_pointer(column.fraction_indices);
	free_device_pointer(column.exceptions_offsets);
	free_device_pointer(column.exceptions);
	free_device_pointer(column.positions);
	free_device_pointer(column.counts);
}

template <typename T>
void free_column(device::ALPExtendedColumn<T> column) {
	free_column(column.ffor);
	free_device_pointer(column.factors);
	free_device_pointer(column.fractions);
	free_device_pointer(column.factor_indices);
	free_device_pointer(column.fraction_indices);
	free_device_pointer(column.exceptions_offsets);
	free_device_pointer(column.exceptions);
	free_device_pointer(column.positions);
	free_device_pointer(column.offsets_counts);
}

} // namespace host
} // namespace flsgpu

#endif // STRUCTS_CUH
