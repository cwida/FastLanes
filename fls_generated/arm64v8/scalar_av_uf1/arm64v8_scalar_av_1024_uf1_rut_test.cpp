#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"
#include <rut/rut.hpp>
#include "arm64v8_scalar_av_1024_uf1_rut_helper.hpp"
TEST_CASE( "test transpose", "[transpose]" )
{
	auto *transposed8 = new int8_t[1024]();
	auto *transposed16 = new int16_t[1024]();
	auto *transposed32 = new int32_t[1024]();
	auto *transposed64 = new int64_t[1024]();
	auto *untransposed8 = new int8_t[1024]();
	auto *untransposed16 = new int16_t[1024]();
	auto *untransposed32 = new int32_t[1024]();
	auto *untransposed64 = new int64_t[1024]();
	SECTION("test 0: ow = 8 i-i")
	{
		rut::scalar::transpose_i(helper::range_ow8, transposed8);
		rut::scalar::untranspose_i(transposed8, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 1: ow = 8 i-o")
	{
		rut::scalar::transpose_i(helper::range_ow8, transposed8);
		rut::scalar::untranspose_o(transposed8, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 2: ow = 8 o-i")
	{
		rut::scalar::transpose_o(helper::range_ow8, transposed8);
		rut::scalar::untranspose_i(transposed8, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 3: ow = 8 o-o")
	{
		rut::scalar::transpose_o(helper::range_ow8, transposed8);
		rut::scalar::untranspose_o(transposed8, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 4: ow = 8 rsum")
	{
		rut::scalar::rsum(helper::delta_arr_ow8, transposed8, helper::base_arr_ow8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(transposed8[i] == (helper::transposed_arr_ow8[i]));
		}
		rut::scalar::untranspose_o(transposed8, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 5: ow = 8 rsum_and_untranspose")
	{
		rut::scalar::rsum_and_untranspose(helper::delta_arr_ow8, untransposed8, helper::base_arr_ow8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 6: ow = 16 i-i")
	{
		rut::scalar::transpose_i(helper::range_ow16, transposed16);
		rut::scalar::untranspose_i(transposed16, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 7: ow = 16 i-o")
	{
		rut::scalar::transpose_i(helper::range_ow16, transposed16);
		rut::scalar::untranspose_o(transposed16, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 8: ow = 16 o-i")
	{
		rut::scalar::transpose_o(helper::range_ow16, transposed16);
		rut::scalar::untranspose_i(transposed16, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 9: ow = 16 o-o")
	{
		rut::scalar::transpose_o(helper::range_ow16, transposed16);
		rut::scalar::untranspose_o(transposed16, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 10: ow = 16 rsum")
	{
		rut::scalar::rsum(helper::delta_arr_ow16, transposed16, helper::base_arr_ow16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(transposed16[i] == (helper::transposed_arr_ow16[i]));
		}
		rut::scalar::untranspose_o(transposed16, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 11: ow = 16 rsum_and_untranspose")
	{
		rut::scalar::rsum_and_untranspose(helper::delta_arr_ow16, untransposed16, helper::base_arr_ow16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 12: ow = 32 i-i")
	{
		rut::scalar::transpose_i(helper::range_ow32, transposed32);
		rut::scalar::untranspose_i(transposed32, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 13: ow = 32 i-o")
	{
		rut::scalar::transpose_i(helper::range_ow32, transposed32);
		rut::scalar::untranspose_o(transposed32, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 14: ow = 32 o-i")
	{
		rut::scalar::transpose_o(helper::range_ow32, transposed32);
		rut::scalar::untranspose_i(transposed32, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 15: ow = 32 o-o")
	{
		rut::scalar::transpose_o(helper::range_ow32, transposed32);
		rut::scalar::untranspose_o(transposed32, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 16: ow = 32 rsum")
	{
		rut::scalar::rsum(helper::delta_arr_ow32, transposed32, helper::base_arr_ow32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(transposed32[i] == (helper::transposed_arr_ow32[i]));
		}
		rut::scalar::untranspose_o(transposed32, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 17: ow = 32 rsum_and_untranspose")
	{
		rut::scalar::rsum_and_untranspose(helper::delta_arr_ow32, untransposed32, helper::base_arr_ow32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 18: ow = 64 i-i")
	{
		rut::scalar::transpose_i(helper::range_ow64, transposed64);
		rut::scalar::untranspose_i(transposed64, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 19: ow = 64 i-o")
	{
		rut::scalar::transpose_i(helper::range_ow64, transposed64);
		rut::scalar::untranspose_o(transposed64, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 20: ow = 64 o-i")
	{
		rut::scalar::transpose_o(helper::range_ow64, transposed64);
		rut::scalar::untranspose_i(transposed64, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 21: ow = 64 o-o")
	{
		rut::scalar::transpose_o(helper::range_ow64, transposed64);
		rut::scalar::untranspose_o(transposed64, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::range_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 22: ow = 64 rsum")
	{
		rut::scalar::rsum(helper::delta_arr_ow64, transposed64, helper::base_arr_ow64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(transposed64[i] == (helper::transposed_arr_ow64[i]));
		}
		rut::scalar::untranspose_o(transposed64, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 23: ow = 64 rsum_and_untranspose")
	{
		rut::scalar::rsum_and_untranspose(helper::delta_arr_ow64, untransposed64, helper::base_arr_ow64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 24: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow8, helper::rle_runs1_len_arr_ow8, 4, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 25: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow8, helper::rle_runs1_len_arr_ow8, 4, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 26: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow16, helper::rle_runs1_len_arr_ow16, 4, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 27: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow16, helper::rle_runs1_len_arr_ow16, 4, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 28: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow32, helper::rle_runs1_len_arr_ow32, 4, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 29: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow32, helper::rle_runs1_len_arr_ow32, 4, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 30: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow64, helper::rle_runs1_len_arr_ow64, 4, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 31: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow64, helper::rle_runs1_len_arr_ow64, 4, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs1_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 32: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow8, helper::rle_runs2_len_arr_ow8, 5, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 33: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow8, helper::rle_runs2_len_arr_ow8, 5, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 34: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow16, helper::rle_runs2_len_arr_ow16, 5, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 35: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow16, helper::rle_runs2_len_arr_ow16, 5, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 36: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow32, helper::rle_runs2_len_arr_ow32, 5, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 37: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow32, helper::rle_runs2_len_arr_ow32, 5, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 38: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow64, helper::rle_runs2_len_arr_ow64, 5, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 39: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow64, helper::rle_runs2_len_arr_ow64, 5, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs2_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 40: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow8, helper::rle_runs3_len_arr_ow8, 6, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 41: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow8, helper::rle_runs3_len_arr_ow8, 6, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 42: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow16, helper::rle_runs3_len_arr_ow16, 6, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 43: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow16, helper::rle_runs3_len_arr_ow16, 6, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 44: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow32, helper::rle_runs3_len_arr_ow32, 6, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 45: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow32, helper::rle_runs3_len_arr_ow32, 6, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 46: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow64, helper::rle_runs3_len_arr_ow64, 6, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 47: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow64, helper::rle_runs3_len_arr_ow64, 6, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs3_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 48: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow8, helper::rle_runs4_len_arr_ow8, 7, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 49: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow8, helper::rle_runs4_len_arr_ow8, 7, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 50: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow16, helper::rle_runs4_len_arr_ow16, 7, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 51: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow16, helper::rle_runs4_len_arr_ow16, 7, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 52: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow32, helper::rle_runs4_len_arr_ow32, 7, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 53: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow32, helper::rle_runs4_len_arr_ow32, 7, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 54: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow64, helper::rle_runs4_len_arr_ow64, 7, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 55: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow64, helper::rle_runs4_len_arr_ow64, 7, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs4_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 56: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow8, helper::rle_runs5_len_arr_ow8, 8, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 57: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow8, helper::rle_runs5_len_arr_ow8, 8, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 58: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow16, helper::rle_runs5_len_arr_ow16, 8, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 59: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow16, helper::rle_runs5_len_arr_ow16, 8, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 60: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow32, helper::rle_runs5_len_arr_ow32, 8, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 61: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow32, helper::rle_runs5_len_arr_ow32, 8, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 62: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow64, helper::rle_runs5_len_arr_ow64, 8, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 63: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow64, helper::rle_runs5_len_arr_ow64, 8, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs5_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 64: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow8, helper::rle_runs6_len_arr_ow8, 9, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 65: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow8, helper::rle_runs6_len_arr_ow8, 9, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 66: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow16, helper::rle_runs6_len_arr_ow16, 9, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 67: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow16, helper::rle_runs6_len_arr_ow16, 9, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 68: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow32, helper::rle_runs6_len_arr_ow32, 9, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 69: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow32, helper::rle_runs6_len_arr_ow32, 9, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 70: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow64, helper::rle_runs6_len_arr_ow64, 9, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 71: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow64, helper::rle_runs6_len_arr_ow64, 9, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs6_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 72: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow8, helper::rle_runs7_len_arr_ow8, 10, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 73: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow8, helper::rle_runs7_len_arr_ow8, 10, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 74: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow16, helper::rle_runs7_len_arr_ow16, 10, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 75: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow16, helper::rle_runs7_len_arr_ow16, 10, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 76: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow32, helper::rle_runs7_len_arr_ow32, 10, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 77: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow32, helper::rle_runs7_len_arr_ow32, 10, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 78: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow64, helper::rle_runs7_len_arr_ow64, 10, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 79: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow64, helper::rle_runs7_len_arr_ow64, 10, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs7_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 80: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow8, helper::rle_runs8_len_arr_ow8, 11, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 81: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow8, helper::rle_runs8_len_arr_ow8, 11, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 82: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow16, helper::rle_runs8_len_arr_ow16, 11, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 83: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow16, helper::rle_runs8_len_arr_ow16, 11, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 84: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow32, helper::rle_runs8_len_arr_ow32, 11, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 85: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow32, helper::rle_runs8_len_arr_ow32, 11, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 86: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow64, helper::rle_runs8_len_arr_ow64, 11, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 87: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow64, helper::rle_runs8_len_arr_ow64, 11, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs8_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 88: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow8, helper::rle_runs9_len_arr_ow8, 12, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 89: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow8, helper::rle_runs9_len_arr_ow8, 12, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 90: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow16, helper::rle_runs9_len_arr_ow16, 12, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 91: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow16, helper::rle_runs9_len_arr_ow16, 12, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 92: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow32, helper::rle_runs9_len_arr_ow32, 12, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 93: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow32, helper::rle_runs9_len_arr_ow32, 12, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 94: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow64, helper::rle_runs9_len_arr_ow64, 12, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 95: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow64, helper::rle_runs9_len_arr_ow64, 12, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs9_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 96: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow8, helper::rle_runs10_len_arr_ow8, 13, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 97: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow8, helper::rle_runs10_len_arr_ow8, 13, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 98: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow16, helper::rle_runs10_len_arr_ow16, 13, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 99: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow16, helper::rle_runs10_len_arr_ow16, 13, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 100: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow32, helper::rle_runs10_len_arr_ow32, 13, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 101: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow32, helper::rle_runs10_len_arr_ow32, 13, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 102: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow64, helper::rle_runs10_len_arr_ow64, 13, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 103: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow64, helper::rle_runs10_len_arr_ow64, 13, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs10_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 104: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow8, helper::rle_runs11_len_arr_ow8, 14, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 105: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow8, helper::rle_runs11_len_arr_ow8, 14, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 106: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow16, helper::rle_runs11_len_arr_ow16, 14, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 107: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow16, helper::rle_runs11_len_arr_ow16, 14, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 108: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow32, helper::rle_runs11_len_arr_ow32, 14, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 109: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow32, helper::rle_runs11_len_arr_ow32, 14, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 110: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow64, helper::rle_runs11_len_arr_ow64, 14, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 111: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow64, helper::rle_runs11_len_arr_ow64, 14, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs11_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 112: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow8, helper::rle_runs12_len_arr_ow8, 14, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 113: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow8, helper::rle_runs12_len_arr_ow8, 14, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 114: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow16, helper::rle_runs12_len_arr_ow16, 14, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 115: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow16, helper::rle_runs12_len_arr_ow16, 14, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 116: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow32, helper::rle_runs12_len_arr_ow32, 14, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 117: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow32, helper::rle_runs12_len_arr_ow32, 14, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 118: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow64, helper::rle_runs12_len_arr_ow64, 14, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 119: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow64, helper::rle_runs12_len_arr_ow64, 14, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs12_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 120: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow8, helper::rle_runs13_len_arr_ow8, 16, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 121: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow8, helper::rle_runs13_len_arr_ow8, 16, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 122: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow16, helper::rle_runs13_len_arr_ow16, 16, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 123: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow16, helper::rle_runs13_len_arr_ow16, 16, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 124: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow32, helper::rle_runs13_len_arr_ow32, 16, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 125: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow32, helper::rle_runs13_len_arr_ow32, 16, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 126: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow64, helper::rle_runs13_len_arr_ow64, 16, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 127: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow64, helper::rle_runs13_len_arr_ow64, 16, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs13_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 128: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow8, helper::rle_runs14_len_arr_ow8, 17, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 129: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow8, helper::rle_runs14_len_arr_ow8, 17, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 130: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow16, helper::rle_runs14_len_arr_ow16, 17, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 131: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow16, helper::rle_runs14_len_arr_ow16, 17, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 132: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow32, helper::rle_runs14_len_arr_ow32, 17, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 133: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow32, helper::rle_runs14_len_arr_ow32, 17, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 134: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow64, helper::rle_runs14_len_arr_ow64, 17, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 135: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow64, helper::rle_runs14_len_arr_ow64, 17, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs14_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 136: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow8, helper::rle_runs15_len_arr_ow8, 18, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 137: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow8, helper::rle_runs15_len_arr_ow8, 18, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 138: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow16, helper::rle_runs15_len_arr_ow16, 18, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 139: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow16, helper::rle_runs15_len_arr_ow16, 18, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 140: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow32, helper::rle_runs15_len_arr_ow32, 18, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 141: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow32, helper::rle_runs15_len_arr_ow32, 18, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 142: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow64, helper::rle_runs15_len_arr_ow64, 18, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 143: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow64, helper::rle_runs15_len_arr_ow64, 18, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs15_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 144: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow8, helper::rle_runs16_len_arr_ow8, 19, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 145: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow8, helper::rle_runs16_len_arr_ow8, 19, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 146: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow16, helper::rle_runs16_len_arr_ow16, 19, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 147: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow16, helper::rle_runs16_len_arr_ow16, 19, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 148: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow32, helper::rle_runs16_len_arr_ow32, 19, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 149: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow32, helper::rle_runs16_len_arr_ow32, 19, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 150: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow64, helper::rle_runs16_len_arr_ow64, 19, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 151: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow64, helper::rle_runs16_len_arr_ow64, 19, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs16_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 152: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow8, helper::rle_runs17_len_arr_ow8, 20, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 153: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow8, helper::rle_runs17_len_arr_ow8, 20, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 154: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow16, helper::rle_runs17_len_arr_ow16, 20, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 155: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow16, helper::rle_runs17_len_arr_ow16, 20, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 156: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow32, helper::rle_runs17_len_arr_ow32, 20, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 157: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow32, helper::rle_runs17_len_arr_ow32, 20, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 158: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow64, helper::rle_runs17_len_arr_ow64, 20, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 159: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow64, helper::rle_runs17_len_arr_ow64, 20, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs17_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 160: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow8, helper::rle_runs18_len_arr_ow8, 21, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 161: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow8, helper::rle_runs18_len_arr_ow8, 21, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 162: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow16, helper::rle_runs18_len_arr_ow16, 21, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 163: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow16, helper::rle_runs18_len_arr_ow16, 21, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 164: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow32, helper::rle_runs18_len_arr_ow32, 21, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 165: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow32, helper::rle_runs18_len_arr_ow32, 21, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 166: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow64, helper::rle_runs18_len_arr_ow64, 21, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 167: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow64, helper::rle_runs18_len_arr_ow64, 21, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs18_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 168: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow8, helper::rle_runs19_len_arr_ow8, 22, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 169: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow8, helper::rle_runs19_len_arr_ow8, 22, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 170: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow16, helper::rle_runs19_len_arr_ow16, 22, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 171: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow16, helper::rle_runs19_len_arr_ow16, 22, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 172: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow32, helper::rle_runs19_len_arr_ow32, 22, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 173: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow32, helper::rle_runs19_len_arr_ow32, 22, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 174: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow64, helper::rle_runs19_len_arr_ow64, 22, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 175: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow64, helper::rle_runs19_len_arr_ow64, 22, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs19_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 176: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow8, helper::rle_runs20_len_arr_ow8, 23, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 177: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow8, helper::rle_runs20_len_arr_ow8, 23, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 178: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow16, helper::rle_runs20_len_arr_ow16, 23, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 179: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow16, helper::rle_runs20_len_arr_ow16, 23, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 180: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow32, helper::rle_runs20_len_arr_ow32, 23, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 181: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow32, helper::rle_runs20_len_arr_ow32, 23, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 182: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow64, helper::rle_runs20_len_arr_ow64, 23, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 183: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow64, helper::rle_runs20_len_arr_ow64, 23, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs20_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 184: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow8, helper::rle_runs21_len_arr_ow8, 24, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 185: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow8, helper::rle_runs21_len_arr_ow8, 24, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 186: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow16, helper::rle_runs21_len_arr_ow16, 24, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 187: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow16, helper::rle_runs21_len_arr_ow16, 24, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 188: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow32, helper::rle_runs21_len_arr_ow32, 24, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 189: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow32, helper::rle_runs21_len_arr_ow32, 24, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 190: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow64, helper::rle_runs21_len_arr_ow64, 24, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 191: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow64, helper::rle_runs21_len_arr_ow64, 24, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs21_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 192: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow8, helper::rle_runs22_len_arr_ow8, 25, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 193: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow8, helper::rle_runs22_len_arr_ow8, 25, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 194: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow16, helper::rle_runs22_len_arr_ow16, 25, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 195: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow16, helper::rle_runs22_len_arr_ow16, 25, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 196: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow32, helper::rle_runs22_len_arr_ow32, 25, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 197: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow32, helper::rle_runs22_len_arr_ow32, 25, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 198: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow64, helper::rle_runs22_len_arr_ow64, 25, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 199: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow64, helper::rle_runs22_len_arr_ow64, 25, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs22_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 200: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow8, helper::rle_runs23_len_arr_ow8, 26, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 201: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow8, helper::rle_runs23_len_arr_ow8, 26, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 202: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow16, helper::rle_runs23_len_arr_ow16, 26, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 203: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow16, helper::rle_runs23_len_arr_ow16, 26, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 204: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow32, helper::rle_runs23_len_arr_ow32, 26, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 205: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow32, helper::rle_runs23_len_arr_ow32, 26, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 206: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow64, helper::rle_runs23_len_arr_ow64, 26, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 207: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow64, helper::rle_runs23_len_arr_ow64, 26, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs23_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 208: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow8, helper::rle_runs24_len_arr_ow8, 27, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 209: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow8, helper::rle_runs24_len_arr_ow8, 27, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 210: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow16, helper::rle_runs24_len_arr_ow16, 27, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 211: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow16, helper::rle_runs24_len_arr_ow16, 27, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 212: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow32, helper::rle_runs24_len_arr_ow32, 27, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 213: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow32, helper::rle_runs24_len_arr_ow32, 27, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 214: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow64, helper::rle_runs24_len_arr_ow64, 27, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 215: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow64, helper::rle_runs24_len_arr_ow64, 27, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs24_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 216: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow8, helper::rle_runs25_len_arr_ow8, 28, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 217: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow8, helper::rle_runs25_len_arr_ow8, 28, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 218: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow16, helper::rle_runs25_len_arr_ow16, 28, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 219: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow16, helper::rle_runs25_len_arr_ow16, 28, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 220: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow32, helper::rle_runs25_len_arr_ow32, 28, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 221: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow32, helper::rle_runs25_len_arr_ow32, 28, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 222: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow64, helper::rle_runs25_len_arr_ow64, 28, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 223: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow64, helper::rle_runs25_len_arr_ow64, 28, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs25_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 224: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow8, helper::rle_runs26_len_arr_ow8, 28, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 225: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow8, helper::rle_runs26_len_arr_ow8, 28, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 226: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow16, helper::rle_runs26_len_arr_ow16, 28, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 227: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow16, helper::rle_runs26_len_arr_ow16, 28, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 228: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow32, helper::rle_runs26_len_arr_ow32, 28, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 229: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow32, helper::rle_runs26_len_arr_ow32, 28, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 230: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow64, helper::rle_runs26_len_arr_ow64, 28, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 231: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow64, helper::rle_runs26_len_arr_ow64, 28, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs26_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 232: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow8, helper::rle_runs27_len_arr_ow8, 30, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 233: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow8, helper::rle_runs27_len_arr_ow8, 30, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 234: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow16, helper::rle_runs27_len_arr_ow16, 30, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 235: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow16, helper::rle_runs27_len_arr_ow16, 30, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 236: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow32, helper::rle_runs27_len_arr_ow32, 30, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 237: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow32, helper::rle_runs27_len_arr_ow32, 30, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 238: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow64, helper::rle_runs27_len_arr_ow64, 30, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 239: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow64, helper::rle_runs27_len_arr_ow64, 30, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs27_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 240: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow8, helper::rle_runs28_len_arr_ow8, 31, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 241: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow8, helper::rle_runs28_len_arr_ow8, 31, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 242: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow16, helper::rle_runs28_len_arr_ow16, 31, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 243: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow16, helper::rle_runs28_len_arr_ow16, 31, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 244: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow32, helper::rle_runs28_len_arr_ow32, 31, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 245: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow32, helper::rle_runs28_len_arr_ow32, 31, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 246: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow64, helper::rle_runs28_len_arr_ow64, 31, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 247: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow64, helper::rle_runs28_len_arr_ow64, 31, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs28_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 248: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow8, helper::rle_runs29_len_arr_ow8, 31, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 249: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow8, helper::rle_runs29_len_arr_ow8, 31, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 250: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow16, helper::rle_runs29_len_arr_ow16, 31, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 251: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow16, helper::rle_runs29_len_arr_ow16, 31, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 252: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow32, helper::rle_runs29_len_arr_ow32, 31, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 253: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow32, helper::rle_runs29_len_arr_ow32, 31, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 254: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow64, helper::rle_runs29_len_arr_ow64, 31, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 255: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow64, helper::rle_runs29_len_arr_ow64, 31, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs29_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 256: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow8, helper::rle_runs30_len_arr_ow8, 33, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 257: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow8, helper::rle_runs30_len_arr_ow8, 33, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 258: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow16, helper::rle_runs30_len_arr_ow16, 33, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 259: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow16, helper::rle_runs30_len_arr_ow16, 33, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 260: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow32, helper::rle_runs30_len_arr_ow32, 33, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 261: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow32, helper::rle_runs30_len_arr_ow32, 33, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 262: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow64, helper::rle_runs30_len_arr_ow64, 33, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 263: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow64, helper::rle_runs30_len_arr_ow64, 33, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs30_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 264: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow8, helper::rle_runs31_len_arr_ow8, 34, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 265: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow8, helper::rle_runs31_len_arr_ow8, 34, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 266: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow16, helper::rle_runs31_len_arr_ow16, 34, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 267: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow16, helper::rle_runs31_len_arr_ow16, 34, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 268: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow32, helper::rle_runs31_len_arr_ow32, 34, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 269: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow32, helper::rle_runs31_len_arr_ow32, 34, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 270: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow64, helper::rle_runs31_len_arr_ow64, 34, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 271: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow64, helper::rle_runs31_len_arr_ow64, 34, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs31_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 272: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow8, helper::rle_runs32_len_arr_ow8, 35, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 273: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow8, helper::rle_runs32_len_arr_ow8, 35, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 274: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow16, helper::rle_runs32_len_arr_ow16, 35, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 275: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow16, helper::rle_runs32_len_arr_ow16, 35, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 276: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow32, helper::rle_runs32_len_arr_ow32, 35, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 277: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow32, helper::rle_runs32_len_arr_ow32, 35, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 278: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow64, helper::rle_runs32_len_arr_ow64, 35, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 279: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow64, helper::rle_runs32_len_arr_ow64, 35, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs32_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 280: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow8, helper::rle_runs33_len_arr_ow8, 35, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 281: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow8, helper::rle_runs33_len_arr_ow8, 35, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 282: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow16, helper::rle_runs33_len_arr_ow16, 35, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 283: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow16, helper::rle_runs33_len_arr_ow16, 35, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 284: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow32, helper::rle_runs33_len_arr_ow32, 35, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 285: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow32, helper::rle_runs33_len_arr_ow32, 35, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 286: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow64, helper::rle_runs33_len_arr_ow64, 35, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 287: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow64, helper::rle_runs33_len_arr_ow64, 35, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs33_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 288: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow8, helper::rle_runs34_len_arr_ow8, 37, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 289: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow8, helper::rle_runs34_len_arr_ow8, 37, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 290: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow16, helper::rle_runs34_len_arr_ow16, 37, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 291: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow16, helper::rle_runs34_len_arr_ow16, 37, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 292: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow32, helper::rle_runs34_len_arr_ow32, 37, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 293: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow32, helper::rle_runs34_len_arr_ow32, 37, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 294: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow64, helper::rle_runs34_len_arr_ow64, 37, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 295: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow64, helper::rle_runs34_len_arr_ow64, 37, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs34_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 296: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow8, helper::rle_runs35_len_arr_ow8, 38, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 297: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow8, helper::rle_runs35_len_arr_ow8, 38, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 298: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow16, helper::rle_runs35_len_arr_ow16, 38, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 299: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow16, helper::rle_runs35_len_arr_ow16, 38, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 300: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow32, helper::rle_runs35_len_arr_ow32, 38, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 301: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow32, helper::rle_runs35_len_arr_ow32, 38, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 302: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow64, helper::rle_runs35_len_arr_ow64, 38, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 303: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow64, helper::rle_runs35_len_arr_ow64, 38, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs35_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 304: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow8, helper::rle_runs36_len_arr_ow8, 39, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 305: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow8, helper::rle_runs36_len_arr_ow8, 39, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 306: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow16, helper::rle_runs36_len_arr_ow16, 39, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 307: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow16, helper::rle_runs36_len_arr_ow16, 39, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 308: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow32, helper::rle_runs36_len_arr_ow32, 39, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 309: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow32, helper::rle_runs36_len_arr_ow32, 39, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 310: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow64, helper::rle_runs36_len_arr_ow64, 39, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 311: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow64, helper::rle_runs36_len_arr_ow64, 39, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs36_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 312: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow8, helper::rle_runs37_len_arr_ow8, 39, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 313: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow8, helper::rle_runs37_len_arr_ow8, 39, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 314: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow16, helper::rle_runs37_len_arr_ow16, 39, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 315: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow16, helper::rle_runs37_len_arr_ow16, 39, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 316: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow32, helper::rle_runs37_len_arr_ow32, 39, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 317: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow32, helper::rle_runs37_len_arr_ow32, 39, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 318: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow64, helper::rle_runs37_len_arr_ow64, 39, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 319: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow64, helper::rle_runs37_len_arr_ow64, 39, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs37_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 320: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow8, helper::rle_runs38_len_arr_ow8, 41, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 321: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow8, helper::rle_runs38_len_arr_ow8, 41, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 322: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow16, helper::rle_runs38_len_arr_ow16, 41, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 323: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow16, helper::rle_runs38_len_arr_ow16, 41, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 324: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow32, helper::rle_runs38_len_arr_ow32, 41, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 325: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow32, helper::rle_runs38_len_arr_ow32, 41, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 326: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow64, helper::rle_runs38_len_arr_ow64, 41, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 327: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow64, helper::rle_runs38_len_arr_ow64, 41, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs38_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 328: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow8, helper::rle_runs39_len_arr_ow8, 42, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 329: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow8, helper::rle_runs39_len_arr_ow8, 42, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 330: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow16, helper::rle_runs39_len_arr_ow16, 42, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 331: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow16, helper::rle_runs39_len_arr_ow16, 42, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 332: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow32, helper::rle_runs39_len_arr_ow32, 42, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 333: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow32, helper::rle_runs39_len_arr_ow32, 42, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 334: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow64, helper::rle_runs39_len_arr_ow64, 42, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 335: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow64, helper::rle_runs39_len_arr_ow64, 42, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs39_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 336: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow8, helper::rle_runs40_len_arr_ow8, 43, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 337: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow8, helper::rle_runs40_len_arr_ow8, 43, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 338: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow16, helper::rle_runs40_len_arr_ow16, 43, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 339: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow16, helper::rle_runs40_len_arr_ow16, 43, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 340: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow32, helper::rle_runs40_len_arr_ow32, 43, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 341: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow32, helper::rle_runs40_len_arr_ow32, 43, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 342: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow64, helper::rle_runs40_len_arr_ow64, 43, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 343: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow64, helper::rle_runs40_len_arr_ow64, 43, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs40_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 344: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow8, helper::rle_runs41_len_arr_ow8, 44, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 345: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow8, helper::rle_runs41_len_arr_ow8, 44, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 346: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow16, helper::rle_runs41_len_arr_ow16, 44, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 347: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow16, helper::rle_runs41_len_arr_ow16, 44, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 348: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow32, helper::rle_runs41_len_arr_ow32, 44, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 349: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow32, helper::rle_runs41_len_arr_ow32, 44, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 350: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow64, helper::rle_runs41_len_arr_ow64, 44, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 351: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow64, helper::rle_runs41_len_arr_ow64, 44, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs41_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 352: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow8, helper::rle_runs42_len_arr_ow8, 45, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 353: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow8, helper::rle_runs42_len_arr_ow8, 45, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 354: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow16, helper::rle_runs42_len_arr_ow16, 45, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 355: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow16, helper::rle_runs42_len_arr_ow16, 45, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 356: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow32, helper::rle_runs42_len_arr_ow32, 45, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 357: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow32, helper::rle_runs42_len_arr_ow32, 45, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 358: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow64, helper::rle_runs42_len_arr_ow64, 45, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 359: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow64, helper::rle_runs42_len_arr_ow64, 45, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs42_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 360: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow8, helper::rle_runs43_len_arr_ow8, 45, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 361: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow8, helper::rle_runs43_len_arr_ow8, 45, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 362: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow16, helper::rle_runs43_len_arr_ow16, 45, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 363: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow16, helper::rle_runs43_len_arr_ow16, 45, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 364: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow32, helper::rle_runs43_len_arr_ow32, 45, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 365: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow32, helper::rle_runs43_len_arr_ow32, 45, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 366: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow64, helper::rle_runs43_len_arr_ow64, 45, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 367: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow64, helper::rle_runs43_len_arr_ow64, 45, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs43_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 368: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow8, helper::rle_runs44_len_arr_ow8, 47, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 369: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow8, helper::rle_runs44_len_arr_ow8, 47, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 370: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow16, helper::rle_runs44_len_arr_ow16, 47, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 371: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow16, helper::rle_runs44_len_arr_ow16, 47, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 372: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow32, helper::rle_runs44_len_arr_ow32, 47, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 373: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow32, helper::rle_runs44_len_arr_ow32, 47, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 374: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow64, helper::rle_runs44_len_arr_ow64, 47, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 375: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow64, helper::rle_runs44_len_arr_ow64, 47, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs44_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 376: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow8, helper::rle_runs45_len_arr_ow8, 48, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 377: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow8, helper::rle_runs45_len_arr_ow8, 48, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 378: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow16, helper::rle_runs45_len_arr_ow16, 48, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 379: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow16, helper::rle_runs45_len_arr_ow16, 48, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 380: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow32, helper::rle_runs45_len_arr_ow32, 48, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 381: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow32, helper::rle_runs45_len_arr_ow32, 48, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 382: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow64, helper::rle_runs45_len_arr_ow64, 48, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 383: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow64, helper::rle_runs45_len_arr_ow64, 48, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs45_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 384: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow8, helper::rle_runs46_len_arr_ow8, 49, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 385: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow8, helper::rle_runs46_len_arr_ow8, 49, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 386: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow16, helper::rle_runs46_len_arr_ow16, 49, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 387: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow16, helper::rle_runs46_len_arr_ow16, 49, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 388: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow32, helper::rle_runs46_len_arr_ow32, 49, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 389: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow32, helper::rle_runs46_len_arr_ow32, 49, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 390: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow64, helper::rle_runs46_len_arr_ow64, 49, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 391: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow64, helper::rle_runs46_len_arr_ow64, 49, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs46_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 392: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow8, helper::rle_runs47_len_arr_ow8, 50, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 393: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow8, helper::rle_runs47_len_arr_ow8, 50, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 394: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow16, helper::rle_runs47_len_arr_ow16, 50, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 395: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow16, helper::rle_runs47_len_arr_ow16, 50, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 396: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow32, helper::rle_runs47_len_arr_ow32, 50, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 397: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow32, helper::rle_runs47_len_arr_ow32, 50, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 398: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow64, helper::rle_runs47_len_arr_ow64, 50, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 399: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow64, helper::rle_runs47_len_arr_ow64, 50, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs47_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 400: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow8, helper::rle_runs48_len_arr_ow8, 51, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 401: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow8, helper::rle_runs48_len_arr_ow8, 51, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 402: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow16, helper::rle_runs48_len_arr_ow16, 51, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 403: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow16, helper::rle_runs48_len_arr_ow16, 51, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 404: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow32, helper::rle_runs48_len_arr_ow32, 51, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 405: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow32, helper::rle_runs48_len_arr_ow32, 51, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 406: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow64, helper::rle_runs48_len_arr_ow64, 51, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 407: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow64, helper::rle_runs48_len_arr_ow64, 51, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs48_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 408: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow8, helper::rle_runs49_len_arr_ow8, 52, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 409: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow8, helper::rle_runs49_len_arr_ow8, 52, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 410: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow16, helper::rle_runs49_len_arr_ow16, 52, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 411: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow16, helper::rle_runs49_len_arr_ow16, 52, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 412: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow32, helper::rle_runs49_len_arr_ow32, 52, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 413: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow32, helper::rle_runs49_len_arr_ow32, 52, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 414: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow64, helper::rle_runs49_len_arr_ow64, 52, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 415: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow64, helper::rle_runs49_len_arr_ow64, 52, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs49_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 416: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow8, helper::rle_runs50_len_arr_ow8, 53, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 417: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow8, helper::rle_runs50_len_arr_ow8, 53, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 418: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow16, helper::rle_runs50_len_arr_ow16, 53, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 419: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow16, helper::rle_runs50_len_arr_ow16, 53, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 420: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow32, helper::rle_runs50_len_arr_ow32, 53, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 421: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow32, helper::rle_runs50_len_arr_ow32, 53, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 422: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow64, helper::rle_runs50_len_arr_ow64, 53, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 423: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow64, helper::rle_runs50_len_arr_ow64, 53, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs50_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 424: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow8, helper::rle_runs51_len_arr_ow8, 54, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 425: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow8, helper::rle_runs51_len_arr_ow8, 54, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 426: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow16, helper::rle_runs51_len_arr_ow16, 54, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 427: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow16, helper::rle_runs51_len_arr_ow16, 54, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 428: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow32, helper::rle_runs51_len_arr_ow32, 54, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 429: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow32, helper::rle_runs51_len_arr_ow32, 54, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 430: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow64, helper::rle_runs51_len_arr_ow64, 54, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 431: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow64, helper::rle_runs51_len_arr_ow64, 54, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs51_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 432: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow8, helper::rle_runs52_len_arr_ow8, 55, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 433: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow8, helper::rle_runs52_len_arr_ow8, 55, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 434: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow16, helper::rle_runs52_len_arr_ow16, 55, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 435: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow16, helper::rle_runs52_len_arr_ow16, 55, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 436: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow32, helper::rle_runs52_len_arr_ow32, 55, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 437: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow32, helper::rle_runs52_len_arr_ow32, 55, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 438: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow64, helper::rle_runs52_len_arr_ow64, 55, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 439: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow64, helper::rle_runs52_len_arr_ow64, 55, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs52_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 440: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow8, helper::rle_runs53_len_arr_ow8, 55, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 441: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow8, helper::rle_runs53_len_arr_ow8, 55, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 442: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow16, helper::rle_runs53_len_arr_ow16, 55, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 443: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow16, helper::rle_runs53_len_arr_ow16, 55, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 444: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow32, helper::rle_runs53_len_arr_ow32, 55, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 445: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow32, helper::rle_runs53_len_arr_ow32, 55, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 446: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow64, helper::rle_runs53_len_arr_ow64, 55, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 447: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow64, helper::rle_runs53_len_arr_ow64, 55, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs53_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 448: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow8, helper::rle_runs54_len_arr_ow8, 56, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 449: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow8, helper::rle_runs54_len_arr_ow8, 56, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 450: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow16, helper::rle_runs54_len_arr_ow16, 56, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 451: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow16, helper::rle_runs54_len_arr_ow16, 56, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 452: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow32, helper::rle_runs54_len_arr_ow32, 56, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 453: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow32, helper::rle_runs54_len_arr_ow32, 56, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 454: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow64, helper::rle_runs54_len_arr_ow64, 56, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 455: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow64, helper::rle_runs54_len_arr_ow64, 56, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs54_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 456: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow8, helper::rle_runs55_len_arr_ow8, 58, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 457: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow8, helper::rle_runs55_len_arr_ow8, 58, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 458: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow16, helper::rle_runs55_len_arr_ow16, 58, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 459: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow16, helper::rle_runs55_len_arr_ow16, 58, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 460: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow32, helper::rle_runs55_len_arr_ow32, 58, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 461: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow32, helper::rle_runs55_len_arr_ow32, 58, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 462: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow64, helper::rle_runs55_len_arr_ow64, 58, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 463: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow64, helper::rle_runs55_len_arr_ow64, 58, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs55_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 464: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow8, helper::rle_runs56_len_arr_ow8, 59, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 465: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow8, helper::rle_runs56_len_arr_ow8, 59, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 466: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow16, helper::rle_runs56_len_arr_ow16, 59, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 467: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow16, helper::rle_runs56_len_arr_ow16, 59, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 468: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow32, helper::rle_runs56_len_arr_ow32, 59, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 469: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow32, helper::rle_runs56_len_arr_ow32, 59, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 470: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow64, helper::rle_runs56_len_arr_ow64, 59, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 471: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow64, helper::rle_runs56_len_arr_ow64, 59, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs56_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 472: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow8, helper::rle_runs57_len_arr_ow8, 59, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 473: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow8, helper::rle_runs57_len_arr_ow8, 59, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 474: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow16, helper::rle_runs57_len_arr_ow16, 59, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 475: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow16, helper::rle_runs57_len_arr_ow16, 59, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 476: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow32, helper::rle_runs57_len_arr_ow32, 59, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 477: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow32, helper::rle_runs57_len_arr_ow32, 59, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 478: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow64, helper::rle_runs57_len_arr_ow64, 59, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 479: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow64, helper::rle_runs57_len_arr_ow64, 59, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs57_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 480: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow8, helper::rle_runs58_len_arr_ow8, 61, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 481: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow8, helper::rle_runs58_len_arr_ow8, 61, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 482: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow16, helper::rle_runs58_len_arr_ow16, 61, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 483: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow16, helper::rle_runs58_len_arr_ow16, 61, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 484: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow32, helper::rle_runs58_len_arr_ow32, 61, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 485: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow32, helper::rle_runs58_len_arr_ow32, 61, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 486: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow64, helper::rle_runs58_len_arr_ow64, 61, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 487: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow64, helper::rle_runs58_len_arr_ow64, 61, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs58_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 488: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow8, helper::rle_runs59_len_arr_ow8, 62, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 489: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow8, helper::rle_runs59_len_arr_ow8, 62, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 490: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow16, helper::rle_runs59_len_arr_ow16, 62, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 491: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow16, helper::rle_runs59_len_arr_ow16, 62, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 492: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow32, helper::rle_runs59_len_arr_ow32, 62, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 493: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow32, helper::rle_runs59_len_arr_ow32, 62, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 494: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow64, helper::rle_runs59_len_arr_ow64, 62, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 495: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow64, helper::rle_runs59_len_arr_ow64, 62, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs59_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 496: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow8, helper::rle_runs60_len_arr_ow8, 63, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 497: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow8, helper::rle_runs60_len_arr_ow8, 63, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 498: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow16, helper::rle_runs60_len_arr_ow16, 63, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 499: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow16, helper::rle_runs60_len_arr_ow16, 63, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 500: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow32, helper::rle_runs60_len_arr_ow32, 63, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 501: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow32, helper::rle_runs60_len_arr_ow32, 63, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 502: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow64, helper::rle_runs60_len_arr_ow64, 63, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 503: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow64, helper::rle_runs60_len_arr_ow64, 63, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs60_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 504: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow8, helper::rle_runs61_len_arr_ow8, 64, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 505: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow8, helper::rle_runs61_len_arr_ow8, 64, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 506: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow16, helper::rle_runs61_len_arr_ow16, 64, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 507: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow16, helper::rle_runs61_len_arr_ow16, 64, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 508: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow32, helper::rle_runs61_len_arr_ow32, 64, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 509: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow32, helper::rle_runs61_len_arr_ow32, 64, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 510: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow64, helper::rle_runs61_len_arr_ow64, 64, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 511: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow64, helper::rle_runs61_len_arr_ow64, 64, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs61_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 512: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow8, helper::rle_runs62_len_arr_ow8, 65, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 513: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow8, helper::rle_runs62_len_arr_ow8, 65, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 514: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow16, helper::rle_runs62_len_arr_ow16, 65, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 515: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow16, helper::rle_runs62_len_arr_ow16, 65, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 516: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow32, helper::rle_runs62_len_arr_ow32, 65, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 517: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow32, helper::rle_runs62_len_arr_ow32, 65, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 518: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow64, helper::rle_runs62_len_arr_ow64, 65, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 519: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow64, helper::rle_runs62_len_arr_ow64, 65, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs62_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 520: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow8, helper::rle_runs63_len_arr_ow8, 66, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 521: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow8, helper::rle_runs63_len_arr_ow8, 66, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 522: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow16, helper::rle_runs63_len_arr_ow16, 66, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 523: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow16, helper::rle_runs63_len_arr_ow16, 66, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 524: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow32, helper::rle_runs63_len_arr_ow32, 66, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 525: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow32, helper::rle_runs63_len_arr_ow32, 66, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 526: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow64, helper::rle_runs63_len_arr_ow64, 66, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 527: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow64, helper::rle_runs63_len_arr_ow64, 66, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs63_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 528: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow8, helper::rle_runs64_len_arr_ow8, 67, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 529: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow8, helper::rle_runs64_len_arr_ow8, 67, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 530: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow16, helper::rle_runs64_len_arr_ow16, 67, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 531: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow16, helper::rle_runs64_len_arr_ow16, 67, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 532: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow32, helper::rle_runs64_len_arr_ow32, 67, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 533: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow32, helper::rle_runs64_len_arr_ow32, 67, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 534: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow64, helper::rle_runs64_len_arr_ow64, 67, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 535: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow64, helper::rle_runs64_len_arr_ow64, 67, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs64_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 536: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow8, helper::rle_runs65_len_arr_ow8, 67, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 537: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow8, helper::rle_runs65_len_arr_ow8, 67, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 538: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow16, helper::rle_runs65_len_arr_ow16, 67, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 539: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow16, helper::rle_runs65_len_arr_ow16, 67, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 540: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow32, helper::rle_runs65_len_arr_ow32, 67, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 541: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow32, helper::rle_runs65_len_arr_ow32, 67, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 542: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow64, helper::rle_runs65_len_arr_ow64, 67, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 543: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow64, helper::rle_runs65_len_arr_ow64, 67, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs65_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 544: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow8, helper::rle_runs66_len_arr_ow8, 69, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 545: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow8, helper::rle_runs66_len_arr_ow8, 69, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 546: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow16, helper::rle_runs66_len_arr_ow16, 69, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 547: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow16, helper::rle_runs66_len_arr_ow16, 69, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 548: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow32, helper::rle_runs66_len_arr_ow32, 69, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 549: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow32, helper::rle_runs66_len_arr_ow32, 69, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 550: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow64, helper::rle_runs66_len_arr_ow64, 69, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 551: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow64, helper::rle_runs66_len_arr_ow64, 69, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs66_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 552: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow8, helper::rle_runs67_len_arr_ow8, 70, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 553: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow8, helper::rle_runs67_len_arr_ow8, 70, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 554: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow16, helper::rle_runs67_len_arr_ow16, 70, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 555: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow16, helper::rle_runs67_len_arr_ow16, 70, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 556: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow32, helper::rle_runs67_len_arr_ow32, 70, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 557: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow32, helper::rle_runs67_len_arr_ow32, 70, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 558: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow64, helper::rle_runs67_len_arr_ow64, 70, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 559: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow64, helper::rle_runs67_len_arr_ow64, 70, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs67_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 560: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow8, helper::rle_runs68_len_arr_ow8, 71, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 561: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow8, helper::rle_runs68_len_arr_ow8, 71, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 562: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow16, helper::rle_runs68_len_arr_ow16, 71, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 563: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow16, helper::rle_runs68_len_arr_ow16, 71, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 564: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow32, helper::rle_runs68_len_arr_ow32, 71, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 565: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow32, helper::rle_runs68_len_arr_ow32, 71, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 566: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow64, helper::rle_runs68_len_arr_ow64, 71, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 567: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow64, helper::rle_runs68_len_arr_ow64, 71, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs68_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 568: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow8, helper::rle_runs69_len_arr_ow8, 71, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 569: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow8, helper::rle_runs69_len_arr_ow8, 71, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 570: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow16, helper::rle_runs69_len_arr_ow16, 71, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 571: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow16, helper::rle_runs69_len_arr_ow16, 71, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 572: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow32, helper::rle_runs69_len_arr_ow32, 71, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 573: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow32, helper::rle_runs69_len_arr_ow32, 71, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 574: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow64, helper::rle_runs69_len_arr_ow64, 71, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 575: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow64, helper::rle_runs69_len_arr_ow64, 71, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs69_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 576: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow8, helper::rle_runs70_len_arr_ow8, 73, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 577: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow8, helper::rle_runs70_len_arr_ow8, 73, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 578: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow16, helper::rle_runs70_len_arr_ow16, 73, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 579: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow16, helper::rle_runs70_len_arr_ow16, 73, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 580: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow32, helper::rle_runs70_len_arr_ow32, 73, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 581: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow32, helper::rle_runs70_len_arr_ow32, 73, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 582: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow64, helper::rle_runs70_len_arr_ow64, 73, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 583: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow64, helper::rle_runs70_len_arr_ow64, 73, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs70_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 584: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow8, helper::rle_runs71_len_arr_ow8, 74, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 585: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow8, helper::rle_runs71_len_arr_ow8, 74, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 586: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow16, helper::rle_runs71_len_arr_ow16, 74, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 587: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow16, helper::rle_runs71_len_arr_ow16, 74, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 588: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow32, helper::rle_runs71_len_arr_ow32, 74, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 589: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow32, helper::rle_runs71_len_arr_ow32, 74, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 590: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow64, helper::rle_runs71_len_arr_ow64, 74, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 591: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow64, helper::rle_runs71_len_arr_ow64, 74, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs71_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 592: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow8, helper::rle_runs72_len_arr_ow8, 75, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 593: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow8, helper::rle_runs72_len_arr_ow8, 75, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 594: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow16, helper::rle_runs72_len_arr_ow16, 75, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 595: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow16, helper::rle_runs72_len_arr_ow16, 75, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 596: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow32, helper::rle_runs72_len_arr_ow32, 75, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 597: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow32, helper::rle_runs72_len_arr_ow32, 75, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 598: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow64, helper::rle_runs72_len_arr_ow64, 75, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 599: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow64, helper::rle_runs72_len_arr_ow64, 75, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs72_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 600: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow8, helper::rle_runs73_len_arr_ow8, 76, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 601: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow8, helper::rle_runs73_len_arr_ow8, 76, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 602: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow16, helper::rle_runs73_len_arr_ow16, 76, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 603: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow16, helper::rle_runs73_len_arr_ow16, 76, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 604: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow32, helper::rle_runs73_len_arr_ow32, 76, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 605: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow32, helper::rle_runs73_len_arr_ow32, 76, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 606: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow64, helper::rle_runs73_len_arr_ow64, 76, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 607: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow64, helper::rle_runs73_len_arr_ow64, 76, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs73_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 608: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow8, helper::rle_runs74_len_arr_ow8, 77, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 609: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow8, helper::rle_runs74_len_arr_ow8, 77, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 610: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow16, helper::rle_runs74_len_arr_ow16, 77, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 611: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow16, helper::rle_runs74_len_arr_ow16, 77, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 612: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow32, helper::rle_runs74_len_arr_ow32, 77, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 613: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow32, helper::rle_runs74_len_arr_ow32, 77, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 614: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow64, helper::rle_runs74_len_arr_ow64, 77, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 615: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow64, helper::rle_runs74_len_arr_ow64, 77, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs74_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 616: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow8, helper::rle_runs75_len_arr_ow8, 76, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 617: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow8, helper::rle_runs75_len_arr_ow8, 76, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 618: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow16, helper::rle_runs75_len_arr_ow16, 76, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 619: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow16, helper::rle_runs75_len_arr_ow16, 76, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 620: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow32, helper::rle_runs75_len_arr_ow32, 76, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 621: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow32, helper::rle_runs75_len_arr_ow32, 76, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 622: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow64, helper::rle_runs75_len_arr_ow64, 76, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 623: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow64, helper::rle_runs75_len_arr_ow64, 76, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs75_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 624: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow8, helper::rle_runs76_len_arr_ow8, 79, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 625: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow8, helper::rle_runs76_len_arr_ow8, 79, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 626: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow16, helper::rle_runs76_len_arr_ow16, 79, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 627: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow16, helper::rle_runs76_len_arr_ow16, 79, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 628: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow32, helper::rle_runs76_len_arr_ow32, 79, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 629: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow32, helper::rle_runs76_len_arr_ow32, 79, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 630: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow64, helper::rle_runs76_len_arr_ow64, 79, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 631: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow64, helper::rle_runs76_len_arr_ow64, 79, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs76_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 632: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow8, helper::rle_runs77_len_arr_ow8, 80, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 633: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow8, helper::rle_runs77_len_arr_ow8, 80, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 634: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow16, helper::rle_runs77_len_arr_ow16, 80, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 635: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow16, helper::rle_runs77_len_arr_ow16, 80, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 636: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow32, helper::rle_runs77_len_arr_ow32, 80, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 637: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow32, helper::rle_runs77_len_arr_ow32, 80, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 638: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow64, helper::rle_runs77_len_arr_ow64, 80, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 639: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow64, helper::rle_runs77_len_arr_ow64, 80, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs77_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 640: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow8, helper::rle_runs78_len_arr_ow8, 81, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 641: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow8, helper::rle_runs78_len_arr_ow8, 81, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 642: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow16, helper::rle_runs78_len_arr_ow16, 81, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 643: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow16, helper::rle_runs78_len_arr_ow16, 81, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 644: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow32, helper::rle_runs78_len_arr_ow32, 81, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 645: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow32, helper::rle_runs78_len_arr_ow32, 81, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 646: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow64, helper::rle_runs78_len_arr_ow64, 81, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 647: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow64, helper::rle_runs78_len_arr_ow64, 81, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs78_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 648: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow8, helper::rle_runs79_len_arr_ow8, 82, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 649: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow8, helper::rle_runs79_len_arr_ow8, 82, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 650: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow16, helper::rle_runs79_len_arr_ow16, 82, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 651: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow16, helper::rle_runs79_len_arr_ow16, 82, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 652: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow32, helper::rle_runs79_len_arr_ow32, 82, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 653: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow32, helper::rle_runs79_len_arr_ow32, 82, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 654: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow64, helper::rle_runs79_len_arr_ow64, 82, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 655: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow64, helper::rle_runs79_len_arr_ow64, 82, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs79_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 656: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow8, helper::rle_runs80_len_arr_ow8, 83, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 657: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow8, helper::rle_runs80_len_arr_ow8, 83, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 658: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow16, helper::rle_runs80_len_arr_ow16, 83, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 659: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow16, helper::rle_runs80_len_arr_ow16, 83, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 660: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow32, helper::rle_runs80_len_arr_ow32, 83, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 661: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow32, helper::rle_runs80_len_arr_ow32, 83, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 662: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow64, helper::rle_runs80_len_arr_ow64, 83, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 663: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow64, helper::rle_runs80_len_arr_ow64, 83, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs80_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 664: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow8, helper::rle_runs81_len_arr_ow8, 84, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 665: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow8, helper::rle_runs81_len_arr_ow8, 84, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 666: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow16, helper::rle_runs81_len_arr_ow16, 84, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 667: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow16, helper::rle_runs81_len_arr_ow16, 84, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 668: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow32, helper::rle_runs81_len_arr_ow32, 84, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 669: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow32, helper::rle_runs81_len_arr_ow32, 84, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 670: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow64, helper::rle_runs81_len_arr_ow64, 84, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 671: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow64, helper::rle_runs81_len_arr_ow64, 84, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs81_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 672: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow8, helper::rle_runs82_len_arr_ow8, 85, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 673: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow8, helper::rle_runs82_len_arr_ow8, 85, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 674: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow16, helper::rle_runs82_len_arr_ow16, 85, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 675: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow16, helper::rle_runs82_len_arr_ow16, 85, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 676: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow32, helper::rle_runs82_len_arr_ow32, 85, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 677: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow32, helper::rle_runs82_len_arr_ow32, 85, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 678: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow64, helper::rle_runs82_len_arr_ow64, 85, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 679: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow64, helper::rle_runs82_len_arr_ow64, 85, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs82_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 680: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow8, helper::rle_runs83_len_arr_ow8, 86, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 681: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow8, helper::rle_runs83_len_arr_ow8, 86, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 682: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow16, helper::rle_runs83_len_arr_ow16, 86, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 683: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow16, helper::rle_runs83_len_arr_ow16, 86, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 684: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow32, helper::rle_runs83_len_arr_ow32, 86, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 685: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow32, helper::rle_runs83_len_arr_ow32, 86, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 686: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow64, helper::rle_runs83_len_arr_ow64, 86, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 687: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow64, helper::rle_runs83_len_arr_ow64, 86, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs83_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 688: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow8, helper::rle_runs84_len_arr_ow8, 87, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 689: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow8, helper::rle_runs84_len_arr_ow8, 87, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 690: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow16, helper::rle_runs84_len_arr_ow16, 87, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 691: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow16, helper::rle_runs84_len_arr_ow16, 87, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 692: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow32, helper::rle_runs84_len_arr_ow32, 87, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 693: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow32, helper::rle_runs84_len_arr_ow32, 87, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 694: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow64, helper::rle_runs84_len_arr_ow64, 87, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 695: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow64, helper::rle_runs84_len_arr_ow64, 87, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs84_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 696: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow8, helper::rle_runs85_len_arr_ow8, 88, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 697: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow8, helper::rle_runs85_len_arr_ow8, 88, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 698: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow16, helper::rle_runs85_len_arr_ow16, 88, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 699: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow16, helper::rle_runs85_len_arr_ow16, 88, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 700: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow32, helper::rle_runs85_len_arr_ow32, 88, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 701: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow32, helper::rle_runs85_len_arr_ow32, 88, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 702: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow64, helper::rle_runs85_len_arr_ow64, 88, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 703: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow64, helper::rle_runs85_len_arr_ow64, 88, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs85_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 704: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow8, helper::rle_runs86_len_arr_ow8, 89, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 705: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow8, helper::rle_runs86_len_arr_ow8, 89, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 706: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow16, helper::rle_runs86_len_arr_ow16, 89, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 707: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow16, helper::rle_runs86_len_arr_ow16, 89, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 708: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow32, helper::rle_runs86_len_arr_ow32, 89, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 709: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow32, helper::rle_runs86_len_arr_ow32, 89, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 710: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow64, helper::rle_runs86_len_arr_ow64, 89, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 711: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow64, helper::rle_runs86_len_arr_ow64, 89, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs86_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 712: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow8, helper::rle_runs87_len_arr_ow8, 90, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 713: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow8, helper::rle_runs87_len_arr_ow8, 90, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 714: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow16, helper::rle_runs87_len_arr_ow16, 90, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 715: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow16, helper::rle_runs87_len_arr_ow16, 90, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 716: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow32, helper::rle_runs87_len_arr_ow32, 90, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 717: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow32, helper::rle_runs87_len_arr_ow32, 90, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 718: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow64, helper::rle_runs87_len_arr_ow64, 90, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 719: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow64, helper::rle_runs87_len_arr_ow64, 90, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs87_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 720: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow8, helper::rle_runs88_len_arr_ow8, 91, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 721: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow8, helper::rle_runs88_len_arr_ow8, 91, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 722: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow16, helper::rle_runs88_len_arr_ow16, 91, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 723: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow16, helper::rle_runs88_len_arr_ow16, 91, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 724: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow32, helper::rle_runs88_len_arr_ow32, 91, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 725: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow32, helper::rle_runs88_len_arr_ow32, 91, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 726: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow64, helper::rle_runs88_len_arr_ow64, 91, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 727: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow64, helper::rle_runs88_len_arr_ow64, 91, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs88_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 728: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow8, helper::rle_runs89_len_arr_ow8, 92, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 729: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow8, helper::rle_runs89_len_arr_ow8, 92, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 730: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow16, helper::rle_runs89_len_arr_ow16, 92, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 731: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow16, helper::rle_runs89_len_arr_ow16, 92, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 732: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow32, helper::rle_runs89_len_arr_ow32, 92, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 733: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow32, helper::rle_runs89_len_arr_ow32, 92, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 734: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow64, helper::rle_runs89_len_arr_ow64, 92, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 735: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow64, helper::rle_runs89_len_arr_ow64, 92, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs89_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 736: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow8, helper::rle_runs90_len_arr_ow8, 93, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 737: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow8, helper::rle_runs90_len_arr_ow8, 93, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 738: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow16, helper::rle_runs90_len_arr_ow16, 93, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 739: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow16, helper::rle_runs90_len_arr_ow16, 93, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 740: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow32, helper::rle_runs90_len_arr_ow32, 93, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 741: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow32, helper::rle_runs90_len_arr_ow32, 93, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 742: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow64, helper::rle_runs90_len_arr_ow64, 93, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 743: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow64, helper::rle_runs90_len_arr_ow64, 93, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs90_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 744: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow8, helper::rle_runs91_len_arr_ow8, 94, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 745: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow8, helper::rle_runs91_len_arr_ow8, 94, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 746: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow16, helper::rle_runs91_len_arr_ow16, 94, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 747: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow16, helper::rle_runs91_len_arr_ow16, 94, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 748: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow32, helper::rle_runs91_len_arr_ow32, 94, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 749: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow32, helper::rle_runs91_len_arr_ow32, 94, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 750: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow64, helper::rle_runs91_len_arr_ow64, 94, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 751: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow64, helper::rle_runs91_len_arr_ow64, 94, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs91_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 752: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow8, helper::rle_runs92_len_arr_ow8, 94, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 753: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow8, helper::rle_runs92_len_arr_ow8, 94, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 754: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow16, helper::rle_runs92_len_arr_ow16, 94, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 755: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow16, helper::rle_runs92_len_arr_ow16, 94, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 756: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow32, helper::rle_runs92_len_arr_ow32, 94, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 757: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow32, helper::rle_runs92_len_arr_ow32, 94, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 758: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow64, helper::rle_runs92_len_arr_ow64, 94, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 759: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow64, helper::rle_runs92_len_arr_ow64, 94, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs92_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 760: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow8, helper::rle_runs93_len_arr_ow8, 96, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 761: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow8, helper::rle_runs93_len_arr_ow8, 96, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 762: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow16, helper::rle_runs93_len_arr_ow16, 96, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 763: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow16, helper::rle_runs93_len_arr_ow16, 96, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 764: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow32, helper::rle_runs93_len_arr_ow32, 96, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 765: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow32, helper::rle_runs93_len_arr_ow32, 96, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 766: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow64, helper::rle_runs93_len_arr_ow64, 96, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 767: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow64, helper::rle_runs93_len_arr_ow64, 96, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs93_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 768: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow8, helper::rle_runs94_len_arr_ow8, 97, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 769: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow8, helper::rle_runs94_len_arr_ow8, 97, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 770: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow16, helper::rle_runs94_len_arr_ow16, 97, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 771: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow16, helper::rle_runs94_len_arr_ow16, 97, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 772: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow32, helper::rle_runs94_len_arr_ow32, 97, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 773: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow32, helper::rle_runs94_len_arr_ow32, 97, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 774: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow64, helper::rle_runs94_len_arr_ow64, 97, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 775: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow64, helper::rle_runs94_len_arr_ow64, 97, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs94_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 776: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow8, helper::rle_runs95_len_arr_ow8, 98, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 777: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow8, helper::rle_runs95_len_arr_ow8, 98, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 778: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow16, helper::rle_runs95_len_arr_ow16, 98, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 779: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow16, helper::rle_runs95_len_arr_ow16, 98, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 780: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow32, helper::rle_runs95_len_arr_ow32, 98, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 781: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow32, helper::rle_runs95_len_arr_ow32, 98, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 782: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow64, helper::rle_runs95_len_arr_ow64, 98, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 783: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow64, helper::rle_runs95_len_arr_ow64, 98, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs95_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 784: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow8, helper::rle_runs96_len_arr_ow8, 99, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 785: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow8, helper::rle_runs96_len_arr_ow8, 99, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 786: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow16, helper::rle_runs96_len_arr_ow16, 99, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 787: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow16, helper::rle_runs96_len_arr_ow16, 99, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 788: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow32, helper::rle_runs96_len_arr_ow32, 99, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 789: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow32, helper::rle_runs96_len_arr_ow32, 99, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 790: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow64, helper::rle_runs96_len_arr_ow64, 99, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 791: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow64, helper::rle_runs96_len_arr_ow64, 99, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs96_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 792: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow8, helper::rle_runs97_len_arr_ow8, 99, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 793: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow8, helper::rle_runs97_len_arr_ow8, 99, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 794: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow16, helper::rle_runs97_len_arr_ow16, 99, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 795: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow16, helper::rle_runs97_len_arr_ow16, 99, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 796: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow32, helper::rle_runs97_len_arr_ow32, 99, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 797: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow32, helper::rle_runs97_len_arr_ow32, 99, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 798: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow64, helper::rle_runs97_len_arr_ow64, 99, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 799: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow64, helper::rle_runs97_len_arr_ow64, 99, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs97_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 800: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow8, helper::rle_runs98_len_arr_ow8, 101, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 801: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow8, helper::rle_runs98_len_arr_ow8, 101, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 802: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow16, helper::rle_runs98_len_arr_ow16, 101, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 803: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow16, helper::rle_runs98_len_arr_ow16, 101, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 804: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow32, helper::rle_runs98_len_arr_ow32, 101, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 805: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow32, helper::rle_runs98_len_arr_ow32, 101, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 806: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow64, helper::rle_runs98_len_arr_ow64, 101, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 807: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow64, helper::rle_runs98_len_arr_ow64, 101, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs98_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	

	//==============================================================================================================
	SECTION("test 808: ow = 8 rle")
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow8, helper::rle_runs99_len_arr_ow8, 102, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 809: ow = 8 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow8, helper::rle_runs99_len_arr_ow8, 102, untransposed8);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow8[i] == (untransposed8[i]));
		}
	}
	SECTION("test 810: ow = 16 rle")
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow16, helper::rle_runs99_len_arr_ow16, 102, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 811: ow = 16 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow16, helper::rle_runs99_len_arr_ow16, 102, untransposed16);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow16[i] == (untransposed16[i]));
		}
	}
	SECTION("test 812: ow = 32 rle")
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow32, helper::rle_runs99_len_arr_ow32, 102, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 813: ow = 32 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow32, helper::rle_runs99_len_arr_ow32, 102, untransposed32);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow32[i] == (untransposed32[i]));
		}
	}
	SECTION("test 814: ow = 64 rle")
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow64, helper::rle_runs99_len_arr_ow64, 102, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
	SECTION("test 815: ow = 64 scalar_rle")
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow64, helper::rle_runs99_len_arr_ow64, 102, untransposed64);
		for (int i = 0; i < 1024; ++i)
		{
			CHECK(helper::rle_runs99_untransposed_arr_ow64[i] == (untransposed64[i]));
		}
	}
}
