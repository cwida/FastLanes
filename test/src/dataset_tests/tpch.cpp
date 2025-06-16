#include "data/tpch.hpp" // Make sure this header defines Tpch::customer, Tpch::lineitem, etc.
#include "fastlanes.hpp"
#include "fls_tester.hpp"

namespace fastlanes {

// Test reading/processing for each TPCH table. Uses TestCorrectness to compare
// against a reference CSV or expected output. Adjust the test names as needed.

TEST_F(FastLanesReaderTester, tpch_customer) {
	TestCorrectness(Tpch::customer);
}

TEST_F(FastLanesReaderTester, tpch_lineitem) {
	TestCorrectness(Tpch::lineitem);
}

TEST_F(FastLanesReaderTester, tpch_orders) {
	TestCorrectness(Tpch::orders);
}

TEST_F(FastLanesReaderTester, tpch_part) {
	TestCorrectness(Tpch::part);
}

TEST_F(FastLanesReaderTester, tpch_partsupp) {
	TestCorrectness(Tpch::partsupp);
}

} // namespace fastlanes
