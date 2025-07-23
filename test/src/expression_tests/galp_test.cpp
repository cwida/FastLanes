// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/expression_tests/galp_test.cpp
// ────────────────────────────────────────────────────────
#include "fls_tester.hpp"

namespace fastlanes {

// ——— FLOAT tests ———————————————————————————————————————————————

TEST_F(FastLanesReaderTester, TEST_GALP_FLOAT_ONE_VECTOR) {
	TestCorrectness(galp::float_galp_one_vector, {OperatorToken::EXP_GALP_FLT});
}

TEST_F(FastLanesReaderTester, TEST_GALP_FLOAT_SINGLE_COLUMN) {
	TestCorrectness(galp::float_galp_single_column, {OperatorToken::EXP_GALP_FLT});
}

TEST_F(FastLanesReaderTester, TEST_GALP_FLOAT_CONSTANT_ONE_VECTOR) {
	TestCorrectness(galp::float_constant_one_vector, {OperatorToken::EXP_GALP_FLT});
}

TEST_F(FastLanesReaderTester, TEST_GALP_FLOAT_CONSTANT_SINGLE_COLUMN) {
	TestCorrectness(galp::float_constant_single_column, {OperatorToken::EXP_GALP_FLT});
}

TEST_F(FastLanesReaderTester, TEST_GALP_FLOAT_POSITIVE_INF_ONE_VECTOR) {
	TestCorrectness(galp::float_positive_inf_one_vector, {OperatorToken::EXP_GALP_FLT});
}

TEST_F(FastLanesReaderTester, TEST_GALP_FLOAT_POSITIVE_INF_SINGLE_COLUMN) {
	TestCorrectness(galp::float_positive_inf_single_column, {OperatorToken::EXP_GALP_FLT});
}

// ——— DOUBLE tests ———————————————————————————————————————————————

TEST_F(FastLanesReaderTester, TEST_GALP_DOUBLE_ONE_VECTOR) {
	TestCorrectness(galp::double_galp_one_vector, {OperatorToken::EXP_GALP_DBL});
}

TEST_F(FastLanesReaderTester, TEST_GALP_DOUBLE_SINGLE_COLUMN) {
	TestCorrectness(galp::double_galp_single_column, {OperatorToken::EXP_GALP_DBL});
}

TEST_F(FastLanesReaderTester, TEST_GALP_DOUBLE_CONSTANT_ONE_VECTOR) {
	TestCorrectness(galp::double_constant_one_vector, {OperatorToken::EXP_GALP_DBL});
}

TEST_F(FastLanesReaderTester, TEST_GALP_DOUBLE_CONSTANT_SINGLE_COLUMN) {
	TestCorrectness(galp::double_constant_single_column, {OperatorToken::EXP_GALP_DBL});
}

TEST_F(FastLanesReaderTester, TEST_GALP_DOUBLE_POSITIVE_INF_ONE_VECTOR) {
	TestCorrectness(galp::double_positive_inf_one_vector, {OperatorToken::EXP_GALP_DBL});
}

TEST_F(FastLanesReaderTester, TEST_GALP_DOUBLE_POSITIVE_INF_SINGLE_COLUMN) {
	TestCorrectness(galp::double_positive_inf_single_column, {OperatorToken::EXP_GALP_DBL});
}

} // namespace fastlanes
