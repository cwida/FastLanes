#include <arm_neon.h>
#include "bitpack/bitpack.h"
#include "arm64v8_neon_iu8lp_1024_uf1_bit_unpack_helper.hpp"
#include "iostream"

static void unpack_1bw_16ow_128crw_1uf(uint16_t *__restrict _in, uint16_t *__restrict _out)
{
    auto out = (_out);
    auto in = (_in);
    uint16x8_t register_0;
    uint16x8_t tmp_0;
    // use 8-bit vlanes
    for (int i = 0; i < 8; ++i)
    {
        register_0 = vld1q_u16(in + (0 * 8 * 8) + (i * 8) + 0);
        tmp_0 = vandq_u8(register_0, vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64 * 0 * 2) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64 * 0 * 2) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
        tmp_0 = vandq_u16(vshrq_n_u8(register_0, 1), vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64 * 1 * 2) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64 * 1 * 2) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
        tmp_0 = vandq_u16(vshrq_n_u8(register_0, 2), vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 2) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 2) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
        tmp_0 = vandq_u16(vshrq_n_u8(register_0, 3), vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 3) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 3) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
        tmp_0 = vandq_u16(vshrq_n_u8(register_0, 4), vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 4) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 4) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
        tmp_0 = vandq_u16(vshrq_n_u8(register_0, 5), vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 5) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 5) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
        tmp_0 = vandq_u16(vshrq_n_u8(register_0, 6), vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 6) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 6) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
        tmp_0 = vandq_u16(vshrq_n_u8(register_0, 7), vdupq_n_u8((1ULL << 1) - 1));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 7) + (0 * 8), vmovl_u8(vget_low_u8(tmp_0)));
        vst1q_u16(out + (i * 8 * 2) + (0 * 8 * 8) + (64* 2 * 7) + (1 * 8), vmovl_u8(vget_high_u8(tmp_0)));
    }
}

int main(){
    auto packed8 = new uint8_t[1024]();
    auto packed16 = new uint16_t[1024]();
    auto packed32 = new uint32_t[1024]();
    auto packed64 = new uint64_t[1024]();
    auto unpacked8 = new uint8_t[1024]();
    auto unpacked16 = new uint16_t[1024]();
    auto unpacked32 = new uint32_t[1024]();
    auto unpacked64 = new uint64_t[1024]();


    for (int k = 0; k < 1024; ++k)
    {
        helper::rand_arr_9_b1_w16_arr[k] = 1;
        std::cout << ((k % 64 == 0)? "\n": " ") << int(helper::rand_arr_9_b1_w16_arr[k]) << " ";
    }

    bitpack::pack(helper::rand_arr_9_b1_w16_arr, packed8, 1);
    std::cout << "\n";

    unpack_1bw_16ow_128crw_1uf(reinterpret_cast<uint16_t *>(packed8), unpacked16);
    for (int k = 0; k < 1024; ++k)
    {
        std::cout << ((k % 64 == 0)? "\n": " ") << unpacked16[k] << " ";
    }
}

