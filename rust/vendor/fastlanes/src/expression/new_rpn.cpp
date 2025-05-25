#include "fls/common/assert.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/rpn.hpp"
#include "fls/std/unordered_set.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * SerializedExpr
\*--------------------------------------------------------------------------------------------------------------------*/

string token_to_string(OperatorToken token) {
	switch (token) {
	case OperatorToken::INVALID:
		return "INVALID"; // 0
	case OperatorToken::EXP_EQUAL:
		return "EXP_EQUAL"; // 1
	case OperatorToken::EXP_CONSTANT_I64:
		return "EXP_CONSTANT_I64"; // 2
	case OperatorToken::EXP_CONSTANT_I32:
		return "EXP_CONSTANT_I32"; // 3
	case OperatorToken::EXP_CONSTANT_I16:
		return "EXP_CONSTANT_I16"; // 4
	case OperatorToken::EXP_CONSTANT_DBL:
		return "EXP_CONSTANT_DBL"; // 5
	case OperatorToken::EXP_CONSTANT_STR:
		return "EXP_CONSTANT_STR"; // 6
	case OperatorToken::EXP_CONSTANT_U08:
		return "EXP_CONSTANT_U08"; // 7
	case OperatorToken::EXP_STRUCT:
		return "EXP_STRUCT"; // 8
	case OperatorToken::EXP_UNCOMPRESSED_STR:
		return "EXP_UNCOMPRESSED_STR"; // 9
	case OperatorToken::EXP_UNCOMPRESSED_I64:
		return "EXP_UNCOMPRESSED_I64"; // 10
	case OperatorToken::EXP_UNCOMPRESSED_I16:
		return "EXP_UNCOMPRESSED_I16"; // 11
	case OperatorToken::EXP_UNCOMPRESSED_I32:
		return "EXP_UNCOMPRESSED_I32"; // 12
	case OperatorToken::EXP_UNCOMPRESSED_DBL:
		return "EXP_UNCOMPRESSED_DBL"; // 13
	case OperatorToken::EXP_UNCOMPRESSED_U08:
		return "EXP_UNCOMPRESSED_U08"; // 14
	case OperatorToken::EXP_FFOR_I64:
		return "EXP_FFOR_I64"; // 15
	case OperatorToken::EXP_FFOR_I32:
		return "EXP_FFOR_I32"; // 16
	case OperatorToken::EXP_FFOR_I16:
		return "EXP_FFOR_I16"; // 17
	case OperatorToken::EXP_DICT_I64_FFOR_U32:
		return "EXP_DICT_I64_FFOR_U32"; // 18
	case OperatorToken::EXP_DICT_I64_FFOR_U16:
		return "EXP_DICT_I64_FFOR_U16"; // 19
	case OperatorToken::EXP_DICT_I64_FFOR_U08:
		return "EXP_DICT_I64_FFOR_U08"; // 20
	case OperatorToken::EXP_DICT_I32_FFOR_U32:
		return "EXP_DICT_I32_FFOR_U32"; // 21
	case OperatorToken::EXP_DICT_I32_FFOR_U16:
		return "EXP_DICT_I32_FFOR_U16"; // 22
	case OperatorToken::EXP_DICT_I32_FFOR_U08:
		return "EXP_DICT_I32_FFOR_U08"; // 23
	case OperatorToken::EXP_DICT_I16_FFOR_U16:
		return "EXP_DICT_I16_FFOR_U16"; // 24
	case OperatorToken::EXP_DICT_I16_FFOR_U08:
		return "EXP_DICT_I16_FFOR_U08"; // 25
	case OperatorToken::EXP_DICT_DBL_FFOR_U32:
		return "EXP_DICT_DBL_FFOR_U32"; // 26
	case OperatorToken::EXP_DICT_DBL_FFOR_U16:
		return "EXP_DICT_DBL_FFOR_U16"; // 27
	case OperatorToken::EXP_DICT_DBL_FFOR_U08:
		return "EXP_DICT_DBL_FFOR_U08"; // 28
	case OperatorToken::EXP_DICT_STR_FFOR_U32:
		return "EXP_DICT_STR_FFOR_U32"; // 29
	case OperatorToken::EXP_DICT_STR_FFOR_U16:
		return "EXP_DICT_STR_FFOR_U16"; // 30
	case OperatorToken::EXP_DICT_STR_FFOR_U08:
		return "EXP_DICT_STR_FFOR_U08"; // 31
	case OperatorToken::EXP_FSST_DICT_STR_FFOR_U32:
		return "EXP_FSST_DICT_STR_FFOR_U32"; // 32
	case OperatorToken::EXP_FSST_DICT_STR_FFOR_U16:
		return "EXP_FSST_DICT_STR_FFOR_U16"; // 33
	case OperatorToken::EXP_FSST_DICT_STR_FFOR_U08:
		return "EXP_FSST_DICT_STR_FFOR_U08"; // 34
	case OperatorToken::WIZARD_DICTIONARY_ENCODE:
		return "WIZARD_DICTIONARY_ENCODE"; // 35
	case OperatorToken::EXP_DICT_I64_U32:
		return "EXP_DICT_I64_U32"; // 36
	case OperatorToken::EXP_DICT_I64_U16:
		return "EXP_DICT_I64_U16"; // 37
	case OperatorToken::EXP_DICT_I64_U08:
		return "EXP_DICT_I64_U08"; // 38
	case OperatorToken::EXP_DICT_I32_U32:
		return "EXP_DICT_I32_U32"; // 39
	case OperatorToken::EXP_DICT_I32_U16:
		return "EXP_DICT_I32_U16"; // 40
	case OperatorToken::EXP_DICT_I32_U08:
		return "EXP_DICT_I32_U08"; // 41
	case OperatorToken::EXP_DICT_I16_U16:
		return "EXP_DICT_I16_U16"; // 42
	case OperatorToken::EXP_DICT_I16_U08:
		return "EXP_DICT_I16_U08"; // 43
	case OperatorToken::EXP_DICT_DBL_U32:
		return "EXP_DICT_DBL_U32"; // 44
	case OperatorToken::EXP_DICT_DBL_U16:
		return "EXP_DICT_DBL_U16"; // 45
	case OperatorToken::EXP_DICT_DBL_U08:
		return "EXP_DICT_DBL_U08"; // 46
	case OperatorToken::EXP_DICT_STR_U32:
		return "EXP_DICT_STR_U32"; // 47
	case OperatorToken::EXP_DICT_STR_U16:
		return "EXP_DICT_STR_U16"; // 48
	case OperatorToken::EXP_DICT_STR_U08:
		return "EXP_DICT_STR_U08"; // 49
	case OperatorToken::EXP_ALP_DBL:
		return "EXP_ALP_DBL"; // 50
	case OperatorToken::EXP_ALP_RD_DBL:
		return "EXP_ALP_RD_DBL"; // 51
	case OperatorToken::EXP_FSST:
		return "EXP_FSST"; // 52
	case OperatorToken::EXP_FSST12:
		return "EXP_FSST12"; // 53
	case OperatorToken::EXP_FSST_DELTA:
		return "EXP_FSST_DELTA"; // 54
	case OperatorToken::EXP_FSST12_DELTA:
		return "EXP_FSST12_DELTA"; // 55
	case OperatorToken::EXP_RLE_I64_U16:
		return "EXP_RLE_I64_U16"; // 56
	case OperatorToken::EXP_RLE_I32_U16:
		return "EXP_RLE_I32_U16"; // 57
	case OperatorToken::EXP_RLE_I16_U16:
		return "EXP_RLE_I16_U16"; // 58
	case OperatorToken::EXP_RLE_DBL_U16:
		return "EXP_RLE_DBL_U16"; // 59
	case OperatorToken::EXP_RLE_STR_U16:
		return "EXP_RLE_STR_U16"; // 60
	case OperatorToken::EXP_DELTA_I64:
		return "EXP_DELTA_I64"; // 61
	case OperatorToken::EXP_DELTA_I32:
		return "EXP_DELTA_I32"; // 62
	case OperatorToken::EXP_DELTA_I16:
		return "EXP_DELTA_I16"; // 63
	case OperatorToken::EXP_FFOR_SLPATCH_I64:
		return "EXP_FFOR_SLPATCH_I64"; // 64
	case OperatorToken::EXP_FFOR_SLPATCH_I32:
		return "EXP_FFOR_SLPATCH_I32"; // 65
	case OperatorToken::EXP_FFOR_SLPATCH_I16:
		return "EXP_FFOR_SLPATCH_I16"; // 66
	case OperatorToken::EXP_DICT_I64_FFOR_SLPATCH_U32:
		return "EXP_DICT_I64_FFOR_SLPATCH_U32"; // 67
	case OperatorToken::EXP_DICT_I64_FFOR_SLPATCH_U16:
		return "EXP_DICT_I64_FFOR_SLPATCH_U16"; // 68
	case OperatorToken::EXP_DICT_I64_FFOR_SLPATCH_U08:
		return "EXP_DICT_I64_FFOR_SLPATCH_U08"; // 69
	case OperatorToken::EXP_DICT_I32_FFOR_SLPATCH_U32:
		return "EXP_DICT_I32_FFOR_SLPATCH_U32"; // 70
	case OperatorToken::EXP_DICT_I32_FFOR_SLPATCH_U16:
		return "EXP_DICT_I32_FFOR_SLPATCH_U16"; // 71
	case OperatorToken::EXP_DICT_I32_FFOR_SLPATCH_U08:
		return "EXP_DICT_I32_FFOR_SLPATCH_U08"; // 72
	case OperatorToken::EXP_DICT_I16_FFOR_SLPATCH_U16:
		return "EXP_DICT_I16_FFOR_SLPATCH_U16"; // 73
	case OperatorToken::EXP_DICT_I16_FFOR_SLPATCH_U08:
		return "EXP_DICT_I16_FFOR_SLPATCH_U08"; // 74
	case OperatorToken::EXP_DICT_DBL_FFOR_SLPATCH_U32:
		return "EXP_DICT_DBL_FFOR_SLPATCH_U32"; // 75
	case OperatorToken::EXP_DICT_DBL_FFOR_SLPATCH_U16:
		return "EXP_DICT_DBL_FFOR_SLPATCH_U16"; // 76
	case OperatorToken::EXP_DICT_DBL_FFOR_SLPATCH_U08:
		return "EXP_DICT_DBL_FFOR_SLPATCH_U08"; // 77
	case OperatorToken::EXP_DICT_STR_FFOR_SLPATCH_U32:
		return "EXP_DICT_STR_FFOR_SLPATCH_U32"; // 78
	case OperatorToken::EXP_DICT_STR_FFOR_SLPATCH_U16:
		return "EXP_DICT_STR_FFOR_SLPATCH_U16"; // 79
	case OperatorToken::EXP_DICT_STR_FFOR_SLPATCH_U08:
		return "EXP_DICT_STR_FFOR_SLPATCH_U08"; // 80
	case OperatorToken::EXP_FSST_DICT_STR_FFOR_SLPATCH_U32:
		return "EXP_FSST_DICT_STR_FFOR_SLPATCH_U32"; // 81
	case OperatorToken::EXP_FSST_DICT_STR_FFOR_SLPATCH_U16:
		return "EXP_FSST_DICT_STR_FFOR_SLPATCH_U16"; // 82
	case OperatorToken::EXP_FSST_DICT_STR_FFOR_SLPATCH_U08:
		return "EXP_FSST_DICT_STR_FFOR_SLPATCH_U08"; // 83
	case OperatorToken::EXP_NULL_DBL:
		return "EXP_NULL_DBL"; // 84
	case OperatorToken::EXP_NULL_I16:
		return "EXP_NULL_I16"; // 85
	case OperatorToken::EXP_RLE_I64_SLPATCH_U16:
		return "EXP_RLE_I64_SLPATCH_U16"; // 86
	case OperatorToken::EXP_RLE_I32_SLPATCH_U16:
		return "EXP_RLE_I32_SLPATCH_U16"; // 87
	case OperatorToken::EXP_RLE_I16_SLPATCH_U16:
		return "EXP_RLE_I16_SLPATCH_U16"; // 88
	case OperatorToken::EXP_RLE_DBL_SLPATCH_U16:
		return "EXP_RLE_DBL_SLPATCH_U16"; // 89
	case OperatorToken::EXP_RLE_STR_SLPATCH_U16:
		return "EXP_RLE_STR_SLPATCH_U16"; // 90
	case OperatorToken::EXP_FSST_DICT_STR_U32:
		return "EXP_FSST_DICT_STR_U32"; // 91
	case OperatorToken::EXP_FSST_DICT_STR_U16:
		return "EXP_FSST_DICT_STR_U16"; // 92
	case OperatorToken::EXP_FSST_DICT_STR_U08:
		return "EXP_FSST_DICT_STR_U08"; // 93
	case OperatorToken::EXP_FSST_DELTA_SLPATCH:
		return "EXP_FSST_DELTA_SLPATCH"; // 94
	case OperatorToken::EXP_FSST12_DELTA_SLPATCH:
		return "EXP_FSST12_DELTA_SLPATCH"; // 95
	case OperatorToken::EXP_FSST12_DICT_STR_U32:
		return "EXP_FSST12_DICT_STR_U32"; // 96
	case OperatorToken::EXP_FSST12_DICT_STR_U16:
		return "EXP_FSST12_DICT_STR_U16"; // 97
	case OperatorToken::EXP_FSST12_DICT_STR_U08:
		return "EXP_FSST12_DICT_STR_U08"; // 98
	case OperatorToken::EXP_FSST12_DICT_STR_FFOR_SLPATCH_U08:
		return "EXP_FSST12_DICT_STR_FFOR_SLPATCH_U08"; // 99
	case OperatorToken::EXP_FSST12_DICT_STR_FFOR_SLPATCH_U16:
		return "EXP_FSST12_DICT_STR_FFOR_SLPATCH_U16"; // 100
	case OperatorToken::EXP_FSST12_DICT_STR_FFOR_SLPATCH_U32:
		return "EXP_FSST12_DICT_STR_FFOR_SLPATCH_U32"; // 101
	case OperatorToken::EXP_FSST12_DICT_STR_FFOR_U08:
		return "EXP_FSST12_DICT_STR_FFOR_U08"; // 102
	case OperatorToken::EXP_FSST12_DICT_STR_FFOR_U16:
		return "EXP_FSST12_DICT_STR_FFOR_U16"; // 103
	case OperatorToken::EXP_FSST12_DICT_STR_FFOR_U32:
		return "EXP_FSST12_DICT_STR_FFOR_U32"; // 104
	case OperatorToken::EXP_UNCOMPRESSED_I08:
		return "EXP_UNCOMPRESSED_I08"; // 105
	case OperatorToken::EXP_CONSTANT_I08:
		return "EXP_CONSTANT_I08"; // 106
	case OperatorToken::EXP_DICT_I08_FFOR_U08:
		return "EXP_DICT_I08_FFOR_U08"; // 107
	case OperatorToken::EXP_DICT_I08_U08:
		return "EXP_DICT_I08_U08"; // 108
	case OperatorToken::EXP_FFOR_I08:
		return "EXP_FFOR_I08"; // 109
	case OperatorToken::WIZARD_CHOOSE_DICT:
		return "WIZARD_CHOOSE_DICT"; // 110
	case OperatorToken::EXP_RLE_I08_U16:
		return "EXP_RLE_I08_U16"; // 111
	case OperatorToken::EXP_DELTA_I08:
		return "EXP_DELTA_I08"; // 112
	case OperatorToken::EXP_FFOR_SLPATCH_I08:
		return "EXP_FFOR_SLPATCH_I08"; // 113
	case OperatorToken::EXP_RLE_I08_SLPATCH_U16:
		return "EXP_RLE_I08_SLPATCH_U16"; // 114
	case OperatorToken::EXP_DICT_I08_FFOR_SLPATCH_U08:
		return "EXP_DICT_I08_FFOR_SLPATCH_U08"; // 115
	case OperatorToken::EXP_FREQUENCY_DBL:
		return "EXP_FREQUENCY_DBL"; // 116
	case OperatorToken::EXP_FREQUENCY_I08:
		return "EXP_FREQUENCY_I08"; // 117
	case OperatorToken::EXP_FREQUENCY_I16:
		return "EXP_FREQUENCY_I16"; // 118
	case OperatorToken::EXP_FREQUENCY_I32:
		return "EXP_FREQUENCY_I32"; // 119
	case OperatorToken::EXP_FREQUENCY_I64:
		return "EXP_FREQUENCY_I64"; // 120
	case OperatorToken::EXP_FREQUENCY_STR:
		return "EXP_FREQUENCY_STR"; // 121
	case OperatorToken::EXP_CROSS_RLE_I08:
		return "EXP_CROSS_RLE_I08"; // 122
	case OperatorToken::EXP_CROSS_RLE_I16:
		return "EXP_CROSS_RLE_I16"; // 123
	case OperatorToken::EXP_CROSS_RLE_I32:
		return "EXP_CROSS_RLE_I32"; // 124
	case OperatorToken::EXP_CROSS_RLE_I64:
		return "EXP_CROSS_RLE_I64"; // 125
	case OperatorToken::EXP_CROSS_RLE_DBL:
		return "EXP_CROSS_RLE_DBL"; // 126
	case OperatorToken::EXP_CROSS_RLE_STR:
		return "EXP_CROSS_RLE_STR"; // 127
	case OperatorToken::EXP_NULL_I32:
		return "EXP_NULL_I32"; // 127
	case OperatorToken::EXP_CONSTANT_FLT:
		return "EXP_CONSTANT_FLT"; // 129
	case OperatorToken::EXP_UNCOMPRESSED_FLT:
		return "EXP_UNCOMPRESSED_FLT"; // 130
	case OperatorToken::EXP_NULL_FLT:
		return "EXP_NULL_FLT"; // 131
	case OperatorToken::EXP_ALP_FLT:
		return "EXP_ALP_FLT"; // 132
	case OperatorToken::EXP_RLE_FLT_U16:
		return "EXP_RLE_FLT_U16"; // 132
	case OperatorToken::EXP_DICT_FLT_FFOR_U16:
		return "EXP_DICT_FLT_FFOR_U16"; // 133
	case OperatorToken::EXP_RLE_FLT_SLPATCH_U16:
		return "EXP_RLE_FLT_SLPATCH_U16"; // 135
	case OperatorToken::EXP_ALP_RD_FLT:
		return "EXP_ALP_RD_FLT"; // 136
	case OperatorToken::EXP_FREQUENCY_FLT:
		return "EXP_FREQUENCY_FLT"; // 137
	case OperatorToken::EXP_CROSS_RLE_FLT:
		return "EXP_CROSS_RLE_FLT"; // 138
	case OperatorToken::EXP_DICT_FLT_FFOR_U08:
		return "EXP_DICT_FLT_FFOR_U08"; // 139
	case OperatorToken::EXP_DICT_FLT_FFOR_SLPATCH_U08:
		return "EXP_DICT_FLT_FFOR_SLPATCH_U08"; // 140
	case OperatorToken::EXP_DICT_FLT_FFOR_SLPATCH_U16:
		return "EXP_DICT_FLT_FFOR_SLPATCH_U16"; // 141
	case OperatorToken::EXP_DICT_FLT_FFOR_U32:
		return "EXP_DICT_FLT_FFOR_U32"; // 142
	case OperatorToken::EXP_DICT_FLT_FFOR_SLPATCH_U32:
		return "EXP_DICT_FLT_FFOR_SLPATCH_U32"; // 143
	default:
		FLS_UNREACHABLE()
	}
}

// Overload the `<<` operator for RPN
std::ostream& operator<<(std::ostream& os, const RPNT& rpn) {
	os << "{";

	// Print operator tokens
	os << "[";
	for (size_t i = 0; i < rpn.operator_tokens.size(); ++i) {
		os << token_to_string(rpn.operator_tokens[i]);
		if (i != rpn.operator_tokens.size() - 1)
			os << ", ";
	}
	os << "]";

	// Print operand tokens
	os << "[";
	for (size_t i = 0; i < rpn.operand_tokens.size(); ++i) {
		os << rpn.operand_tokens[i];
		if (i != rpn.operand_tokens.size() - 1)
			os << ", ";
	}
	os << "]";

	os << "}";
	return os;
}

bool is_1_to_1(const OperatorToken token) {
	static std::unordered_set<OperatorToken> one_to_one_set {
	    OperatorToken::EXP_DICT_I64_U32,        OperatorToken::EXP_DICT_I64_U16,
	    OperatorToken::EXP_DICT_I64_U08,        OperatorToken::EXP_DICT_I32_U32,
	    OperatorToken::EXP_DICT_I32_U16,        OperatorToken::EXP_DICT_I32_U08,
	    OperatorToken::EXP_DICT_I16_U16,        OperatorToken::EXP_DICT_I16_U08,
	    OperatorToken::EXP_DICT_I08_U08,        OperatorToken::EXP_DICT_DBL_U32,
	    OperatorToken::EXP_DICT_DBL_U16,        OperatorToken::EXP_DICT_DBL_U08,
	    OperatorToken::EXP_DICT_STR_U32,        OperatorToken::EXP_DICT_STR_U16,
	    OperatorToken::EXP_DICT_STR_U08,        OperatorToken::EXP_FSST_DICT_STR_U32,
	    OperatorToken::EXP_FSST_DICT_STR_U16,   OperatorToken::EXP_FSST_DICT_STR_U08,
	    OperatorToken::EXP_FSST12_DICT_STR_U32, OperatorToken::EXP_FSST12_DICT_STR_U16,
	    OperatorToken::EXP_FSST12_DICT_STR_U08,
	};

	return one_to_one_set.contains(token);
}

} // namespace fastlanes