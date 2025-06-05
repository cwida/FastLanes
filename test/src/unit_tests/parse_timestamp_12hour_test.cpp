// test/src/unit_tests/parse_timestamp_12hour_test.cpp

#include "fls/types/timestamp.hpp"
#include <gtest/gtest.h>

namespace fastlanes {

// ──────────────────────────────────────────────────────────────
// parse_timestamp: 12-hour clock with AM/PM
// ──────────────────────────────────────────────────────────────

// 2004-01-01T00:01:00 UTC → 1 minute after midnight
//  Unix timestamp = 1072915200 + 60 = 1072915260 seconds
//  ⇒ 1072915260 × 10^6 = 1072915260000000 μs
TEST(ParseTimestamp_12HourFormat, JustAfterMidnight) {
	EXPECT_EQ(parse_timestamp("01/01/2004 12:01:00 AM"), 1072915260'000000LL);
}

// 2004-01-01T12:00:00 UTC → noon
//  Unix timestamp = 1072915200 + 43200 = 1072958400 seconds
//  ⇒ 1072958400 × 10^6 = 1072958400000000 μs
TEST(ParseTimestamp_12HourFormat, NoonExactly) {
	EXPECT_EQ(parse_timestamp("01/01/2004 12:00:00 PM"), 1072958400'000000LL);
}

// 2004-07-04T03:05:07 UTC → early morning on July 4
//  Unix timestamp = 1088910307 seconds
//  ⇒ 1088910307 × 10^6 = 1088910307000000 μs
TEST(ParseTimestamp_12HourFormat, EarlyMorningSummer) {
	EXPECT_EQ(parse_timestamp("07/04/2004 03:05:07 AM"), 1088910307'000000LL);
}

// 2004-07-04T21:15:30 UTC → late evening on July 4
//  Unix timestamp = 1088975730 seconds
//  ⇒ 1088975730 × 10^6 = 1088975730000000 μs
TEST(ParseTimestamp_12HourFormat, LateEveningSummer) {
	EXPECT_EQ(parse_timestamp("07/04/2004 09:15:30 PM"), 1088975730'000000LL);
}

// Invalid hour “13:00:00 AM”: should throw invalid_argument
TEST(ParseTimestamp_12HourFormat, InvalidHour) {
	EXPECT_THROW(parse_timestamp("01/01/2004 13:00:00 AM"), std::invalid_argument);
}

// Invalid suffix “XM” instead of “AM”/“PM”: should throw invalid_argument
TEST(ParseTimestamp_12HourFormat, InvalidSuffix) {
	EXPECT_THROW(parse_timestamp("01/01/2004 10:00:00 XM"), std::invalid_argument);
}

} // namespace fastlanes
