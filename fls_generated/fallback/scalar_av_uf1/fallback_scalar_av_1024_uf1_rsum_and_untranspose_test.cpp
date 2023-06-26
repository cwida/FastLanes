#include "gtest/gtest.h"
#include "fls_gen/transpose/transpose.hpp"
#include "fls_gen/untranspose/untranspose.hpp"
#include "fls_gen/rsum/rsum.hpp"
#include "fls_gen/rsum_and_untranspose/rsum_and_untranspose.hpp"
#include "fallback_scalar_av_1024_uf1_rsum_and_untranspose_helper.hpp"
class fallback_scalar_av_1024_uf1_rsum_and_untranspose: public ::testing::Test
{
	public:
	uint8_t *transposed8;
	uint16_t *transposed16;
	uint32_t *transposed32;
	uint64_t *transposed64;
	uint8_t *untransposed8;
	uint16_t *untransposed16;
	uint32_t *untransposed32;
	uint64_t *untransposed64;
	void SetUp() override
	{
		transposed8 = new uint8_t[1024]();
		transposed16 = new uint16_t[1024]();
		transposed32 = new uint32_t[1024]();
		transposed64 = new uint64_t[1024]();
		untransposed8 = new uint8_t[1024]();
		untransposed16 = new uint16_t[1024]();
		untransposed32 = new uint32_t[1024]();
		untransposed64 = new uint64_t[1024]();
	}
	~fallback_scalar_av_1024_uf1_rsum_and_untranspose () override
	{
		delete[] transposed8;
		delete[] transposed16;
		delete[] transposed32;
		delete[] transposed64;
		delete[] untransposed8;
		delete[] untransposed16;
		delete[] untransposed32;
		delete[] untransposed64;
	}
}
;
TEST_F(fallback_scalar_av_1024_uf1_rsum_and_untranspose, test_0_ow_8_rsum_and_untranspose)
{
	generated::rsum_and_untranspose::fallback::scalar::rsum_and_untranspose(helper::delta_arr_ow8, untransposed8, helper::base_arr_ow8);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow8[i], untransposed8[i]);
	}
}
TEST_F(fallback_scalar_av_1024_uf1_rsum_and_untranspose, test_1_ow_16_rsum_and_untranspose)
{
	generated::rsum_and_untranspose::fallback::scalar::rsum_and_untranspose(helper::delta_arr_ow16, untransposed16, helper::base_arr_ow16);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow16[i], untransposed16[i]);
	}
}
TEST_F(fallback_scalar_av_1024_uf1_rsum_and_untranspose, test_2_ow_32_rsum_and_untranspose)
{
	generated::rsum_and_untranspose::fallback::scalar::rsum_and_untranspose(helper::delta_arr_ow32, untransposed32, helper::base_arr_ow32);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow32[i], untransposed32[i]);
	}
}
TEST_F(fallback_scalar_av_1024_uf1_rsum_and_untranspose, test_3_ow_64_rsum_and_untranspose)
{
	generated::rsum_and_untranspose::fallback::scalar::rsum_and_untranspose(helper::delta_arr_ow64, untransposed64, helper::base_arr_ow64);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow64[i], untransposed64[i]);
	}
}
