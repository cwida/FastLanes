#include "bitpacking.hpp"
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
