#include "fls/primitive/fls_memset/fls_memset.hpp"
#include "fls/common/common.hpp"
#include "fls/expression/data_type.hpp"
#include <stdexcept>
#include <type_traits>

namespace fastlanes {
static void unffor_0bw_8ow_8crw_1uf(const uint8_t* __restrict base_p, uint8_t* __restrict a_out_p) {
	[[maybe_unused]] auto    out = reinterpret_cast<uint8_t*>(a_out_p);
	[[maybe_unused]] uint8_t register_0;
	[[maybe_unused]] uint8_t tmp_0;
	[[maybe_unused]] uint8_t base_0 = *(base_p);
	for (int i = 0; i < 128; ++i) {
		*(out + (i * 1) + (0 * 128) + (128 * 0)) = base_0;
		*(out + (i * 1) + (0 * 128) + (128 * 1)) = base_0;
		*(out + (i * 1) + (0 * 128) + (128 * 2)) = base_0;
		*(out + (i * 1) + (0 * 128) + (128 * 3)) = base_0;
		*(out + (i * 1) + (0 * 128) + (128 * 4)) = base_0;
		*(out + (i * 1) + (0 * 128) + (128 * 5)) = base_0;
		*(out + (i * 1) + (0 * 128) + (128 * 6)) = base_0;
		*(out + (i * 1) + (0 * 128) + (128 * 7)) = base_0;
	}
}

static void unffor_0bw_16ow_16crw_1uf(const uint16_t* __restrict base_p, uint16_t* __restrict a_out_p) {
	[[maybe_unused]] auto     out = reinterpret_cast<uint16_t*>(a_out_p);
	[[maybe_unused]] uint16_t register_0;
	[[maybe_unused]] uint16_t tmp_0;
	[[maybe_unused]] uint16_t base_0 = *(base_p);
	for (int i = 0; i < 64; ++i) {
		*(out + (i * 1) + (0 * 64) + (64 * 0))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 1))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 2))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 3))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 4))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 5))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 6))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 7))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 8))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 9))  = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 10)) = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 11)) = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 12)) = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 13)) = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 14)) = base_0;
		*(out + (i * 1) + (0 * 64) + (64 * 15)) = base_0;
	}
}

static void unffor_0bw_32ow_32crw_1uf(const uint32_t* __restrict base_p, uint32_t* __restrict a_out_p) {
	[[maybe_unused]] auto     out = reinterpret_cast<uint32_t*>(a_out_p);
	[[maybe_unused]] uint32_t register_0;
	[[maybe_unused]] uint32_t tmp_0;
	[[maybe_unused]] uint32_t base_0 = *(base_p);
	for (int i = 0; i < 32; ++i) {
		*(out + (i * 1) + (0 * 32) + (32 * 0))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 1))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 2))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 3))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 4))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 5))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 6))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 7))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 8))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 9))  = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 10)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 11)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 12)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 13)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 14)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 15)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 16)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 17)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 18)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 19)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 20)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 21)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 22)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 23)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 24)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 25)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 26)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 27)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 28)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 29)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 30)) = base_0;
		*(out + (i * 1) + (0 * 32) + (32 * 31)) = base_0;
	}
}
static void unffor_0bw_64ow_64crw_1uf(const uint64_t* __restrict base_p, uint64_t* __restrict a_out_p) {
	[[maybe_unused]] auto     out = reinterpret_cast<uint64_t*>(a_out_p);
	[[maybe_unused]] uint64_t register_0;
	[[maybe_unused]] uint64_t tmp_0;
	[[maybe_unused]] uint64_t base_0 = *(base_p);
#pragma clang loop vectorize(enable)
	for (int i = 0; i < 16; ++i) {
		*(out + (i * 1) + (0 * 16) + (16 * 0))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 1))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 2))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 3))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 4))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 5))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 6))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 7))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 8))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 9))  = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 10)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 11)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 12)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 13)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 14)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 15)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 16)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 17)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 18)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 19)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 20)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 21)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 22)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 23)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 24)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 25)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 26)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 27)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 28)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 29)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 30)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 31)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 32)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 33)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 34)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 35)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 36)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 37)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 38)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 39)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 40)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 41)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 42)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 43)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 44)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 45)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 46)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 47)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 48)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 49)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 50)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 51)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 52)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 53)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 54)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 55)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 56)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 57)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 58)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 59)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 60)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 61)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 62)) = base_0;
		*(out + (i * 1) + (0 * 16) + (16 * 63)) = base_0;
	}
}

template <typename PT>
void fls_memset(const PT* __restrict base_p, PT* __restrict out_p) {
	if constexpr (std::is_same_v<PT, dbl_pt> || std::is_same_v<PT, u64_pt> || std::is_same_v<PT, i64_pt>) {
		unffor_0bw_64ow_64crw_1uf(reinterpret_cast<const uint64_t*>(base_p), reinterpret_cast<uint64_t*>(out_p));
	} else if constexpr (std::is_same_v<PT, flt_pt> || std::is_same_v<PT, u32_pt> || std::is_same_v<PT, i32_pt>) {
		unffor_0bw_32ow_32crw_1uf(reinterpret_cast<const u32_pt*>(base_p), reinterpret_cast<u32_pt*>(out_p));
	} else if constexpr (std::is_same_v<PT, u16_pt> || std::is_same_v<PT, i16_pt>) {
		unffor_0bw_16ow_16crw_1uf(reinterpret_cast<const u16_pt*>(base_p), reinterpret_cast<u16_pt*>(out_p));
	} else if constexpr (std::is_same_v<PT, u08_pt> || std::is_same_v<PT, i08_pt>) {
		unffor_0bw_8ow_8crw_1uf(reinterpret_cast<const u08_pt*>(base_p), reinterpret_cast<u08_pt*>(out_p));
	} else {
		FLS_UNREACHABLE()
	}
}

template void fls_memset<dbl_pt>(const dbl_pt* __restrict in_p, dbl_pt* __restrict out_p);
template void fls_memset<u64_pt>(const u64_pt* __restrict in_p, u64_pt* __restrict out_p);
template void fls_memset<i64_pt>(const i64_pt* __restrict in_p, i64_pt* __restrict out_p);
template void fls_memset<flt_pt>(const flt_pt* __restrict in_p, flt_pt* __restrict out_p);
template void fls_memset<u32_pt>(const u32_pt* __restrict in_p, u32_pt* __restrict out_p);
template void fls_memset<i32_pt>(const i32_pt* __restrict in_p, i32_pt* __restrict out_p);
template void fls_memset<u16_pt>(const u16_pt* __restrict in_p, u16_pt* __restrict out_p);
template void fls_memset<i16_pt>(const i16_pt* __restrict in_p, i16_pt* __restrict out_p);
template void fls_memset<u08_pt>(const u08_pt* __restrict in_p, u08_pt* __restrict out_p);
template void fls_memset<i08_pt>(const i08_pt* __restrict in_p, i08_pt* __restrict out_p);
} // namespace fastlanes