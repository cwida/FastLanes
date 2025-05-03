#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/data_type.hpp"
#include <stdexcept>
#include <type_traits>

namespace fastlanes {
static void unpack_8bw_8ow_8crw_1uf(const uint8_t* __restrict a_in_p, uint8_t* __restrict a_out_p) {
	[[maybe_unused]] auto       out = reinterpret_cast<uint8_t*>(a_out_p);
	[[maybe_unused]] const auto in  = reinterpret_cast<const uint8_t*>(a_in_p);
	[[maybe_unused]] uint8_t    register_0;
	[[maybe_unused]] uint8_t    tmp_0;
	[[maybe_unused]] uint8_t    base_0 = 0ULL;
	for (int i = 0; i < 128; ++i) {
		register_0                           = *(in + (0 * 128) + (i * 1) + 0);
		out[(i * 1) + (0 * 128) + (128 * 0)] = register_0;
		register_0                           = *(in + (0 * 128) + (i * 1) + 128);
		out[(i * 1) + (0 * 128) + (128 * 1)] = register_0;
		register_0                           = *(in + (0 * 128) + (i * 1) + 256);
		out[(i * 1) + (0 * 128) + (128 * 2)] = register_0;
		register_0                           = *(in + (0 * 128) + (i * 1) + 384);
		out[(i * 1) + (0 * 128) + (128 * 3)] = register_0;
		register_0                           = *(in + (0 * 128) + (i * 1) + 512);
		out[(i * 1) + (0 * 128) + (128 * 4)] = register_0;
		register_0                           = *(in + (0 * 128) + (i * 1) + 640);
		out[(i * 1) + (0 * 128) + (128 * 5)] = register_0;
		register_0                           = *(in + (0 * 128) + (i * 1) + 768);
		out[(i * 1) + (0 * 128) + (128 * 6)] = register_0;
		register_0                           = *(in + (0 * 128) + (i * 1) + 896);
		out[(i * 1) + (0 * 128) + (128 * 7)] = register_0;
	}
}

static void unpack_16bw_16ow_16crw_1uf(const uint16_t* __restrict a_in_p, uint16_t* __restrict a_out_p) {
	[[maybe_unused]] auto       out = reinterpret_cast<uint16_t*>(a_out_p);
	[[maybe_unused]] const auto in  = reinterpret_cast<const uint16_t*>(a_in_p);
	[[maybe_unused]] uint16_t   register_0;
	[[maybe_unused]] uint16_t   tmp_0;
	[[maybe_unused]] uint16_t   base_0 = 0ULL;
	for (int i = 0; i < 64; ++i) {
		register_0                          = *(in + (0 * 64) + (i * 1) + 0);
		out[(i * 1) + (0 * 64) + (64 * 0)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 64);
		out[(i * 1) + (0 * 64) + (64 * 1)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 128);
		out[(i * 1) + (0 * 64) + (64 * 2)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 192);
		out[(i * 1) + (0 * 64) + (64 * 3)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 256);
		out[(i * 1) + (0 * 64) + (64 * 4)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 320);
		out[(i * 1) + (0 * 64) + (64 * 5)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 384);
		out[(i * 1) + (0 * 64) + (64 * 6)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 448);
		out[(i * 1) + (0 * 64) + (64 * 7)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 512);
		out[(i * 1) + (0 * 64) + (64 * 8)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 576);
		out[(i * 1) + (0 * 64) + (64 * 9)]  = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 640);
		out[(i * 1) + (0 * 64) + (64 * 10)] = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 704);
		out[(i * 1) + (0 * 64) + (64 * 11)] = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 768);
		out[(i * 1) + (0 * 64) + (64 * 12)] = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 832);
		out[(i * 1) + (0 * 64) + (64 * 13)] = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 896);
		out[(i * 1) + (0 * 64) + (64 * 14)] = register_0;
		register_0                          = *(in + (0 * 64) + (i * 1) + 960);
		out[(i * 1) + (0 * 64) + (64 * 15)] = register_0;
	}
}

static void unpack_32bw_32ow_32crw_1uf(const uint32_t* __restrict a_in_p, uint32_t* __restrict a_out_p) {
	[[maybe_unused]] auto       out = reinterpret_cast<uint32_t*>(a_out_p);
	[[maybe_unused]] const auto in  = reinterpret_cast<const uint32_t*>(a_in_p);
	[[maybe_unused]] uint32_t   register_0;
	[[maybe_unused]] uint32_t   tmp_0;
	[[maybe_unused]] uint32_t   base_0 = 0ULL;
	for (int i = 0; i < 32; ++i) {
		register_0                          = *(in + (0 * 32) + (i * 1) + 0);
		out[(i * 1) + (0 * 32) + (32 * 0)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 32);
		out[(i * 1) + (0 * 32) + (32 * 1)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 64);
		out[(i * 1) + (0 * 32) + (32 * 2)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 96);
		out[(i * 1) + (0 * 32) + (32 * 3)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 128);
		out[(i * 1) + (0 * 32) + (32 * 4)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 160);
		out[(i * 1) + (0 * 32) + (32 * 5)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 192);
		out[(i * 1) + (0 * 32) + (32 * 6)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 224);
		out[(i * 1) + (0 * 32) + (32 * 7)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 256);
		out[(i * 1) + (0 * 32) + (32 * 8)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 288);
		out[(i * 1) + (0 * 32) + (32 * 9)]  = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 320);
		out[(i * 1) + (0 * 32) + (32 * 10)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 352);
		out[(i * 1) + (0 * 32) + (32 * 11)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 384);
		out[(i * 1) + (0 * 32) + (32 * 12)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 416);
		out[(i * 1) + (0 * 32) + (32 * 13)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 448);
		out[(i * 1) + (0 * 32) + (32 * 14)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 480);
		out[(i * 1) + (0 * 32) + (32 * 15)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 512);
		out[(i * 1) + (0 * 32) + (32 * 16)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 544);
		out[(i * 1) + (0 * 32) + (32 * 17)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 576);
		out[(i * 1) + (0 * 32) + (32 * 18)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 608);
		out[(i * 1) + (0 * 32) + (32 * 19)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 640);
		out[(i * 1) + (0 * 32) + (32 * 20)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 672);
		out[(i * 1) + (0 * 32) + (32 * 21)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 704);
		out[(i * 1) + (0 * 32) + (32 * 22)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 736);
		out[(i * 1) + (0 * 32) + (32 * 23)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 768);
		out[(i * 1) + (0 * 32) + (32 * 24)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 800);
		out[(i * 1) + (0 * 32) + (32 * 25)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 832);
		out[(i * 1) + (0 * 32) + (32 * 26)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 864);
		out[(i * 1) + (0 * 32) + (32 * 27)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 896);
		out[(i * 1) + (0 * 32) + (32 * 28)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 928);
		out[(i * 1) + (0 * 32) + (32 * 29)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 960);
		out[(i * 1) + (0 * 32) + (32 * 30)] = register_0;
		register_0                          = *(in + (0 * 32) + (i * 1) + 992);
		out[(i * 1) + (0 * 32) + (32 * 31)] = register_0;
	}
}

static void unpack_64bw_64ow_64crw_1uf(const uint64_t* __restrict in, uint64_t* __restrict out) {
	[[maybe_unused]] uint64_t register_0;
	[[maybe_unused]] uint64_t tmp_0;
#pragma clang loop vectorize(enable)
	for (int i = 0; i < 16; ++i) {
		register_0                          = *(in + (0 * 16) + (i * 1) + 0);
		out[(i * 1) + (0 * 16) + (16 * 0)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 16);
		out[(i * 1) + (0 * 16) + (16 * 1)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 32);
		out[(i * 1) + (0 * 16) + (16 * 2)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 48);
		out[(i * 1) + (0 * 16) + (16 * 3)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 64);
		out[(i * 1) + (0 * 16) + (16 * 4)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 80);
		out[(i * 1) + (0 * 16) + (16 * 5)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 96);
		out[(i * 1) + (0 * 16) + (16 * 6)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 112);
		out[(i * 1) + (0 * 16) + (16 * 7)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 128);
		out[(i * 1) + (0 * 16) + (16 * 8)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 144);
		out[(i * 1) + (0 * 16) + (16 * 9)]  = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 160);
		out[(i * 1) + (0 * 16) + (16 * 10)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 176);
		out[(i * 1) + (0 * 16) + (16 * 11)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 192);
		out[(i * 1) + (0 * 16) + (16 * 12)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 208);
		out[(i * 1) + (0 * 16) + (16 * 13)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 224);
		out[(i * 1) + (0 * 16) + (16 * 14)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 240);
		out[(i * 1) + (0 * 16) + (16 * 15)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 256);
		out[(i * 1) + (0 * 16) + (16 * 16)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 272);
		out[(i * 1) + (0 * 16) + (16 * 17)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 288);
		out[(i * 1) + (0 * 16) + (16 * 18)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 304);
		out[(i * 1) + (0 * 16) + (16 * 19)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 320);
		out[(i * 1) + (0 * 16) + (16 * 20)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 336);
		out[(i * 1) + (0 * 16) + (16 * 21)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 352);
		out[(i * 1) + (0 * 16) + (16 * 22)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 368);
		out[(i * 1) + (0 * 16) + (16 * 23)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 384);
		out[(i * 1) + (0 * 16) + (16 * 24)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 400);
		out[(i * 1) + (0 * 16) + (16 * 25)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 416);
		out[(i * 1) + (0 * 16) + (16 * 26)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 432);
		out[(i * 1) + (0 * 16) + (16 * 27)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 448);
		out[(i * 1) + (0 * 16) + (16 * 28)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 464);
		out[(i * 1) + (0 * 16) + (16 * 29)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 480);
		out[(i * 1) + (0 * 16) + (16 * 30)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 496);
		out[(i * 1) + (0 * 16) + (16 * 31)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 512);
		out[(i * 1) + (0 * 16) + (16 * 32)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 528);
		out[(i * 1) + (0 * 16) + (16 * 33)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 544);
		out[(i * 1) + (0 * 16) + (16 * 34)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 560);
		out[(i * 1) + (0 * 16) + (16 * 35)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 576);
		out[(i * 1) + (0 * 16) + (16 * 36)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 592);
		out[(i * 1) + (0 * 16) + (16 * 37)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 608);
		out[(i * 1) + (0 * 16) + (16 * 38)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 624);
		out[(i * 1) + (0 * 16) + (16 * 39)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 640);
		out[(i * 1) + (0 * 16) + (16 * 40)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 656);
		out[(i * 1) + (0 * 16) + (16 * 41)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 672);
		out[(i * 1) + (0 * 16) + (16 * 42)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 688);
		out[(i * 1) + (0 * 16) + (16 * 43)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 704);
		out[(i * 1) + (0 * 16) + (16 * 44)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 720);
		out[(i * 1) + (0 * 16) + (16 * 45)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 736);
		out[(i * 1) + (0 * 16) + (16 * 46)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 752);
		out[(i * 1) + (0 * 16) + (16 * 47)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 768);
		out[(i * 1) + (0 * 16) + (16 * 48)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 784);
		out[(i * 1) + (0 * 16) + (16 * 49)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 800);
		out[(i * 1) + (0 * 16) + (16 * 50)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 816);
		out[(i * 1) + (0 * 16) + (16 * 51)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 832);
		out[(i * 1) + (0 * 16) + (16 * 52)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 848);
		out[(i * 1) + (0 * 16) + (16 * 53)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 864);
		out[(i * 1) + (0 * 16) + (16 * 54)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 880);
		out[(i * 1) + (0 * 16) + (16 * 55)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 896);
		out[(i * 1) + (0 * 16) + (16 * 56)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 912);
		out[(i * 1) + (0 * 16) + (16 * 57)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 928);
		out[(i * 1) + (0 * 16) + (16 * 58)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 944);
		out[(i * 1) + (0 * 16) + (16 * 59)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 960);
		out[(i * 1) + (0 * 16) + (16 * 60)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 976);
		out[(i * 1) + (0 * 16) + (16 * 61)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 992);
		out[(i * 1) + (0 * 16) + (16 * 62)] = register_0;
		register_0                          = *(in + (0 * 16) + (i * 1) + 1008);
		out[(i * 1) + (0 * 16) + (16 * 63)] = register_0;
	}
}

template <typename PT>
void copy(const PT* __restrict in_p, PT* __restrict out_p) {
	if constexpr (std::is_same_v<PT, dbl_pt> || std::is_same_v<PT, u64_pt> || std::is_same_v<PT, i64_pt>) {
		unpack_64bw_64ow_64crw_1uf(reinterpret_cast<const uint64_t*>(in_p), reinterpret_cast<uint64_t*>(out_p));
	} else if constexpr (std::is_same_v<PT, flt_pt> || std::is_same_v<PT, u32_pt> || std::is_same_v<PT, i32_pt>) {
		unpack_32bw_32ow_32crw_1uf(reinterpret_cast<const u32_pt*>(in_p), reinterpret_cast<u32_pt*>(out_p));
	} else if constexpr (std::is_same_v<PT, u16_pt> || std::is_same_v<PT, i16_pt>) {
		unpack_16bw_16ow_16crw_1uf(reinterpret_cast<const u16_pt*>(in_p), reinterpret_cast<u16_pt*>(out_p));
	} else if constexpr (std::is_same_v<PT, u08_pt> || std::is_same_v<PT, i08_pt>) {
		unpack_8bw_8ow_8crw_1uf(reinterpret_cast<const u08_pt*>(in_p), reinterpret_cast<u08_pt*>(out_p));
	} else {
		FLS_UNREACHABLE()
	}
}

template void copy<dbl_pt>(const dbl_pt* __restrict in_p, dbl_pt* __restrict out_p);
template void copy<u64_pt>(const u64_pt* __restrict in_p, u64_pt* __restrict out_p);
template void copy<i64_pt>(const i64_pt* __restrict in_p, i64_pt* __restrict out_p);
template void copy<flt_pt>(const flt_pt* __restrict in_p, flt_pt* __restrict out_p);
template void copy<u32_pt>(const u32_pt* __restrict in_p, u32_pt* __restrict out_p);
template void copy<i32_pt>(const i32_pt* __restrict in_p, i32_pt* __restrict out_p);
template void copy<u16_pt>(const u16_pt* __restrict in_p, u16_pt* __restrict out_p);
template void copy<i16_pt>(const i16_pt* __restrict in_p, i16_pt* __restrict out_p);
template void copy<u08_pt>(const u08_pt* __restrict in_p, u08_pt* __restrict out_p);
template void copy<i08_pt>(const i08_pt* __restrict in_p, i08_pt* __restrict out_p);
} // namespace fastlanes