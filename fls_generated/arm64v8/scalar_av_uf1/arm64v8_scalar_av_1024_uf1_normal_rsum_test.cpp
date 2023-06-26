#include "gtest/gtest.h"
#include "fls_gen/normal_rsum/normal_rsum.hpp"
#include "arm64v8_scalar_av_1024_uf1_normal_rsum_helper.hpp"
class arm64v8_scalar_av_1024_uf1_normal_rsum: public ::testing::Test
{
	public:
	int8_t *out8;
	int16_t *out16;
	int32_t *out32;
	int64_t *out64;
	void SetUp() override
	{
		out8 = new int8_t[1024]();
		out16 = new int16_t[1024]();
		out32 = new int32_t[1024]();
		out64 = new int64_t[1024]();
	}
	~arm64v8_scalar_av_1024_uf1_normal_rsum () override
	{
		delete[] out8;
		delete[] out16;
		delete[] out32;
		delete[] out64;
	}
}
;
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 0_ow_8_rsum)
{
	generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow8, out8, helper::base_arr_ow8);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out8[i], helper::arr_ow8[i]);
	}
}
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 1_ow_8_rsum)
{
	generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow8, out8, helper::base_arr_ow8);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out8[i], helper::arr_ow8[i]);
	}
}
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 2_ow_16_rsum)
{
	generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow16, out16, helper::base_arr_ow16);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out16[i], helper::arr_ow16[i]);
	}
}
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 3_ow_16_rsum)
{
	generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow16, out16, helper::base_arr_ow16);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out16[i], helper::arr_ow16[i]);
	}
}
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 4_ow_32_rsum)
{
	generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow32, out32, helper::base_arr_ow32);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out32[i], helper::arr_ow32[i]);
	}
}
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 5_ow_32_rsum)
{
	generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow32, out32, helper::base_arr_ow32);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out32[i], helper::arr_ow32[i]);
	}
}
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 6_ow_64_rsum)
{
	generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow64, out64, helper::base_arr_ow64);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out64[i], helper::arr_ow64[i]);
	}
}
TEST_F(arm64v8_scalar_av_1024_uf1_normal_rsum, 7_ow_64_rsum)
{
	generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow64, out64, helper::base_arr_ow64);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(out64[i], helper::arr_ow64[i]);
	}
}
