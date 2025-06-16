#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/patch/ll_patch.hpp"
#include "fls/cor/prm/patch/patch.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"

#pragma clang diagnostic ignored "-Wconversion"

namespace fastlanes {
template <typename T>
static void ll_patch_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto*       in_arr = reinterpret_cast<T*>(src_vec.buf_arr[stt.cur_src_buff].mutable_data());
	const auto* base_p = reinterpret_cast<const T*>(stt.base);

	rle_idx_t new_c {0};
	rle_idx_t old_c {0};
	//[fixme]
	rle_idx_t tmp[vec_n_tup()];
	switch (stt.exc_c) {
	case 0:
		break;
	default:
		T curr_pos  = stt.exc_pos_arr[old_c++];
		T next_pos  = stt.exc_pos_arr[old_c++];
		T max_range = 1 << stt.bw;

		FLS_ASSERT_CORRECT_POS(curr_pos)
		do {
			tmp[new_c++] = curr_pos;
			auto con     = patch::is_compulsory_exc(curr_pos, next_pos, max_range);
			if (old_c <= stt.exc_c && con) {
				curr_pos += max_range;
			} else {
				curr_pos = next_pos;
				next_pos = stt.exc_pos_arr[old_c++];
			}
		} while (old_c <= stt.exc_c + 1);
		stt.exc_c = new_c;
	}

	/* push the number of exceptions. */
	des_vec.buf_arr[stt.cur_des_buff + 1].UnsafeAppend(&stt.exc_c, sizeof(rle_idx_t));
	/* push the pos of first exception. */
	des_vec.buf_arr[stt.cur_des_buff + 1].UnsafeAppend(&tmp[0], sizeof(rle_idx_t));

	/* push the exceptions and fix the linked list. */
	for (rle_idx_t i {0}; i < stt.exc_c; ++i) {
		des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAppend(&in_arr[tmp[i]], sizeof(T));

		auto gap       = tmp[i + 1] - tmp[i] + (*base_p) - 1;
		in_arr[tmp[i]] = gap;
	}

	FLS_PLOG_KEY_VALUE("after ll_patch", ToStr::to_str<T>(in_arr));
	stt.cur_des_buff += 2;
}

template <typename T>
cmpr_fun_t ll_patch::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return ll_patch_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return ll_patch_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return ll_patch_compress<uint32_t>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return ll_patch_compress<uint32_t>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, ll_patch::ResolveCompressFunc)

} // namespace fastlanes
