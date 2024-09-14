#include "gtest/gtest.h"
#include "fls_gen/unrsum/unrsum.hpp"
#include "helper_scalar_av_1024_uf1_unrsum_helper.hpp"
class helper_scalar_av_1024_uf1_unrsum: public ::testing::Test
{
	public:
	uint8_t *rsum8;
	uint16_t *rsum16;
	uint32_t *rsum32;
	uint64_t *rsum64;
	uint8_t *unrsum8;
	uint16_t *unrsum16;
	uint32_t *unrsum32;
	uint64_t *unrsum64;
	uint8_t *inplace_unrsum8;
	uint16_t *inplace_unrsum16;
	uint32_t *inplace_unrsum32;
	uint64_t *inplace_unrsum64;
	void SetUp() override
	{
		rsum8 = new uint8_t[1024]();
		rsum16 = new uint16_t[1024]();
		rsum32 = new uint32_t[1024]();
		rsum64 = new uint64_t[1024]();
		unrsum8 = new uint8_t[1024]();
		unrsum16 = new uint16_t[1024]();
		unrsum32 = new uint32_t[1024]();
		unrsum64 = new uint64_t[1024]();
		inplace_unrsum8 = new uint8_t[1024]();
		inplace_unrsum16 = new uint16_t[1024]();
		inplace_unrsum32 = new uint32_t[1024]();
		inplace_unrsum64 = new uint64_t[1024]();
	}
	~helper_scalar_av_1024_uf1_unrsum () override
	{
		delete[] rsum8;
		delete[] rsum16;
		delete[] rsum32;
		delete[] rsum64;
		delete[] unrsum8;
		delete[] unrsum16;
		delete[] unrsum32;
		delete[] unrsum64;
		delete[] inplace_unrsum8;
		delete[] inplace_unrsum16;
		delete[] inplace_unrsum32;
		delete[] inplace_unrsum64;
	}
}
;
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_0_ow_8_unrsum)
{
	generated::unrsum::helper::scalar::unrsum(helper::transposed_arr_ow8, unrsum8);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(unrsum8[i], helper::delta_arr_ow8[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_1_ow_16_unrsum)
{
	generated::unrsum::helper::scalar::unrsum(helper::transposed_arr_ow16, unrsum16);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(unrsum16[i], helper::delta_arr_ow16[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_2_ow_32_unrsum)
{
	generated::unrsum::helper::scalar::unrsum(helper::transposed_arr_ow32, unrsum32);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(unrsum32[i], helper::delta_arr_ow32[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_3_ow_64_unrsum)
{
	generated::unrsum::helper::scalar::unrsum(helper::transposed_arr_ow64, unrsum64);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(unrsum64[i], helper::delta_arr_ow64[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_4_ow_8_unrsum_inplace)
{
	memcpy(inplace_unrsum8, helper::transposed_arr_ow8, (8/8) * 1024);
	generated::unrsum::helper::scalar::unrsum_inplace(inplace_unrsum8);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(inplace_unrsum8[i], helper::delta_arr_ow8[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_5_ow_16_unrsum_inplace)
{
	memcpy(inplace_unrsum16, helper::transposed_arr_ow16, (16/8) * 1024);
	generated::unrsum::helper::scalar::unrsum_inplace(inplace_unrsum16);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(inplace_unrsum16[i], helper::delta_arr_ow16[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_6_ow_32_unrsum_inplace)
{
	memcpy(inplace_unrsum32, helper::transposed_arr_ow32, (32/8) * 1024);
	generated::unrsum::helper::scalar::unrsum_inplace(inplace_unrsum32);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(inplace_unrsum32[i], helper::delta_arr_ow32[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_unrsum, test_7_ow_64_unrsum_inplace)
{
	memcpy(inplace_unrsum64, helper::transposed_arr_ow64, (64/8) * 1024);
	generated::unrsum::helper::scalar::unrsum_inplace(inplace_unrsum64);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(inplace_unrsum64[i], helper::delta_arr_ow64[i]);
	}
}
