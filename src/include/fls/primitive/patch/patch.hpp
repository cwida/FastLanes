// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/primitive/patch/patch.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_PRIMITIVE_PATCH_PATCH_HPP
#define FLS_PRIMITIVE_PATCH_PATCH_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
n_t calculate_bitpacked_vector_size(bw_t bw);

template <typename PT>
class Patch {
public:
	static void data_parallelize(const PT*       in_exc_arr,
	                             const uint16_t* in_pos_arr,
	                             n_t             n_exceptions,
	                             PT*             out_exc_arr,
	                             uint16_t*       out_offset,
	                             uint16_t*       out_pos_arr,
	                             uint8_t*        out_count);
};

} // namespace fastlanes
#endif // FLS_PRIMITIVE_PATCH_PATCH_HPP
