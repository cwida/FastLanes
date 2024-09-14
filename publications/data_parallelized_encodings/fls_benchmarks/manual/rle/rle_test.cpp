#include "generator.hpp"
#include "rle_helper.hpp"
#include "gtest/gtest.h"

class rle : public ::testing::Test {
public:
	uint8_t*  output08;
	uint16_t* output16;
	uint32_t* output32;
	uint64_t* output64;

	uint32_t* gen_value_32;
	uint32_t* gen_length_32;
	uint32_t* value_32;
	uint32_t* length_32;
	uint16_t* gen_value_16;
	uint16_t* gen_length_16;
	uint16_t* value_16;
	uint16_t* length_16;

	void SetUp() override {
		output08 = new uint8_t[1024]();
		output16 = new uint16_t[1024]();
		output32 = new uint32_t[1024]();
		output64 = new uint64_t[1024]();

		gen_value_32  = new uint32_t[1024]();
		gen_length_32 = new uint32_t[1024]();
		value_32      = new uint32_t[1024]();
		length_32     = new uint32_t[1024]();

		gen_value_16  = new uint16_t[1024]();
		gen_length_16 = new uint16_t[1024]();
		value_16      = new uint16_t[1024]();
		length_16     = new uint16_t[1024]();

	}
	~rle() override {
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


TEST_F(rle, rle_scalar_16) {
	for (size_t n {1}; n < 250; ++n) {
		generator::generate_rle_data(n, gen_value_16, gen_length_16);

		manual::rle::scalar_rle_decompress(gen_value_16, gen_length_16, output16);

		manual::rle::scalar_rle_compress(value_16, length_16, output16);

		for (int i {0}; i < n; ++i) {
			ASSERT_EQ(gen_value_16[i], value_16[i]);
			ASSERT_EQ(gen_length_16[i], length_16[i]);
		}
	}
}

TEST_F(rle, rle_scalar_32) {
	for (size_t n {1}; n < 250; ++n) {
		generator::generate_rle_data(n, gen_value_32, gen_length_32);

		manual::rle::scalar_rle_decompress(gen_value_32, gen_length_32, output32);

		manual::rle::scalar_rle_compress(value_32, length_32, output32);

		for (int i {0}; i < n; ++i) {
			ASSERT_EQ(gen_value_32[i], value_32[i]);
			ASSERT_EQ(gen_length_32[i], length_32[i]);
		}
	}
}



TEST_F(rle, rle_avx512_32) {
	for (size_t n {1}; n < 250; ++n) {
		generator::generate_rle_data(n, gen_value_32, gen_length_32);

		manual::rle::simd_rle_avx512_32(gen_value_32, gen_length_32, output32);

		manual::rle::scalar_rle_compress(value_32, length_32, output32);

		for (int i {0}; i < n; ++i) {
			ASSERT_EQ(gen_value_32[i], value_32[i]);
			ASSERT_EQ(gen_length_32[i], length_32[i]);
		}
	}
}

TEST_F(rle, rle_avx512_16) {
	for (size_t n {1}; n < 250; ++n) {
		generator::generate_rle_data(n, gen_value_16, gen_length_16);

		manual::rle::simd_rle_avx512_16(gen_value_16, gen_length_16, output16);

		manual::rle::scalar_rle_compress(value_16, length_16, output16);

		for (int i {0}; i < n; ++i) {
			ASSERT_EQ(gen_value_16[i], value_16[i]);
			ASSERT_EQ(gen_length_16[i], length_16[i]);
		}
	}
}