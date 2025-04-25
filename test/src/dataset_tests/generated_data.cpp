#include "fls_tester.hpp"

namespace fastlanes {

// Equalities
TEST_F(FastLanesReaderTester, EQUALITY_I64PT) {
	TestEquality(GENERATED::EQUALITY_I64PT);
}
TEST_F(FastLanesReaderTester, EQUALITY_DBLPT) {
	TestEquality(GENERATED::EQUALITY_DBLPT);
}
TEST_F(FastLanesReaderTester, EQUALITY_STRPT) {
	TestEquality(GENERATED::EQUALITY_STRPT);
}

// Single Columns
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_STRPT) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_STRPT);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_I64PT) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_I64PT);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_I32PT) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_I32PT);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_I08PT) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_I08PT);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_DBLPT) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_DBLPT);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_U08PT) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_U08PT);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_STRUCT) {
	TestCorrectness<FileT::JSON>(GENERATED::STRUCT);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_DECIMAL) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_DECIMAL);
}
TEST_F(FastLanesReaderTester, SINGLE_COLUMN_FLOAT) {
	TestCorrectness(GENERATED::SINGLE_COLUMN_FLOAT);
}

// All Constants
TEST_F(FastLanesReaderTester, ALL_CONSTANT) {
	const vector<n_t> constant_cols = {0, 1, 2, 3, 4};
	const vector<n_t> equal_cols    = {};
	const vector<n_t> target_column_indexes {};

	AllTest(GENERATED::ALL_CONSTANT, constant_cols, equal_cols, target_column_indexes);
}

// All types
TEST_F(FastLanesReaderTester, ALL_TYPES) {
	TestCorrectness<FileT::JSON>(GENERATED::ALL_TYPES);
}

// TEST ONE VEC
TEST_F(FastLanesReaderTester, ONE_VEC_I64PT) {
	TestCorrectness(GENERATED::ONE_VEC_I64PT);
}
TEST_F(FastLanesReaderTester, ONE_VEC_I32PT) {
	TestCorrectness(GENERATED::ONE_VEC_I32PT);
}
TEST_F(FastLanesReaderTester, ONE_VEC_STRPT) {
	TestCorrectness(GENERATED::ONE_VEC_STRPT);
}
TEST_F(FastLanesReaderTester, ONE_VEC_I08PT) {
	TestCorrectness(GENERATED::ONE_VEC_I08PT);
}
TEST_F(FastLanesReaderTester, ONE_VEC_DECIMAL) {
	TestCorrectness(GENERATED::ONE_VEC_DECIMAL);
}

// TEST ONE VEC
TEST_F(FastLanesReaderTester, TWO_VEC_STRPT) {
	TestCorrectness(GENERATED::TWO_VEC_STRPT);
}

TEST_F(FastLanesReaderTester, ONE_TO_ONE) {
	const vector<n_t> constant_cols                 = {};
	const vector<n_t> equal_cols                    = {};  // No equal columns found
	const vector<n_t> one_to_one_mapped_col_indexes = {1}; // No one-to-one mapped columns found
	AllTest(GENERATED::CCC_ONE_TO_ONE_MAP, constant_cols, equal_cols, one_to_one_mapped_col_indexes);
}

TEST_F(FastLanesReaderTester, MOSTLYNULL) {
	TestCorrectness(GENERATED::MOSTLY_NULL);
}

TEST_F(FastLanesReaderTester, FSST_DICT_U16_EXPR) {
	TestCorrectness(GENERATED::FSST_DICT_U16_EXPR);
}

// whitebox
TEST_F(FastLanesReaderTester, NUMBER_STRINGS) {
	TestCorrectness(GENERATED::NUMBER_STRINGS);
}
TEST_F(FastLanesReaderTester, DECIMAL_DOUBLES) {
	TestCorrectness(GENERATED::DECIMAL_DOUBLES);
}

} // namespace fastlanes