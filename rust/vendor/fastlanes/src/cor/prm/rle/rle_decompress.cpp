#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/rle_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"
#include <cstring>

namespace fastlanes {
template <typename T>
static void rle_decompress(PageParam src, VecParam des, DecompressState& stt) {
	auto* in_pos_arr  = reinterpret_cast<rle_idx_t*>(src.arr[stt.cur_src_arr - 0]);
	auto* out_pos_arr = reinterpret_cast<rle_idx_t*>(des.arr[stt.cur_des_arr - 0]);
	auto* in_val_arr  = reinterpret_cast<T*>(src.arr[stt.cur_des_arr - 1]);
	auto* out_val_arr = reinterpret_cast<T*>(des.arr[stt.cur_des_arr - 1]);

	// [FIXME]
	// zero copy,
	// not possible yet! after memory pool.
	//	out_val_arr = in_val_arr;
	//	out_pos_arr = in_pos_arr;

	std::memcpy(out_pos_arr, in_pos_arr, vec_bsz<rle_idx_t>());
	/* Lest pos_t determine the size of val_arr. */
	std::memcpy(out_val_arr, in_val_arr, (in_pos_arr[1023] + 1) * sizeof(T));

	FLS_PLOG_KEY_VALUE("in_val_arr", ToStr::to_str<T>(in_val_arr));
	FLS_PLOG_KEY_VALUE("in_pos_arr", ToStr::to_str<rle_idx_t>(in_pos_arr));

	FLS_PLOG_KEY_VALUE("out_val_arr", ToStr::to_str<T>(out_val_arr));
	FLS_PLOG_KEY_VALUE("out_pos_arr", ToStr::to_str<rle_idx_t>(out_pos_arr));

	stt.cur_src_arr -= 2;
	stt.cur_des_arr -= 2;
}

template <typename T>
de_cmpr_fun_t rle::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return rle_decompress<uint64_t>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return rle_decompress<uint64_t>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return rle_decompress<uint32_t>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return rle_decompress<uint32_t>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, rle::ResolveDecompressFunc)

} // namespace fastlanes