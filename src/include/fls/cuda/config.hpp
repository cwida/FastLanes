// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/cuda/config.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_CUDA_CONFIG_HPP
#define FLS_CUDA_CONFIG_HPP

#include "fls/common/alias.hpp" // for hdr_field_t

namespace fastlanes::cuda {
class Config {
public:
	explicit Config(); //
public:
	static constexpr n_t REGISTER_WIDTH = 1024; //
};

} // namespace fastlanes::cuda

#endif // FLS_CUDA_CONFIG_HPP
