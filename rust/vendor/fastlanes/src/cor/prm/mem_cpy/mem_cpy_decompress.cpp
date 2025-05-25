#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/mem_cpy_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include <cstring>

namespace fastlanes {
template <typename T>
static void mem_cpy_decmpr(PageParam src, VecParam des, DecompressState& stt) {
	auto* in_arr  = reinterpret_cast<const T*>(src.arr[stt.cur_src_arr - 0]);
	auto* out_arr = reinterpret_cast<T*>(des.arr[stt.cur_des_arr - 0]);

	std::memcpy(out_arr, in_arr, vec_bsz<T>());

	FLS_PLOG_KEY_VALUE("cur_vec", ToStr::to_str<T>(out_arr));

	stt.cur_des_arr -= 1;
	stt.cur_src_arr -= 1;
}

static void off_mem_cpy_decmpr(PageParam src, VecParam des, DecompressState& stt) {
	auto* in_arr  = src.arr[stt.cur_src_arr - 0];
	auto* out_arr = des.arr[stt.cur_des_arr - 0];

	/* in smart offset array the last tuple show the number of bytes. */
	uint32_t byte_c = reinterpret_cast<uint32_t*>(des.arr[stt.cur_des_arr + 1])[1023];
	// FLS_ASSERT_LE(byte_c, CFG::BUF::SZ) // todo[buf]
	std::memcpy(out_arr, in_arr, byte_c);

	FLS_PLOG_KEY_VALUE("cur_vec", ToStr::to_str<uint8_t>(out_arr));

	stt.cur_des_arr -= 1;
	stt.cur_src_arr -= 1;
}

template <typename T>
de_cmpr_fun_t mem_cpy::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return mem_cpy_decmpr<uint64_t>;
	} else if constexpr (std::is_same_v<T, uint64_t>) {
		return mem_cpy_decmpr<uint64_t>;
	} else if constexpr (std::is_same_v<T, int32_t>) {
		return mem_cpy_decmpr<uint32_t>;
	} else if constexpr (std::is_same_v<T, uint32_t>) {
		return mem_cpy_decmpr<uint32_t>;
	} else if constexpr (std::is_same_v<T, uint16_t>) {
		return mem_cpy_decmpr<uint16_t>;
	} else if constexpr (std::is_same_v<T, uint8_t>) {
		return mem_cpy_decmpr<uint8_t>;
	} else if constexpr (std::is_same_v<T, str_pt>) {
		return off_mem_cpy_decmpr;
	} else if constexpr (std::is_same_v<T, dbl_pt>) {
		return mem_cpy_decmpr<dbl_pt>;
	}

	FLS_ABORT("IT IS NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, mem_cpy::ResolveDecompressFunc)
} // namespace fastlanes