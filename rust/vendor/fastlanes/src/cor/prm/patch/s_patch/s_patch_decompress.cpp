#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/patch/s_patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"

namespace fastlanes {
template <typename T>
static void s_patch_decompress(PageParam src, VecParam des, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(des.arr[stt.cur_des_arr])

	auto*    exc_arr     = reinterpret_cast<T*>(src.arr[stt.cur_src_arr - 1]);
	auto*    exc_pos_arr = reinterpret_cast<uint16_t*>(src.arr[stt.cur_src_arr - 0]);
	auto*    out_arr     = reinterpret_cast<T*>(des.arr[stt.cur_des_arr]);
	uint16_t exc_c       = exc_pos_arr[0];

	for (uint16_t i {0}; i < exc_c; ++i) {
		auto next_pos     = exc_pos_arr[i + 1];
		out_arr[next_pos] = exc_arr[i];
	}

	stt.cur_src_arr -= 2;

	FLS_PLOG_KEY_VALUE("exc_arr", ToStr::to_str<T>(exc_arr, exc_c));
	FLS_PLOG_KEY_VALUE("after s_patch", ToStr::to_str<T>(out_arr));
}

template <typename T>
de_cmpr_fun_t s_patch::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return s_patch_decompress<T>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return s_patch_decompress<T>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return s_patch_decompress<T>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return s_patch_decompress<T>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, s_patch::ResolveDecompressFunc)

} // namespace fastlanes