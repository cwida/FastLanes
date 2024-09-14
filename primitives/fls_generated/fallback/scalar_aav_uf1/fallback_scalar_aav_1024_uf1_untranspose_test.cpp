// generated!
// NOLINTBEGIN
#include "fallback_scalar_aav_1024_uf1_untranspose_helper.hpp"
#include "fls_gen/rsum/rsum.hpp"
#include "fls_gen/rsum_and_untranspose/rsum_and_untranspose.hpp"
#include "fls_gen/transpose/transpose.hpp"
#include "fls_gen/untranspose/untranspose.hpp"
#include "gtest/gtest.h"
class fallback_scalar_aav_1024_uf1_untranspose : public ::testing::Test {
public:
	uint8_t*  transposed8;
	uint16_t* transposed16;
	uint32_t* transposed32;
	uint64_t* transposed64;
	uint8_t*  untransposed8;
	uint16_t* untransposed16;
	uint32_t* untransposed32;
	uint64_t* untransposed64;
	void      SetUp() override {
        transposed8    = new uint8_t[1024]();
        transposed16   = new uint16_t[1024]();
        transposed32   = new uint32_t[1024]();
        transposed64   = new uint64_t[1024]();
        untransposed8  = new uint8_t[1024]();
        untransposed16 = new uint16_t[1024]();
        untransposed32 = new uint32_t[1024]();
        untransposed64 = new uint64_t[1024]();
	}
	~fallback_scalar_aav_1024_uf1_untranspose() override {
		delete[] transposed8;
		delete[] transposed16;
		delete[] transposed32;
		delete[] transposed64;
		delete[] untransposed8;
		delete[] untransposed16;
		delete[] untransposed32;
		delete[] untransposed64;
	}
};
