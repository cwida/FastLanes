#ifndef FLS_CUDA_COMMON_HPP
#define FLS_CUDA_COMMON_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/cuda/config.hpp"

namespace fastlanes::cuda {

template <typename PT>
constexpr n_t bits_in_object() {
	return sizeof(PT) * CHAR_BIT;
}

template <typename PT>
constexpr n_t get_lane_bitwidth() {
	return bits_in_object<PT>();
}

template <typename PT>
constexpr n_t get_n_lanes() {
	return Config::REGISTER_WIDTH / get_lane_bitwidth<PT>();
}

template <typename T>
constexpr n_t get_values_per_lane() {
	return CFG::VEC_SZ / get_n_lanes<T>();
}

} // namespace fastlanes::cuda

#endif // FLS_CUDA_COMMON_HPP