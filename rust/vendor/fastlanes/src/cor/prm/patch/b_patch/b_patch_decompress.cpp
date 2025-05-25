#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/patch/b_patch.hpp"
#include "fls/cor/prm/patch/patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"

namespace fastlanes {
template <typename T>
static void b_patch_decompress(PageParam src, VecParam des, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(des.arr[stt.cur_des_arr])

	auto* exc_arr    = reinterpret_cast<T*>(src.arr[stt.cur_src_arr - 1]);
	auto* bitmap_arr = reinterpret_cast<uint64_t*>(src.arr[stt.cur_src_arr - 0]);
	auto* out_p      = reinterpret_cast<T*>(des.arr[stt.cur_des_arr]);

	FLS_PLOG_KEY_VALUE("out_p", ToStr::to_str<T>(out_p));

	typed_patch<T>::b_patch_decompress(out_p, bitmap_arr, exc_arr);

	stt.cur_src_arr -= 2;

	FLS_PLOG_KEY_VALUE("out_p", ToStr::to_str<T>(out_p));
	FLS_PLOG_KEY_VALUE("bitmap", ToStr::to_str<void>(reinterpret_cast<void*>(bitmap_arr)));
}

template <typename T>
de_cmpr_fun_t b_patch::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return b_patch_decompress<uint64_t>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return b_patch_decompress<uint64_t>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return b_patch_decompress<uint32_t>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return b_patch_decompress<uint32_t>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, b_patch::ResolveDecompressFunc)

} // namespace fastlanes