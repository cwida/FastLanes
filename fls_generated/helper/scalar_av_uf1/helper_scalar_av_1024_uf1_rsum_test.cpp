#include "gtest/gtest.h"
#include "fls_gen/transpose/transpose.hpp"
#include "fls_gen/untranspose/untranspose.hpp"
#include "fls_gen/rsum/rsum.hpp"
#include "fls_gen/rsum_and_untranspose/rsum_and_untranspose.hpp"
#include "helper_scalar_av_1024_uf1_rsum_helper.hpp"
class helper_scalar_av_1024_uf1_rsum: public ::testing::Test
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
	~helper_scalar_av_1024_uf1_rsum () override
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
TEST_F(helper_scalar_av_1024_uf1_rsum, test_0_ow_8_rsum)
{
	generated::rsum::helper::scalar::rsum(helper::delta_arr_ow8, transposed8, helper::base_arr_ow8);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(transposed8[i], helper::transposed_arr_ow8[i]);
	}
	generated::untranspose::helper::scalar::untranspose_o(transposed8, untransposed8);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow8[i], untransposed8[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_rsum, test_1_ow_16_rsum)
{
	generated::rsum::helper::scalar::rsum(helper::delta_arr_ow16, transposed16, helper::base_arr_ow16);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(transposed16[i], helper::transposed_arr_ow16[i]);
	}
	generated::untranspose::helper::scalar::untranspose_o(transposed16, untransposed16);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow16[i], untransposed16[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_rsum, test_2_ow_32_rsum)
{
	generated::rsum::helper::scalar::rsum(helper::delta_arr_ow32, transposed32, helper::base_arr_ow32);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(transposed32[i], helper::transposed_arr_ow32[i]);
	}
	generated::untranspose::helper::scalar::untranspose_o(transposed32, untransposed32);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow32[i], untransposed32[i]);
	}
}
TEST_F(helper_scalar_av_1024_uf1_rsum, test_3_ow_64_rsum)
{
	generated::rsum::helper::scalar::rsum(helper::delta_arr_ow64, transposed64, helper::base_arr_ow64);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(transposed64[i], helper::transposed_arr_ow64[i]);
	}
	generated::untranspose::helper::scalar::untranspose_o(transposed64, untransposed64);
	for (int i = 0; i < 1024; ++i)
	{
		ASSERT_EQ(helper::untransposed_arr_ow64[i], untransposed64[i]);
	}
}
