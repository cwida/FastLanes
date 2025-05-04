#include "fls/wizard/sampling_layout.hpp"
#include <algorithm>
#include <array>
#include <gtest/gtest.h>
#include <unordered_set>
#include <vector>

namespace fastlanes {
// Helper: convert a constexpr array to a vector<n_t>
template <n_t N>
static vector<n_t> to_vec(const array<uint64_t, N>& arr) {
	return {arr.begin(), arr.end()};
}

// ───────────────────────── TESTS ─────────────────────────────────────────────

// 1. Exact equality for sizes covered at compile time
TEST(FinalLayoutDynamic, MatchesCompileTimeLayouts) {
	EXPECT_EQ(sampling_layout_dynamic(1), to_vec<1>(sampling_layout<1>()));
	EXPECT_EQ(sampling_layout_dynamic(2), to_vec<2>(sampling_layout<2>()));
	EXPECT_EQ(sampling_layout_dynamic(32), to_vec<32>(sampling_layout<32>()));
	EXPECT_EQ(sampling_layout_dynamic(64), to_vec<64>(sampling_layout<64>()));
}

// 2. Explicit checks for a few small Ns
TEST(FinalLayoutDynamic, SmallSizes) {
	// sampling_layout_test.cpp
	EXPECT_EQ(sampling_layout_dynamic(3), (vector<n_t> {0, 2, 1}));
	EXPECT_EQ(sampling_layout_dynamic(4), (vector<n_t> {0, 3, 1, 2}));
	EXPECT_EQ(sampling_layout_dynamic(7), (vector<n_t> {0, 6, 3, 4, 5, 1, 2}));
}

// 3. General-property test: permutation [0..N-1] with unique elements
TEST(FinalLayoutDynamic, ProducesPermutation) {
	for (n_t N = 1; N <= 128; ++N) {
		auto vec = sampling_layout_dynamic(N);

		ASSERT_EQ(vec.size(), N);

		std::unordered_set<n_t> seen(vec.begin(), vec.end());
		EXPECT_EQ(seen.size(), N) << "Duplicate or missing element for N = " << N;

		// Ensure every value 0..N-1 appears
		for (n_t v = 0; v < static_cast<n_t>(N); ++v) {
			EXPECT_TRUE(seen.count(v)) << "Value " << v << " missing for N = " << N;
		}
	}
}

} // namespace fastlanes