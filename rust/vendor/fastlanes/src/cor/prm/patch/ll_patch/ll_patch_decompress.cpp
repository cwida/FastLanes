#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/patch/ll_patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"

namespace fastlanes {
template <typename T>
static void ll_patch_decompress(PageParam src, VecParam des, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(des.arr[stt.cur_des_arr])

	auto*     exc_p       = reinterpret_cast<T*>(src.arr[stt.cur_src_arr - 1]);
	auto*     exc_pos_arr = reinterpret_cast<rle_idx_t*>(src.arr[stt.cur_src_arr - 0]);
	auto*     out_p       = reinterpret_cast<T*>(des.arr[stt.cur_des_arr]);
	auto      base        = *(reinterpret_cast<T*>(stt.base));
	rle_idx_t exc_c       = exc_pos_arr[0];

	FLS_PLOG_KEY_VALUE("exe_c", std::to_string(exc_c));

	rle_idx_t first_pos = exc_pos_arr[1];
	FLS_PLOG_KEY_VALUE("first_pos", std::to_string(first_pos));

	FLS_PLOG_KEY_VALUE("out_arr", ToStr::to_str<T>(out_p));
	FLS_PLOG_KEY_VALUE("exc_arr", ToStr::to_str<T>(exc_p, exc_c));
	FLS_PLOG_KEY_VALUE("[exe_c, exc_first_pos] ", ToStr::to_str<rle_idx_t>(exc_pos_arr, 2));

	T cur = first_pos;
	T offset {0};
	for (T i {0}; i < exc_c; ++i) {
		offset     = out_p[cur] - base + 1;
		out_p[cur] = exc_p[i];
		cur += offset;
	}

	stt.cur_src_arr -= 2;

	FLS_PLOG_KEY_VALUE("out_p", ToStr::to_str<T>(out_p));
}

template <typename T>
de_cmpr_fun_t ll_patch::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return ll_patch_decompress<uint64_t>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return ll_patch_decompress<uint64_t>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return ll_patch_decompress<uint32_t>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return ll_patch_decompress<uint32_t>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, ll_patch::ResolveDecompressFunc)

} // namespace fastlanes