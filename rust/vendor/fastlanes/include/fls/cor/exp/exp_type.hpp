#ifndef FLS_COR_EXP_EXP_TYPE_HPP
#define FLS_COR_EXP_EXP_TYPE_HPP

#include <cstdint>

namespace fastlanes {
enum class ExpT : uint8_t {
	INVALID      = 0, // always!
	UNDECIDED    = 1,
	UNCOMPRESSED = 2,
	BYTE_ARR     = 3,
	FFOR         = 4,
	DELTA        = 5,
	RLE          = 6,
	FSST         = 7,
	DICT         = 8,
	DICT_FRQ     = 9,
	DICT_VAL     = 10,
	DICT_RLE     = 11,
	TGT_EQUALITY = 12,
	TGT_1T1      = 13,
	TGT_1TN      = 14,
	SRC_1T1      = 15,
	SRC_1TN      = 16,
	ALP          = 17,
	ALP_RD       = 18,
	FSST12       = 20,
};
} // namespace fastlanes
#endif // FLS_COR_EXP_EXP_TYPE_HPP
