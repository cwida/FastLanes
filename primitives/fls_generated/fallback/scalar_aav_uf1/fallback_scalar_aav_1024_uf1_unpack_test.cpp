// generated!
// NOLINTBEGIN
#include "fallback_scalar_aav_1024_uf1_unpack_helper.hpp"
#include "fls_gen/pack/pack.hpp"
#include "fls_gen/unpack/unpack.hpp"
#include "gtest/gtest.h"
class fallback_scalar_aav_1024_uf1_unpack : public ::testing::Test {
public:
	uint8_t*  packed8;
	uint16_t* packed16;
	uint32_t* packed32;
	uint64_t* packed64;
	uint8_t*  unpacked8;
	uint16_t* unpacked16;
	uint32_t* unpacked32;
	uint64_t* unpacked64;
	uint8_t*  base8;
	uint16_t* base16;
	uint32_t* base32;
	uint64_t* base64;
	void      SetUp() override {
        packed8    = new uint8_t[1024]();
        packed16   = new uint16_t[1024]();
        packed32   = new uint32_t[1024]();
        packed64   = new uint64_t[1024]();
        unpacked8  = new uint8_t[1024]();
        unpacked16 = new uint16_t[1024]();
        unpacked32 = new uint32_t[1024]();
        unpacked64 = new uint64_t[1024]();
        base8      = new uint8_t[1]();
        base16     = new uint16_t[1]();
        base32     = new uint32_t[1]();
        base64     = new uint64_t[1]();
	}
	~fallback_scalar_aav_1024_uf1_unpack() override {
		delete[] packed8;
		delete[] packed16;
		delete[] packed32;
		delete[] packed64;
		delete[] unpacked8;
		delete[] unpacked16;
		delete[] unpacked32;
		delete[] unpacked64;
	}
};
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_0_bw_0_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_0_b0_w8_arr, const_cast<uint8_t*>(packed8), 0);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 0);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_0_b0_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_1_bw_1_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_1_b1_w8_arr, const_cast<uint8_t*>(packed8), 1);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 1);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_1_b1_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_2_bw_2_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_2_b2_w8_arr, const_cast<uint8_t*>(packed8), 2);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 2);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_2_b2_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_3_bw_3_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_3_b3_w8_arr, const_cast<uint8_t*>(packed8), 3);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 3);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_3_b3_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_4_bw_4_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_4_b4_w8_arr, const_cast<uint8_t*>(packed8), 4);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 4);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_4_b4_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_5_bw_5_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_5_b5_w8_arr, const_cast<uint8_t*>(packed8), 5);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 5);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_5_b5_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_6_bw_6_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_6_b6_w8_arr, const_cast<uint8_t*>(packed8), 6);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 6);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_6_b6_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_7_bw_7_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_7_b7_w8_arr, const_cast<uint8_t*>(packed8), 7);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 7);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_7_b7_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_8_bw_8_ow_8) {
	*(base8) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_8_b8_w8_arr, const_cast<uint8_t*>(packed8), 8);
	generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 8);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_8_b8_w8_arr[k], unpacked8[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_9_bw_0_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_9_b0_w16_arr, const_cast<uint16_t*>(packed16), 0);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 0);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_9_b0_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_10_bw_1_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_10_b1_w16_arr, const_cast<uint16_t*>(packed16), 1);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 1);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_10_b1_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_11_bw_2_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_11_b2_w16_arr, const_cast<uint16_t*>(packed16), 2);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 2);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_11_b2_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_12_bw_3_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_12_b3_w16_arr, const_cast<uint16_t*>(packed16), 3);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 3);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_12_b3_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_13_bw_4_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_13_b4_w16_arr, const_cast<uint16_t*>(packed16), 4);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 4);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_13_b4_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_14_bw_5_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_14_b5_w16_arr, const_cast<uint16_t*>(packed16), 5);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 5);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_14_b5_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_15_bw_6_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_15_b6_w16_arr, const_cast<uint16_t*>(packed16), 6);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 6);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_15_b6_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_16_bw_7_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_16_b7_w16_arr, const_cast<uint16_t*>(packed16), 7);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 7);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_16_b7_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_17_bw_8_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_17_b8_w16_arr, const_cast<uint16_t*>(packed16), 8);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 8);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_17_b8_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_18_bw_9_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_18_b9_w16_arr, const_cast<uint16_t*>(packed16), 9);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 9);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_18_b9_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_19_bw_10_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_19_b10_w16_arr, const_cast<uint16_t*>(packed16), 10);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 10);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_19_b10_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_20_bw_11_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_20_b11_w16_arr, const_cast<uint16_t*>(packed16), 11);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 11);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_20_b11_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_21_bw_12_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_21_b12_w16_arr, const_cast<uint16_t*>(packed16), 12);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 12);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_21_b12_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_22_bw_13_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_22_b13_w16_arr, const_cast<uint16_t*>(packed16), 13);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 13);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_22_b13_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_23_bw_14_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_23_b14_w16_arr, const_cast<uint16_t*>(packed16), 14);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 14);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_23_b14_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_24_bw_15_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_24_b15_w16_arr, const_cast<uint16_t*>(packed16), 15);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 15);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_24_b15_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_25_bw_16_ow_16) {
	*(base16) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_25_b16_w16_arr, const_cast<uint16_t*>(packed16), 16);
	generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 16);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_25_b16_w16_arr[k], unpacked16[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_26_bw_0_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_26_b0_w32_arr, const_cast<uint32_t*>(packed32), 0);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 0);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_26_b0_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_27_bw_1_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_27_b1_w32_arr, const_cast<uint32_t*>(packed32), 1);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 1);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_27_b1_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_28_bw_2_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_28_b2_w32_arr, const_cast<uint32_t*>(packed32), 2);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 2);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_28_b2_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_29_bw_3_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_29_b3_w32_arr, const_cast<uint32_t*>(packed32), 3);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 3);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_29_b3_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_30_bw_4_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_30_b4_w32_arr, const_cast<uint32_t*>(packed32), 4);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 4);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_30_b4_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_31_bw_5_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_31_b5_w32_arr, const_cast<uint32_t*>(packed32), 5);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 5);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_31_b5_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_32_bw_6_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_32_b6_w32_arr, const_cast<uint32_t*>(packed32), 6);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 6);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_32_b6_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_33_bw_7_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_33_b7_w32_arr, const_cast<uint32_t*>(packed32), 7);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 7);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_33_b7_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_34_bw_8_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_34_b8_w32_arr, const_cast<uint32_t*>(packed32), 8);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 8);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_34_b8_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_35_bw_9_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_35_b9_w32_arr, const_cast<uint32_t*>(packed32), 9);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 9);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_35_b9_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_36_bw_10_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_36_b10_w32_arr, const_cast<uint32_t*>(packed32), 10);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 10);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_36_b10_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_37_bw_11_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_37_b11_w32_arr, const_cast<uint32_t*>(packed32), 11);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 11);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_37_b11_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_38_bw_12_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_38_b12_w32_arr, const_cast<uint32_t*>(packed32), 12);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 12);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_38_b12_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_39_bw_13_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_39_b13_w32_arr, const_cast<uint32_t*>(packed32), 13);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 13);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_39_b13_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_40_bw_14_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_40_b14_w32_arr, const_cast<uint32_t*>(packed32), 14);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 14);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_40_b14_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_41_bw_15_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_41_b15_w32_arr, const_cast<uint32_t*>(packed32), 15);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 15);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_41_b15_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_42_bw_16_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_42_b16_w32_arr, const_cast<uint32_t*>(packed32), 16);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 16);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_42_b16_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_43_bw_17_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_43_b17_w32_arr, const_cast<uint32_t*>(packed32), 17);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 17);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_43_b17_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_44_bw_18_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_44_b18_w32_arr, const_cast<uint32_t*>(packed32), 18);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 18);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_44_b18_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_45_bw_19_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_45_b19_w32_arr, const_cast<uint32_t*>(packed32), 19);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 19);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_45_b19_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_46_bw_20_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_46_b20_w32_arr, const_cast<uint32_t*>(packed32), 20);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 20);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_46_b20_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_47_bw_21_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_47_b21_w32_arr, const_cast<uint32_t*>(packed32), 21);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 21);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_47_b21_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_48_bw_22_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_48_b22_w32_arr, const_cast<uint32_t*>(packed32), 22);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 22);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_48_b22_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_49_bw_23_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_49_b23_w32_arr, const_cast<uint32_t*>(packed32), 23);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 23);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_49_b23_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_50_bw_24_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_50_b24_w32_arr, const_cast<uint32_t*>(packed32), 24);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 24);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_50_b24_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_51_bw_25_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_51_b25_w32_arr, const_cast<uint32_t*>(packed32), 25);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 25);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_51_b25_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_52_bw_26_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_52_b26_w32_arr, const_cast<uint32_t*>(packed32), 26);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 26);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_52_b26_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_53_bw_27_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_53_b27_w32_arr, const_cast<uint32_t*>(packed32), 27);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 27);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_53_b27_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_54_bw_28_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_54_b28_w32_arr, const_cast<uint32_t*>(packed32), 28);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 28);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_54_b28_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_55_bw_29_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_55_b29_w32_arr, const_cast<uint32_t*>(packed32), 29);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 29);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_55_b29_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_56_bw_30_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_56_b30_w32_arr, const_cast<uint32_t*>(packed32), 30);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 30);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_56_b30_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_57_bw_31_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_57_b31_w32_arr, const_cast<uint32_t*>(packed32), 31);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 31);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_57_b31_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_58_bw_32_ow_32) {
	*(base32) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_58_b32_w32_arr, const_cast<uint32_t*>(packed32), 32);
	generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 32);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_58_b32_w32_arr[k], unpacked32[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_59_bw_0_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_59_b0_w64_arr, const_cast<uint64_t*>(packed64), 0);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 0);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_59_b0_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_60_bw_1_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_60_b1_w64_arr, const_cast<uint64_t*>(packed64), 1);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 1);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_60_b1_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_61_bw_2_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_61_b2_w64_arr, const_cast<uint64_t*>(packed64), 2);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 2);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_61_b2_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_62_bw_3_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_62_b3_w64_arr, const_cast<uint64_t*>(packed64), 3);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 3);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_62_b3_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_63_bw_4_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_63_b4_w64_arr, const_cast<uint64_t*>(packed64), 4);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 4);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_63_b4_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_64_bw_5_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_64_b5_w64_arr, const_cast<uint64_t*>(packed64), 5);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 5);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_64_b5_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_65_bw_6_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_65_b6_w64_arr, const_cast<uint64_t*>(packed64), 6);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 6);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_65_b6_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_66_bw_7_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_66_b7_w64_arr, const_cast<uint64_t*>(packed64), 7);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 7);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_66_b7_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_67_bw_8_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_67_b8_w64_arr, const_cast<uint64_t*>(packed64), 8);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 8);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_67_b8_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_68_bw_9_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_68_b9_w64_arr, const_cast<uint64_t*>(packed64), 9);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 9);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_68_b9_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_69_bw_10_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_69_b10_w64_arr, const_cast<uint64_t*>(packed64), 10);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 10);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_69_b10_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_70_bw_11_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_70_b11_w64_arr, const_cast<uint64_t*>(packed64), 11);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 11);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_70_b11_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_71_bw_12_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_71_b12_w64_arr, const_cast<uint64_t*>(packed64), 12);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 12);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_71_b12_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_72_bw_13_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_72_b13_w64_arr, const_cast<uint64_t*>(packed64), 13);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 13);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_72_b13_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_73_bw_14_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_73_b14_w64_arr, const_cast<uint64_t*>(packed64), 14);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 14);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_73_b14_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_74_bw_15_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_74_b15_w64_arr, const_cast<uint64_t*>(packed64), 15);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 15);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_74_b15_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_75_bw_16_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_75_b16_w64_arr, const_cast<uint64_t*>(packed64), 16);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 16);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_75_b16_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_76_bw_17_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_76_b17_w64_arr, const_cast<uint64_t*>(packed64), 17);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 17);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_76_b17_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_77_bw_18_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_77_b18_w64_arr, const_cast<uint64_t*>(packed64), 18);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 18);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_77_b18_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_78_bw_19_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_78_b19_w64_arr, const_cast<uint64_t*>(packed64), 19);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 19);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_78_b19_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_79_bw_20_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_79_b20_w64_arr, const_cast<uint64_t*>(packed64), 20);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 20);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_79_b20_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_80_bw_21_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_80_b21_w64_arr, const_cast<uint64_t*>(packed64), 21);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 21);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_80_b21_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_81_bw_22_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_81_b22_w64_arr, const_cast<uint64_t*>(packed64), 22);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 22);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_81_b22_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_82_bw_23_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_82_b23_w64_arr, const_cast<uint64_t*>(packed64), 23);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 23);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_82_b23_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_83_bw_24_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_83_b24_w64_arr, const_cast<uint64_t*>(packed64), 24);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 24);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_83_b24_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_84_bw_25_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_84_b25_w64_arr, const_cast<uint64_t*>(packed64), 25);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 25);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_84_b25_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_85_bw_26_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_85_b26_w64_arr, const_cast<uint64_t*>(packed64), 26);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 26);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_85_b26_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_86_bw_27_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_86_b27_w64_arr, const_cast<uint64_t*>(packed64), 27);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 27);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_86_b27_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_87_bw_28_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_87_b28_w64_arr, const_cast<uint64_t*>(packed64), 28);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 28);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_87_b28_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_88_bw_29_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_88_b29_w64_arr, const_cast<uint64_t*>(packed64), 29);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 29);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_88_b29_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_89_bw_30_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_89_b30_w64_arr, const_cast<uint64_t*>(packed64), 30);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 30);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_89_b30_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_90_bw_31_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_90_b31_w64_arr, const_cast<uint64_t*>(packed64), 31);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 31);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_90_b31_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_91_bw_32_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_91_b32_w64_arr, const_cast<uint64_t*>(packed64), 32);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 32);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_91_b32_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_92_bw_33_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_92_b33_w64_arr, const_cast<uint64_t*>(packed64), 33);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 33);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_92_b33_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_93_bw_34_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_93_b34_w64_arr, const_cast<uint64_t*>(packed64), 34);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 34);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_93_b34_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_94_bw_35_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_94_b35_w64_arr, const_cast<uint64_t*>(packed64), 35);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 35);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_94_b35_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_95_bw_36_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_95_b36_w64_arr, const_cast<uint64_t*>(packed64), 36);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 36);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_95_b36_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_96_bw_37_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_96_b37_w64_arr, const_cast<uint64_t*>(packed64), 37);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 37);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_96_b37_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_97_bw_38_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_97_b38_w64_arr, const_cast<uint64_t*>(packed64), 38);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 38);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_97_b38_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_98_bw_39_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_98_b39_w64_arr, const_cast<uint64_t*>(packed64), 39);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 39);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_98_b39_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_99_bw_40_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_99_b40_w64_arr, const_cast<uint64_t*>(packed64), 40);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 40);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_99_b40_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_100_bw_41_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_100_b41_w64_arr, const_cast<uint64_t*>(packed64), 41);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 41);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_100_b41_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_101_bw_42_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_101_b42_w64_arr, const_cast<uint64_t*>(packed64), 42);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 42);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_101_b42_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_102_bw_43_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_102_b43_w64_arr, const_cast<uint64_t*>(packed64), 43);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 43);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_102_b43_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_103_bw_44_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_103_b44_w64_arr, const_cast<uint64_t*>(packed64), 44);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 44);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_103_b44_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_104_bw_45_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_104_b45_w64_arr, const_cast<uint64_t*>(packed64), 45);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 45);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_104_b45_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_105_bw_46_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_105_b46_w64_arr, const_cast<uint64_t*>(packed64), 46);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 46);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_105_b46_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_106_bw_47_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_106_b47_w64_arr, const_cast<uint64_t*>(packed64), 47);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 47);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_106_b47_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_107_bw_48_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_107_b48_w64_arr, const_cast<uint64_t*>(packed64), 48);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 48);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_107_b48_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_108_bw_49_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_108_b49_w64_arr, const_cast<uint64_t*>(packed64), 49);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 49);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_108_b49_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_109_bw_50_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_109_b50_w64_arr, const_cast<uint64_t*>(packed64), 50);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 50);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_109_b50_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_110_bw_51_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_110_b51_w64_arr, const_cast<uint64_t*>(packed64), 51);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 51);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_110_b51_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_111_bw_52_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_111_b52_w64_arr, const_cast<uint64_t*>(packed64), 52);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 52);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_111_b52_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_112_bw_53_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_112_b53_w64_arr, const_cast<uint64_t*>(packed64), 53);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 53);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_112_b53_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_113_bw_54_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_113_b54_w64_arr, const_cast<uint64_t*>(packed64), 54);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 54);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_113_b54_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_114_bw_55_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_114_b55_w64_arr, const_cast<uint64_t*>(packed64), 55);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 55);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_114_b55_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_115_bw_56_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_115_b56_w64_arr, const_cast<uint64_t*>(packed64), 56);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 56);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_115_b56_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_116_bw_57_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_116_b57_w64_arr, const_cast<uint64_t*>(packed64), 57);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 57);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_116_b57_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_117_bw_58_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_117_b58_w64_arr, const_cast<uint64_t*>(packed64), 58);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 58);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_117_b58_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_118_bw_59_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_118_b59_w64_arr, const_cast<uint64_t*>(packed64), 59);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 59);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_118_b59_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_119_bw_60_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_119_b60_w64_arr, const_cast<uint64_t*>(packed64), 60);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 60);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_119_b60_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_120_bw_61_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_120_b61_w64_arr, const_cast<uint64_t*>(packed64), 61);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 61);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_120_b61_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_121_bw_62_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_121_b62_w64_arr, const_cast<uint64_t*>(packed64), 62);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 62);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_121_b62_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_122_bw_63_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_122_b63_w64_arr, const_cast<uint64_t*>(packed64), 63);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 63);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_122_b63_w64_arr[k], unpacked64[k]);
	}
}
TEST_F(fallback_scalar_aav_1024_uf1_unpack, test_123_bw_64_ow_64) {
	*(base64) = 0;
	generated::pack::fallback::scalar::pack(helper::rand_arr_123_b64_w64_arr, const_cast<uint64_t*>(packed64), 64);
	generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 64);
	for (int k = 0; k < 1024; ++k) {
		ASSERT_EQ(helper::rand_arr_123_b64_w64_arr[k], unpacked64[k]);
	}
}
