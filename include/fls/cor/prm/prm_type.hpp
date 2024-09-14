#ifndef FLS_COR_PRM_PRM_TYPE_HPP
#define FLS_COR_PRM_PRM_TYPE_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
enum class prm_t : uint8_t { // NOLINT
	INVALID = 0,
	ZER_CPY,
	TRS, // in-place TRS
	MEM_CPY,
	MEM_TRS,
	ANALYZE,
	PA_ANALYZE, // patch_analyze
	RLE,
	RSUM,
	BITPACK,
	FFOR,
	B_FFOR,
	FACTOR,
	FSST,
	LL_PATCH,
	B_PATCH,
	S_PATCH,
	ALP,
};

std::string to_string(prm_t prm_t);
} // namespace fastlanes
#endif // FLS_COR_PRM_PRM_TYPE_HPP
