// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/alp/alp-bindings.cu
// ────────────────────────────────────────────────────────
#include "alp.hpp"
#include "alp/alp-bindings.cuh"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iterator>
#include <stdexcept>

namespace alp {
constexpr int MAX_ATTEMPTS_TO_ENCODE = 10000;

template <typename T>
size_t get_bytes_overhead_size_per_alp_vector() {
	return sizeof(uint8_t) + // bit_width
	       sizeof(uint8_t) + // factor-idx
	       sizeof(uint8_t) + // exponent-idx
	       sizeof(T);        // ffor base
	                         // + 32; // Overhead of vector offset in packed array
	                         // + 32; // Overhead of vector offset in exception array
};

template <typename T>
size_t get_bytes_overhead_size_per_alp_extended_vector() {
	return get_bytes_overhead_size_per_alp_vector<T>() +
	       sizeof(uint16_t) * utils::get_n_lanes<T>(); // pos + offset per lane
	                                                   // data parallel_format;
};

template <typename T>
size_t get_bytes_vector_compressed_size_without_overhead(const uint8_t bit_width, const uint16_t exceptions_count) {
	constexpr size_t line_size               = utils::get_n_lanes<T>() * sizeof(T);
	constexpr size_t exception_value_size    = sizeof(T);
	constexpr size_t exception_position_size = sizeof(uint16_t);

	return bit_width * line_size + exceptions_count * (exception_value_size + exception_position_size);
}

template <typename T>
bool is_compressable(const T* input_array, const size_t count) {
	T*       sample_array = new T[count];
	state<T> alpstate;

	bool is_possible = false;
	for (int32_t attempts = 0; attempts < MAX_ATTEMPTS_TO_ENCODE; ++attempts) {
		alp::encoder<T>::init(input_array, count, sample_array, alpstate);

		if ((is_possible = alpstate.scheme == alp::Scheme::ALP)) {
			break;
		}
	}

	delete[] sample_array;
	return is_possible;
}

template <typename T>
state<T> configure_alpstate(const T* input_array, const size_t n_values) {
	T*       sample_array = new T[n_values];
	state<T> alpstate;

	bool successful_encoding = false;
	for (int32_t attempts = 0; attempts < MAX_ATTEMPTS_TO_ENCODE; ++attempts) {
		alp::encoder<T>::init(input_array, n_values, sample_array, alpstate);

		if ((successful_encoding = alpstate.scheme == Scheme::ALP)) {
			break;
		}
	}
	if (!successful_encoding) {
		throw alp::EncodingException();
	}
	delete[] sample_array;
	return alpstate;
}

template <typename T>
flsgpu::host::ALPColumn<T> encode(const T* input_array, const size_t n_values, const bool print_compression_info) {
	using INT_T  = typename utils::same_width_int<T>::type;
	using UINT_T = typename utils::same_width_uint<T>::type;

	const size_t n_vecs   = utils::get_n_vecs_from_size(n_values);
	state<T>     alpstate = configure_alpstate(input_array, n_values);

	// Intermediate arrays
	UINT_T*   packed_array = new UINT_T[consts::VALUES_PER_VECTOR];
	T*        exceptions   = new T[consts::VALUES_PER_VECTOR];
	uint16_t* positions    = new uint16_t[consts::VALUES_PER_VECTOR];

	auto v_packed_array = std::vector<UINT_T>();
	auto v_exceptions   = std::vector<T>();
	auto v_positions    = std::vector<uint16_t>();

	// Final arrays
	vbw_t*    bit_widths         = new vbw_t[n_vecs];
	size_t*   vector_offsets     = new size_t[n_vecs];
	UINT_T*   bases              = new UINT_T[n_vecs];
	uint8_t*  factor_indices     = new uint8_t[n_vecs];
	uint8_t*  fraction_indices   = new uint8_t[n_vecs];
	size_t*   exceptions_offsets = new size_t[n_vecs];
	uint16_t* counts             = new uint16_t[n_vecs];

	size_t compressed_vector_sizes = 0;
	INT_T* encoded_array           = new INT_T[consts::VALUES_PER_VECTOR];
	size_t exceptions_offset       = 0;
	size_t vector_offset           = 0;

	size_t bit_widths_sum = 0;
	for (size_t vi {0}; vi < n_vecs; vi++) {
		alp::encoder<T>::encode(input_array, exceptions, positions, encoded_array, alpstate, nullptr);
		alp::encoder<T>::analyze_ffor(encoded_array, bit_widths[vi], reinterpret_cast<INT_T*>(&bases[vi]));

		counts[vi] = alpstate.n_exceptions;
		bit_widths_sum += bit_widths[vi];
		fastlanes::generated::ffor::fallback::scalar::ffor(
		    reinterpret_cast<UINT_T*>(encoded_array), packed_array, bit_widths[vi], &bases[vi]);

		input_array += consts::VALUES_PER_VECTOR;
		size_t compressed_values_size = utils::get_compressed_vector_size<T>(bit_widths[vi]);

		v_exceptions.insert(v_exceptions.end(), exceptions, exceptions + counts[vi]);
		v_positions.insert(v_positions.end(), positions, positions + counts[vi]);

		v_packed_array.insert(v_packed_array.end(), packed_array, packed_array + compressed_values_size);

		factor_indices[vi]     = alpstate.fac;
		fraction_indices[vi]   = alpstate.exp;
		exceptions_offsets[vi] = exceptions_offset;
		exceptions_offset += counts[vi];
		vector_offsets[vi] = vector_offset;
		vector_offset += compressed_values_size;

		compressed_vector_sizes +=
		    alp::get_bytes_vector_compressed_size_without_overhead<T>(bit_widths[vi], counts[vi]);
	}
	delete[] encoded_array;

	size_t compressed_alp_bytes_size =
	    compressed_vector_sizes + n_vecs * alp::get_bytes_overhead_size_per_alp_vector<T>();
	size_t compressed_alp_extended_bytes_size =
	    compressed_vector_sizes + n_vecs * alp::get_bytes_overhead_size_per_alp_extended_vector<T>();

	// Wrapping it up
	delete[] packed_array;
	delete[] exceptions;
	delete[] positions;

	packed_array = new UINT_T[v_packed_array.size()];
	exceptions   = new T[v_exceptions.size()];
	positions    = new uint16_t[v_positions.size()];

	std::memcpy(packed_array, v_packed_array.data(), v_packed_array.size() * sizeof(UINT_T));
	std::memcpy(exceptions, v_exceptions.data(), v_exceptions.size() * sizeof(T));
	std::memcpy(positions, v_positions.data(), v_positions.size() * sizeof(uint16_t));

	if (print_compression_info) {
		const size_t input_size = n_values * sizeof(T);
		printf("ALP_COMPRESSION_PARAMETERS,%zu,%f,%f,%f,%f\n",
		       n_vecs,
		       static_cast<double>(input_size) / static_cast<double>(compressed_alp_bytes_size),
		       static_cast<double>(input_size) / static_cast<double>(compressed_alp_extended_bytes_size),
		       static_cast<double>(bit_widths_sum) / static_cast<double>(n_vecs),
		       static_cast<double>(v_exceptions.size()) / static_cast<double>(n_vecs));
	}

	return flsgpu::host::ALPColumn<T> {
	    flsgpu::host::FFORColumn<UINT_T> {
	        flsgpu::host::BPColumn<UINT_T> {
	            n_values,
	            v_packed_array.size(),
	            packed_array,
	            bit_widths,
	            vector_offsets,
	        },
	        bases,
	    },
	    factor_indices,
	    fraction_indices,
	    v_exceptions.size(),
	    exceptions_offsets,
	    exceptions,
	    positions,
	    counts,
	    compressed_alp_bytes_size,
	    compressed_alp_extended_bytes_size,
	};
}

template <typename T>
T* decode(const flsgpu::host::ALPColumn<T> column, T* output_array) {
	const size_t n_vecs = utils::get_n_vecs_from_size(column.ffor.bp.n_values);

	T* c_output_array = output_array;
	for (size_t vi {0}; vi < n_vecs; ++vi) {
		generated::falp::fallback::scalar::falp(column.ffor.bp.packed_array + column.ffor.bp.vector_offsets[vi],
		                                        c_output_array,
		                                        column.ffor.bp.bit_widths[vi],
		                                        &column.ffor.bases[vi],
		                                        column.factor_indices[vi],
		                                        column.fraction_indices[vi]);

		alp::state<T> alpstate;
		alpstate.n_exceptions = column.counts[vi];

		alp::decoder<T>::patch_exceptions(c_output_array,
		                                  column.exceptions + column.exceptions_offsets[vi],
		                                  column.positions + column.exceptions_offsets[vi],
		                                  alpstate);

		c_output_array += consts::VALUES_PER_VECTOR;
	}

	return output_array;
}

template <typename T>
T* decode(const flsgpu::host::ALPExtendedColumn<T> column, T* output_array) {
	constexpr unsigned N_LANES = utils::get_n_lanes<T>();
	const size_t       n_vecs  = utils::get_n_vecs_from_size(column.ffor.bp.n_values);

	T* c_output_array = output_array;
	for (size_t vi {0}; vi < n_vecs; ++vi) {
		generated::falp::fallback::scalar::falp(column.ffor.bp.packed_array + column.ffor.bp.vector_offsets[vi],
		                                        c_output_array,
		                                        column.ffor.bp.bit_widths[vi],
		                                        &column.ffor.bases[vi],
		                                        column.factor_indices[vi],
		                                        column.fraction_indices[vi]);

		// Reconstruct total count
		uint16_t count = 0;
		for (size_t offset_count_i {0}; offset_count_i < N_LANES; ++offset_count_i) {
			count += column.offsets_counts[vi * N_LANES + offset_count_i] >> 10;
		}

		alp::state<T> alpstate;
		alpstate.n_exceptions = count; // fix me

		alp::decoder<T>::patch_exceptions(c_output_array,
		                                  column.exceptions + column.exceptions_offsets[vi],
		                                  column.positions + column.exceptions_offsets[vi],
		                                  alpstate);

		c_output_array += consts::VALUES_PER_VECTOR;
	}

	return output_array;
}

template bool is_compressable(const float* input_array, const size_t n_values);
template bool is_compressable(const double* input_array, const size_t n_values);

template flsgpu::host::ALPColumn<float>
encode(const float* input_array, const size_t n_values, const bool print_compression_info);
template flsgpu::host::ALPColumn<double>
encode(const double* input_array, const size_t n_values, const bool print_compression_info);

template float*  decode(const flsgpu::host::ALPColumn<float> column, float* output_array);
template double* decode(const flsgpu::host::ALPColumn<double> column, double* output_array);
template float*  decode(const flsgpu::host::ALPExtendedColumn<float> column, float* output_array);
template double* decode(const flsgpu::host::ALPExtendedColumn<double> column, double* output_array);

} // namespace alp
