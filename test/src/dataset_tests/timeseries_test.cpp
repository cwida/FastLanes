// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/dataset_tests/timeseries_test.cpp
// ────────────────────────────────────────────────────────
#include "data/TimeSeries.hpp"
#include "fastlanes.hpp"
#include "fls_tester.hpp"

namespace fastlanes {

#define TIMESERIES_TEST(DATASET_VAR)                                                                                     \
	TEST_F(FastLanesReaderTester, TimeSeries_##DATASET_VAR) {                                                            \
		const std::vector<n_t> constant_cols {};                                                                       \
		const std::vector<n_t> equal_cols {};                                                                          \
		const std::vector<n_t> one_to_one_mapped_col_indexes {};                                                       \
		AllTest(TimeSeries::DATASET_VAR, constant_cols, equal_cols, one_to_one_mapped_col_indexes);                      \
	}


TIMESERIES_TEST(SMART_GRID)
TIMESERIES_TEST(LINEAR_ROEAD)
TIMESERIES_TEST(COMPUTER_MONITOR)
TIMESERIES_TEST(AMPds)
TIMESERIES_TEST(WEATHER_FORCAST)


#undef TIMESERIES_TEST

} // namespace fastlanes
