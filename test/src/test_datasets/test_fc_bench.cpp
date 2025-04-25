#include "fls_tester.hpp"

namespace fastlanes {

// examples
TEST_F(FastLanesReaderTester, fc_bench_test) {
	const vector<n_t> constant_cols = {};
	const vector<n_t> equal_cols    = {};
	const vector<n_t> target_column_indexes {};

	AllTest(fc_bench::fc_bench_sample, constant_cols, equal_cols, target_column_indexes);
}
} // namespace fastlanes