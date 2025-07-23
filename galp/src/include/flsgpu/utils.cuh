// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/flsgpu/utils.cuh
// ────────────────────────────────────────────────────────
#ifndef FASTLANES_UTILS_H
#define FASTLANES_UTILS_H

#include "consts.cuh"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>

namespace utils { // internal functions
	              //
template <typename T>
struct same_width_int {
	using type = typename std::conditional<
	    sizeof(T) == 8,
	    int64_t,
	    typename std::conditional<sizeof(T) == 4,
	                              int32_t,
	                              typename std::conditional<sizeof(T) == 2, int16_t, int8_t>::type>::type>::type;
};

template <typename T>
struct same_width_uint {
	using type = typename std::conditional<
	    sizeof(T) == 8,
	    uint64_t,
	    typename std::conditional<sizeof(T) == 4,
	                              uint32_t,
	                              typename std::conditional<sizeof(T) == 2, uint16_t, uint8_t>::type>::type>::type;
};

template <typename T, typename returnT = int32_t>
constexpr returnT sizeof_in_bits() {
	return sizeof(T) * 8;
}

template <typename T>
constexpr T min(const T& a, const T& b) {
	// C++-11 and older do not offer constexpr, that is why this is added here
	return a <= b ? a : b;
}

template <typename T_in, typename T_out>
constexpr T_out reinterpret_type(const T_in& in) {
	// Type punning, the compiler optimizes out the memcpy
	// https://cuda.godbolt.org/z/bKG89YTY7
	// https://stackoverflow.com/questions/47037104/cuda-type-punning-memcpy-vs-ub-union
	// T_out out;
	// T_in staged = in;
	// memcpy(&out, &staged, min(sizeof(T_in), sizeof(T_out)));
	// return out;
	T_in staged = in;
	return *reinterpret_cast<T_out*>(&staged);
}

template <typename T>
constexpr T h_set_first_n_bits(const int32_t count) {
	return (count < sizeof_in_bits<T>() ? static_cast<T>((T {1} << int32_t {count}) - T {1}) : static_cast<T>(~T {0}));
}

template <typename T>
constexpr T set_first_n_bits(const int32_t count) {
	using UINT_T = typename same_width_uint<T>::type;
	static_assert(std::is_integral<T>::value, "T must be an integer type");

	return reinterpret_type<UINT_T, T>(std::numeric_limits<UINT_T>::max() >>
	                                   reinterpret_type<int32_t, UINT_T>(utils::sizeof_in_bits<UINT_T>() - count));
}

template <typename T>
constexpr int32_t get_lane_bitwidth() {
	return sizeof_in_bits<T>();
}

template <typename T>
constexpr int32_t get_n_lanes() {
	return consts::REGISTER_WIDTH / get_lane_bitwidth<T>();
}

template <typename T>
constexpr int32_t get_values_per_lane() {
	return consts::VALUES_PER_VECTOR / get_n_lanes<T>();
}

template <typename T>
constexpr int32_t get_compressed_vector_size(int32_t value_bit_width) {
	return (consts::VALUES_PER_VECTOR * value_bit_width) / sizeof_in_bits<T>();
}

constexpr size_t get_n_vecs_from_size(const size_t size) {
	return (size + consts::VALUES_PER_VECTOR - 1) / consts::VALUES_PER_VECTOR;
}

template <typename T>
T* copy_array(const T* in, const size_t n_elements) {
	T* out = new T[n_elements];
	std::memcpy(out, in, sizeof(T) * n_elements);
	return out;
}

} // namespace utils

#endif // FASTLANES_UTILS_H
