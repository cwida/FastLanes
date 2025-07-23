// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// data/include/data/generated.hpp
// ────────────────────────────────────────────────────────
#ifndef DATA_GENERATED_HPP
#define DATA_GENERATED_HPP

#include <string>

namespace fastlanes {

class GENERATED {
public:
	static constexpr std::string_view CCC_ONE_TO_ONE_MAP {FLS_CMAKE_SOURCE_DIR "/data/generated/one_to_one"};
	static constexpr std::string_view ALL_CONSTANT {FLS_CMAKE_SOURCE_DIR "/data/generated/all_constant"};
	static constexpr std::string_view STRUCT {FLS_CMAKE_SOURCE_DIR "/data/generated/struct"};

	// SINGLE COLUMN
	static constexpr std::string_view SINGLE_COLUMN_I64PT {FLS_CMAKE_SOURCE_DIR
	                                                       "/data/generated/single_columns/fls_i64"};
	static constexpr std::string_view SINGLE_COLUMN_I32PT {FLS_CMAKE_SOURCE_DIR
	                                                       "/data/generated/single_columns/fls_i32"};
	static constexpr std::string_view SINGLE_COLUMN_I08PT {FLS_CMAKE_SOURCE_DIR
	                                                       "/data/generated/single_columns/fls_i08"};
	static constexpr std::string_view SINGLE_COLUMN_DBLPT {FLS_CMAKE_SOURCE_DIR
	                                                       "/data/generated/single_columns/fls_dbl"};
	static constexpr std::string_view SINGLE_COLUMN_STRPT {FLS_CMAKE_SOURCE_DIR
	                                                       "/data/generated/single_columns/fls_str"};
	static constexpr std::string_view SINGLE_COLUMN_U08PT {FLS_CMAKE_SOURCE_DIR
	                                                       "/data/generated/single_columns/fls_u08"};
	static constexpr std::string_view SINGLE_COLUMN_DECIMAL {FLS_CMAKE_SOURCE_DIR
	                                                         "/data/generated/single_columns/decimal"};
	static constexpr std::string_view SINGLE_COLUMN_FLOAT {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/float"};
	static constexpr std::string_view SINGLE_COLUMN_IRREGULAR_I64 {FLS_CMAKE_SOURCE_DIR
	                                                               "/data/generated/single_columns/irregular_i64"};
	static constexpr std::string_view SINGLE_COLUMN_DATE {FLS_CMAKE_SOURCE_DIR
	                                                      "/data/generated/single_columns/fls_date"};
	static constexpr std::string_view SINGLE_COLUMN_TIMESTAMP {FLS_CMAKE_SOURCE_DIR
	                                                           "/data/generated/single_columns/fls_timestamp"};
	static constexpr std::string_view SINGLE_COLUMN_BYTE_ARRAY {FLS_CMAKE_SOURCE_DIR
	                                                            "/data/generated/single_columns/byte_array"};
	static constexpr std::string_view SINGLE_COLUMN_JPEG {FLS_CMAKE_SOURCE_DIR "/data/generated/single_columns/jpeg"};
	static constexpr std::string_view SINGLE_COLUMN_BOOLEAN {FLS_CMAKE_SOURCE_DIR
	                                                         "/data/generated/single_columns/boolean"};

	//
	static constexpr std::string_view EQUALITY_I64PT {FLS_CMAKE_SOURCE_DIR "/data/generated/equality/fls_i64"};
	static constexpr std::string_view EQUALITY_DBLPT {FLS_CMAKE_SOURCE_DIR "/data/generated/equality/fls_dbl"};
	static constexpr std::string_view EQUALITY_STRPT {FLS_CMAKE_SOURCE_DIR "/data/generated/equality/fls_str"};
	static constexpr std::string_view ALL_TYPES {FLS_CMAKE_SOURCE_DIR "/data/generated/all_types"};
	static constexpr std::string_view X_PLUS_Y_EQUAL_Z {FLS_CMAKE_SOURCE_DIR
	                                                    "/data/generated/whitebox/x_plus_y_equal_z"};

	// ONE VEC
	static constexpr std::string_view ONE_VEC_I64PT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_i64"};
	static constexpr std::string_view ONE_VEC_I32PT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_i32"};
	static constexpr std::string_view ONE_VEC_I08PT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_i08"};
	static constexpr std::string_view ONE_VEC_STRPT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_str"};
	static constexpr std::string_view ONE_VEC_DBLPT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_dbl"};
	static constexpr std::string_view ONE_VEC_DECIMAL {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/decimal"};
	static constexpr std::string_view ONE_VEC_BOOLEAN {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/boolean"};
	static constexpr std::string_view ONE_VEC_U08PT {FLS_CMAKE_SOURCE_DIR "/data/generated/one_vector/fls_u08"};

	// TWO VEC
	static constexpr std::string_view TWO_VEC_STRPT {FLS_CMAKE_SOURCE_DIR "/data/generated/two_vector/fls_str"};

	// MOSTLY NULL
	static constexpr std::string_view MOSTLY_NULL {FLS_CMAKE_SOURCE_DIR "/data/generated/mostly_null"};

	// ENCODINGS
	static constexpr std::string_view FSST_DICT_U16_EXPR {FLS_CMAKE_SOURCE_DIR
	                                                      "/data/generated/encodings/fsst_dict_u16"};
	static constexpr std::string_view FREQUENCY_DBL_EXPR {FLS_CMAKE_SOURCE_DIR
	                                                      "/data/generated/encodings/frequency_dbl"};
	static constexpr std::string_view FREQUENCY_STR_EXPR {FLS_CMAKE_SOURCE_DIR
	                                                      "/data/generated/encodings/frequency_str"};
	static constexpr std::string_view EXP_CROSS_RLE_i16 {FLS_CMAKE_SOURCE_DIR
	                                                     "/data/generated/encodings/cross_rle_i16"};
	static constexpr std::string_view EXP_CROSS_RLE_STR {FLS_CMAKE_SOURCE_DIR
	                                                     "/data/generated/encodings/cross_rle_str"};
	static constexpr std::string_view EXP_ALP_FLT {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/alp_flt"};
	static constexpr std::string_view EXP_ALP_DBL {FLS_CMAKE_SOURCE_DIR "/data/generated/encodings/alp_dbl"};

	//
	static constexpr std::string_view NUMBER_STRINGS {FLS_CMAKE_SOURCE_DIR "/data/generated/whitebox/number_strings"};
	static constexpr std::string_view DECIMAL_DOUBLES {FLS_CMAKE_SOURCE_DIR "/data/generated/whitebox/decimal_doubles"};

	// Any count value
	static constexpr std::string_view ANY_VALUE_COUNT_I64_1 {FLS_CMAKE_SOURCE_DIR "/data/generated/any_value_count/1"};
	static constexpr std::string_view ANY_VALUE_COUNT_I64_666 {FLS_CMAKE_SOURCE_DIR
	                                                           "/data/generated/any_value_count/666"};
	static constexpr std::string_view ANY_VALUE_COUNT_I64_52422 {FLS_CMAKE_SOURCE_DIR
	                                                             "/data/generated/any_value_count/25570"};

	// SUBNORMAL
	static constexpr std::string_view SUBNORMALS {FLS_CMAKE_SOURCE_DIR "/data/generated/subnormals"};
};

} // namespace fastlanes

#endif // DATA_GENERATED_HPP
