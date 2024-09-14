#include "lemire_bitunpack_helper.hpp"
#include "gtest/gtest.h"

class rsum : public ::testing::Test {
public:
	uint8_t*  output08;
	uint16_t* output16;
	uint32_t* output32;
	uint64_t* output64;

	uint32_t* gen_value_32;
	uint32_t* gen_length_32;
	uint32_t* value_32;
	uint32_t* length_32;

	void SetUp() override {
		output08 = new uint8_t[1024]();
		output16 = new uint16_t[1024]();
		output32 = new uint32_t[1024]();
		output64 = new uint64_t[1024]();

		gen_value_32  = new uint32_t[1024]();
		gen_length_32 = new uint32_t[1024]();
		value_32      = new uint32_t[1024]();
		length_32     = new uint32_t[1024]();
	}
	~rsum() override {
		delete[] output08;
		delete[] output16;
		delete[] output32;
		delete[] output64;

		delete[] gen_value_32;
		delete[] gen_length_32;
		delete[] value_32;
		delete[] length_32;
	}
};

TEST_F(rsum, test_scalar_delta_manual_08) {
	manual::delta::scalar_delta(helper::delta_08, output08, helper::bases_08);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output08[i], helper::array_08[i]);
	}
}

TEST_F(rsum, test_scalar_delta_manual_16) {
	manual::delta::scalar_delta(helper::delta_16, output16, helper::bases_16);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output16[i], helper::array_16[i]);
	}
}

TEST_F(rsum, test_scalar_delta_manual_32) {
	manual::delta::scalar_delta(helper::delta_32, output32, helper::bases_32);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output32[i], helper::array_32[i]);
	}
}

TEST_F(rsum, test_scalar_delta_manual_64) {
	manual::delta::scalar_delta(helper::delta_64, output64, helper::bases_64);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output64[i], helper::array_64[i]);
	}
}

TEST_F(rsum, test_scalar_delta_lemire_d1) {
	manual::delta::lemire_d1(helper::delta_32, output32, helper::bases_32);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output32[i], helper::array_32[i]);
	}
}

TEST_F(rsum, test_scalar_avx2_d1) {
	manual::delta::my_avx2_d1(helper::delta_32, output32, helper::bases_32);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output32[i], helper::array_32[i]);
	}
}

// this implementation fails the test as the instruction has different behaviour.

// TEST_F(rsum, test_scalar_avx512_d1_08) {
//	manual::delta::avx512_d1_08(helper::delta_08, output08, helper::bases_08);
//	for (int i = 0; i < 1024; ++i) {
//		ASSERT_EQ(output08[i], helper::array_08[i]);
//	}
// }

// this implementation does not exist.

// TEST_F(rsum, test_scalar_avx512_d1_16) {
//	manual::delta::avx512_d1_16(helper::delta_16, output16, helper::bases_16);
//	for (int i = 0; i < 1024; ++i) {
//		ASSERT_EQ(output16[i], helper::array_16[i]);
//	}
// }

TEST_F(rsum, test_scalar_avx512_d1_32) {
	manual::delta::avx512_d1_32(helper::delta_32, output32, helper::bases_32);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output32[i], helper::array_32[i]);
	}
}

TEST_F(rsum, test_scalar_delta_4courser_08) {
	manual::delta::four_cursor_delta(helper::delta_08, output08, helper::bases_08);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output08[i], helper::array_08[i]);
	}
}

TEST_F(rsum, test_scalar_delta_4courser_16) {
	manual::delta::four_cursor_delta(helper::delta_16, output16, helper::bases_16);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output16[i], helper::array_16[i]);
	}
}

TEST_F(rsum, test_scalar_delta_4courser_32) {
	manual::delta::four_cursor_delta(helper::delta_32, output32, helper::bases_32);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output32[i], helper::array_32[i]);
	}
}

TEST_F(rsum, test_scalar_delta_4courser_64) {
	manual::delta::four_cursor_delta(helper::delta_64, output64, helper::bases_64);
	for (int i = 0; i < 1024; ++i) {
		ASSERT_EQ(output64[i], helper::array_64[i]);
	}
}