#ifndef DATA_GENERATED_HPP
#define DATA_GENERATED_HPP

#include "fls/std/string.hpp"

namespace fastlanes {

class GENERATED {
public:
	static constexpr string_view CCC_ONE_TO_ONE_MAP {FLS_CMAKE_SOURCE_DIR "/data/generated/one_to_one"};
	static constexpr string_view ALL_CONSTANT {FLS_CMAKE_SOURCE_DIR "/data/generated/all_constant"};
	static constexpr string_view STRUCT {FLS_CMAKE_SOURCE_DIR "/data/generated/struct"};

	// SINGLE COLUMN
	static constexpr string_view SINGLE_COLUMN_I64PT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/fls_i64"};
	static constexpr string_view SINGLE_COLUMN_I32PT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/fls_i32"};
	static constexpr string_view SINGLE_COLUMN_I08PT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/fls_i08"};
	static constexpr string_view SINGLE_COLUMN_DBLPT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/fls_dbl"};
	static constexpr string_view SINGLE_COLUMN_STRPT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/fls_str"};
	static constexpr string_view SINGLE_COLUMN_U08PT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/fls_u08"};
	static constexpr string_view SINGLE_COLUMN_DECIMAL {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/decimal"};
	static constexpr string_view SINGLE_COLUMN_FLOAT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/float"};
	static constexpr string_view SINGLE_COLUMN_IRREGULAR_I64 {FLS_CMAKE_SOURCE_DIR
	                                                          "/data/generated/single_columns/irregular_i64"};

	//
	static constexpr string_view EQUALITY_I64PT {FLS_CMAKE_SOURCE_DIR "/data/generated/equality/fls_i64"};
	static constexpr string_view EQUALITY_DBLPT {FLS_CMAKE_SOURCE_DIR "/data/generated/equality/fls_dbl"};
	static constexpr string_view EQUALITY_STRPT {FLS_CMAKE_SOURCE_DIR "/data/generated/equality/fls_str"};
	static constexpr string_view ALL_TYPES {FLS_CMAKE_SOURCE_DIR "/data/generated/all_types"};
	static constexpr string_view X_PLUS_Y_EQUAL_Z {FLS_CMAKE_SOURCE_DIR "/data/generated/whitebox/x_plus_y_equal_z"};

	// ONE VEC
	static constexpr string_view ONE_VEC_I64PT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_i64"};
	static constexpr string_view ONE_VEC_I32PT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_i32"};
	static constexpr string_view ONE_VEC_I08PT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_i08"};
	static constexpr string_view ONE_VEC_STRPT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_str"};
	static constexpr string_view ONE_VEC_DBLPT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_dbl"};
	static constexpr string_view ONE_VEC_DECIMAL {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/decimal"};

	// TWO VEC
	static constexpr string_view TWO_VEC_STRPT {FLS_CMAKE_SOURCE_DIR "/data/generated/two_vector/fls_str"};

	// MOSTLY NULL
	static constexpr string_view MOSTLY_NULL {FLS_CMAKE_SOURCE_DIR "/data/generated/mostly_null"};

	// ENCODINGS
	static constexpr string_view FSST_DICT_U16_EXPR {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/fsst_dict_u16"};
	static constexpr string_view FREQUENCY_DBL_EXPR {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/frequency_dbl"};
	static constexpr string_view FREQUENCY_STR_EXPR {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/frequency_str"};
	static constexpr string_view EXP_CROSS_RLE_i16 {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/cross_rle_i16"};
	static constexpr string_view EXP_CROSS_RLE_STR {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/cross_rle_str"};
	static constexpr string_view EXP_ALP_FLT {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/alp_flt"};
	static constexpr string_view EXP_ALP_DBL {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/alp_dbl"};

	static constexpr string_view NUMBER_STRINGS {FLS_CMAKE_SOURCE_DIR "/data/generated/whitebox/number_strings"};
	static constexpr string_view DECIMAL_DOUBLES {FLS_CMAKE_SOURCE_DIR "/data/generated/whitebox/decimal_doubles"};
};

} // namespace fastlanes

#endif // DATA_GENERATED_HPP
