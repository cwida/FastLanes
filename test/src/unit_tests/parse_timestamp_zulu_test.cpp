// test/src/unit_tests/parse_timestamp_zulu_test.cpp

#include "fls/types/timestamp.hpp"
#include <gtest/gtest.h>

namespace fastlanes {

// ──────────────────────────────────────────────────────────────
// parse_timestamp: ISO-8601 Zulu (“Z”) suffix
// ──────────────────────────────────────────────────────────────

// 2014-12-31T23:01:35.647Z
//   → 2014-12-31 23:01:35 UTC + 0 offset
//   Unix timestamp seconds = 1420066895
//   + 0.647s = 1420066895.647
//   μs = 1420066895 * 1e6 + 647000 = 1420066895647000
TEST(ParseTimestamp_ISO8601_Zulu_WithFraction, Valid) {
	EXPECT_EQ(parse_timestamp("2014-12-31T23:01:35.647Z"), 1420066895'647000LL);
}

// 2014-12-31T23:01:35Z
//   → 2014-12-31 23:01:35 UTC exactly
//   Unix timestamp seconds = 1420066895
//   μs = 1420066895 * 1e6 = 1420066895000000
TEST(ParseTimestamp_ISO8601_Zulu_NoFraction, Valid) {
	EXPECT_EQ(parse_timestamp("2014-12-31T23:01:35Z"), 1420066895'000000LL);
}

// Lowercase ‘z’ is not permitted – should throw invalid_argument
TEST(ParseTimestamp_ISO8601_Zulu_LowercaseZ, Invalid) {
	EXPECT_THROW(parse_timestamp("2014-12-31T23:01:35.647z"), std::invalid_argument);
}

// Trailing characters after “Z” are not allowed
TEST(ParseTimestamp_ISO8601_Zulu_TrailingGarbage, Invalid) {
	EXPECT_THROW(parse_timestamp("2014-12-31T23:01:35.647ZFOO"), std::invalid_argument);
}

} // namespace fastlanes
