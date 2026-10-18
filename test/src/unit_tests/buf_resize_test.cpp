// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// test/src/unit_tests/buf_resize_test.cpp
// ────────────────────────────────────────────────────────
#include "fls/cor/lyt/buf.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>

namespace fastlanes {
TEST(BufResize, GrowthUpdatesCapacityAndPreservesPayload) {
	const std::array<uint8_t, 2> payload {0x31, 0x92};
	Buf                          buf(2);
	buf.Append(payload.data(), payload.size());

	buf.Resize(4);

	ASSERT_EQ(buf.Capacity(), 4);
	EXPECT_EQ(buf.Size(), payload.size());
	EXPECT_EQ(buf.length(), payload.size());
	EXPECT_EQ(buf.data()[0], payload[0]);
	EXPECT_EQ(buf.data()[1], payload[1]);
	ASSERT_EQ(buf.Span().size(), payload.size());
	EXPECT_EQ(std::to_integer<uint8_t>(buf.Span()[1]), payload[1]);
}

TEST(BufResize, RepeatedGrowthSucceeds) {
	const std::array<uint8_t, 2> payload {0x31, 0x92};
	Buf                          buf(2);
	buf.Append(payload.data(), payload.size());

	buf.Resize(4);
	ASSERT_NO_THROW(buf.Resize(8));

	ASSERT_EQ(buf.Capacity(), 8);
	EXPECT_EQ(buf.Size(), payload.size());
	EXPECT_EQ(buf.data()[0], payload[0]);
	EXPECT_EQ(buf.data()[1], payload[1]);
}

TEST(BufResize, AppendUsesEnlargedCapacity) {
	const std::array<uint8_t, 2> payload {0x31, 0x92};
	const std::array<uint8_t, 4> suffix {0x43, 0x64, 0x85, 0xa6};
	Buf                          buf(2);
	buf.Append(payload.data(), payload.size());
	buf.Resize(8);
	ASSERT_EQ(buf.Capacity(), 8);

	buf.Append(suffix.data(), suffix.size());

	EXPECT_EQ(buf.Size(), payload.size() + suffix.size());
	EXPECT_EQ(buf.Capacity(), 8);
	EXPECT_EQ(buf.data()[0], payload[0]);
	EXPECT_EQ(buf.data()[1], payload[1]);
	for (std::size_t i = 0; i < suffix.size(); ++i) {
		EXPECT_EQ(buf.data()[payload.size() + i], suffix[i]);
	}
}

TEST(BufResize, NonGrowthPreservesState) {
	const std::array<uint8_t, 2> payload {0x31, 0x92};
	Buf                          buf(4);
	buf.Append(payload.data(), payload.size());
	auto* initial = buf.data();

	for (const auto request : {4U, 2U}) {
		buf.Resize(request);
		EXPECT_EQ(buf.Capacity(), 4);
		EXPECT_EQ(buf.Size(), payload.size());
		EXPECT_EQ(buf.data(), initial);
		EXPECT_EQ(buf.data()[0], payload[0]);
		EXPECT_EQ(buf.data()[1], payload[1]);
	}
}

TEST(BufResize, SwappedBufferRejectsResize) {
	std::array<uint8_t, 4> external {1, 2, 3, 4};
	Buf                    buf(4);
	buf.Swap(external.data());

	for (const auto request : {2U, 8U}) {
		EXPECT_THROW(buf.Resize(request), std::runtime_error);
		EXPECT_EQ(buf.data(), external.data());
		EXPECT_EQ(buf.Size(), 0);
		EXPECT_EQ(buf.Capacity(), 4);
		EXPECT_EQ(external, (std::array<uint8_t, 4> {1, 2, 3, 4}));
	}
}
} // namespace fastlanes
