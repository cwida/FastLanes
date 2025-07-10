// validitymask_test.cpp

#include "fls/types/validitymask.hpp"
#include <array>
#include <cstring>
#include <gtest/gtest.h>
#include <initializer_list>

namespace fastlanes {

// ───────────────────────────────────────── helpers
static ValidityMask mask_from(std::initializer_list<n_t> positions) {
	ValidityMask m;
	for (n_t p : positions)
		m.set(p);
	return m;
}

constexpr n_t BIT_CNT   = ValidityMask::BIT_COUNT;   // normally 1024
constexpr n_t BYTE_SIZE = ValidityMask::byte_size(); // normally 128

// ───────────────────────────────────────── ctor & empty state
TEST(ValidityMask, DefaultConstructedIsEmpty) {
	ValidityMask m;
	EXPECT_EQ(m.count(), 0);
	EXPECT_TRUE(m.none());
	EXPECT_FALSE(m.any());
	EXPECT_FALSE(m.all());
}

// ───────────────────────────────────────── single-bit API
TEST(ValidityMask, SetResetFlipTestSingleBits) {
	ValidityMask m;
	const n_t    first = 0;
	const n_t    last  = BIT_CNT - 1;

	m.set(first);
	m.set(last);
	EXPECT_TRUE(m.test(first));
	EXPECT_TRUE(m.test(last));
	EXPECT_EQ(m.count(), 2);

	m.reset(first);
	EXPECT_FALSE(m.test(first));
	EXPECT_TRUE(m.test(last));
	EXPECT_EQ(m.count(), 1);

	m.flip(last);  // clear last
	m.flip(first); // set first again
	EXPECT_TRUE(m.test(first));
	EXPECT_FALSE(m.test(last));
	EXPECT_EQ(m.count(), 1);
}

// ───────────────────────────────────────── bulk ops
TEST(ValidityMask, FillClearAnyAllCount) {
	ValidityMask m;
	m.fill();
	EXPECT_TRUE(m.all());
	EXPECT_EQ(m.count(), BIT_CNT);

	m.clear();
	EXPECT_TRUE(m.none());
	EXPECT_EQ(m.count(), 0);
}

// ───────────────────────────────────────── bitwise ops
TEST(ValidityMask, BitwiseOrAndXor) {
	auto         a = mask_from({0, 63});
	auto         b = mask_from({63, 100});
	ValidityMask c;

	// OR ⇒ {0,63,100}
	c.copy_from(a);
	c.bit_or(b);
	EXPECT_TRUE(c.test(0));
	EXPECT_TRUE(c.test(63));
	EXPECT_TRUE(c.test(100));
	EXPECT_EQ(c.count(), 3);

	// AND ⇒ {63}
	c.copy_from(a);
	c.bit_and(b);
	EXPECT_FALSE(c.test(0));
	EXPECT_TRUE(c.test(63));
	EXPECT_FALSE(c.test(100));
	EXPECT_EQ(c.count(), 1);

	// XOR ⇒ {0,100}
	c.copy_from(a);
	c.bit_xor(b);
	EXPECT_TRUE(c.test(0));
	EXPECT_FALSE(c.test(63));
	EXPECT_TRUE(c.test(100));
	EXPECT_EQ(c.count(), 2);
}

// ───────────────────────────────────────── copy semantics
TEST(ValidityMask, CopyFromClonesMask) {
	auto         src = mask_from({1, 500});
	ValidityMask dst;
	dst.copy_from(src);

	EXPECT_TRUE(dst.test(1));
	EXPECT_TRUE(dst.test(500));
	EXPECT_EQ(dst.count(), 2);
}

// ───────────────────────────────────────── encode / member decode round-trip
TEST(ValidityMask, EncodeDecodeRoundTrip) {
	// Prepare a buffer: even indices non-zero (0xFF), odd indices 0.
	std::array<uint8_t, BIT_CNT> inBytes {};
	for (n_t i = 0; i < BIT_CNT; ++i)
		inBytes[i] = (i & 1) ? 0x00 : 0xFF;

	ValidityMask m;
	m.encode(inBytes.data()); // load

	// decode → 0 / 1 bytes
	std::array<uint8_t, BIT_CNT> outBytes {};
	m.decode(outBytes.data());

	for (n_t i = 0; i < BIT_CNT; ++i) {
		bool expectedBit = (i & 1) == 0;
		EXPECT_EQ(bool(outBytes[i]), expectedBit) << "byte " << i;
	}
}

// ───────────────────────────────────────── static decode vs. member decode
TEST(ValidityMask, StaticDecodeMatchesMember) {
	// multiples-of-3 pattern
	ValidityMask m;
	for (n_t i = 0; i < BIT_CNT; i += 3)
		m.set(i);

	std::array<uint8_t, BIT_CNT> memberBuf {};
	std::array<uint8_t, BIT_CNT> staticBuf {};

	m.decode(memberBuf.data());
	ValidityMask::decode(m.data(), staticBuf.data());

	for (n_t i = 0; i < BIT_CNT; ++i)
		EXPECT_EQ(memberBuf[i], staticBuf[i]) << "byte " << i;
}

// ───────────────────────────────────────── static decode from raw words
TEST(ValidityMask, StaticDecodeFromRawWords) {
	// rawWords[0]  → 0xAAAAAAAA...  (odd bits set)
	// rawWords[15] → all ones
	std::array<uint64_t, ValidityMask::WORD_COUNT> rawWords {};
	rawWords[0]  = 0xAAAAAAAAAAAAAAAAULL;
	rawWords[15] = ~uint64_t {0};

	std::array<uint8_t, BIT_CNT> bytes {};
	ValidityMask::decode(rawWords.data(), bytes.data());

	for (n_t i = 0; i < BIT_CNT; ++i) {
		bool expect;
		if (i < 64)
			expect = (i & 1) == 1; // word0 pattern
		else if (i >= 15 * 64)
			expect = true; // word15 all ones
		else
			expect = false;
		EXPECT_EQ(bool(bytes[i]), expect) << "byte " << i;
	}
}

// ───────────────────────────────────────── data() raw pointer
TEST(ValidityMask, DataPointerAccess) {
	ValidityMask m;
	uint64_t*    raw = m.data();
	ASSERT_NE(raw, nullptr);

	raw[0] = 1ULL; // set bit0 via pointer
	EXPECT_TRUE(m.test(0));
	EXPECT_EQ(m.count(), 1);
}

// ───────────────────────────────────────── constants sanity
TEST(ValidityMask, ByteSizeConstant) {
	EXPECT_EQ(BYTE_SIZE, BIT_CNT / 8); // 1024 → 128
}

// ───────────────────────────────────────── stress sequential operations
TEST(ValidityMask, StressSequentialSetFlip) {
	ValidityMask m;

	for (n_t i = 0; i < BIT_CNT; ++i)
		m.set(i);
	EXPECT_TRUE(m.all());
	EXPECT_EQ(m.count(), BIT_CNT);

	for (n_t i = 0; i < BIT_CNT; ++i)
		m.flip(i);
	EXPECT_TRUE(m.none());

	for (n_t i = 0; i < BIT_CNT; i += 2)
		m.flip(i);
	EXPECT_EQ(m.count(), BIT_CNT / 2);
}

} // namespace fastlanes
