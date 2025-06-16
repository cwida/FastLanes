#include "fls/cfg/cfg.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/patch/b_patch.hpp"
#include "fls/cor/prm/patch/patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"

namespace fastlanes {
template <typename T>
static void b_patch_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto* in_arr = reinterpret_cast<T*>(src_vec.buf_arr[stt.cur_src_buff].mutable_data());

	patch::b_patch_compress(stt.exc_pos_arr, stt.exc_c, stt.bitmap);
	FLS_PLOG_KEY_VALUE("bitmap", ToStr::to_str<void>(reinterpret_cast<void*>(stt.bitmap)));
	des_vec.buf_arr[stt.cur_des_buff + 1].UnsafeAppend(&stt.bitmap, CFG::BitMap::SZ);

	for (n_t i {0}; i < stt.exc_c; i++) {
		des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAppend(&in_arr[stt.exc_pos_arr[i]], sizeof(T));
	}

	stt.cur_des_buff += 2;
	FLS_PLOG_KEY_VALUE("bitmap", ToStr::to_str<void>(reinterpret_cast<void*>(stt.bitmap)));
}

template <typename T>
cmpr_fun_t b_patch::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return b_patch_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return b_patch_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return b_patch_compress<uint32_t>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return b_patch_compress<uint32_t>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, b_patch::ResolveCompressFunc)

} // namespace fastlanes
