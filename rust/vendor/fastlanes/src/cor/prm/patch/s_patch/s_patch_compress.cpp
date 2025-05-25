#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/patch/s_patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/util.hpp"

namespace fastlanes {
template <typename T>
static void s_patch_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	/* first, push the number of exceptions */
	auto* in_arr = reinterpret_cast<T*>(src_vec.buf_arr[stt.cur_src_buff].mutable_data());

	des_vec.buf_arr[stt.cur_des_buff + 1].UnsafeAppend(&stt.exc_c, sizeof(uint16_t));

	for (n_t i {0}; i < stt.exc_c; i++) {
		/* [TODO], after recursive compression store bw bits of exception. */
		des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAppend(&in_arr[stt.exc_pos_arr[i]], sizeof(T));
		des_vec.buf_arr[stt.cur_des_buff + 1].UnsafeAppend(&stt.exc_pos_arr[i], sizeof(uint16_t));
	}

	stt.cur_des_buff += 2;
}

template <typename T>
cmpr_fun_t s_patch::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return s_patch_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return s_patch_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return s_patch_compress<uint32_t>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return s_patch_compress<uint32_t>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, s_patch::ResolveCompressFunc)

} // namespace fastlanes