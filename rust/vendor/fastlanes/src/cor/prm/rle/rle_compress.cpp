#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/rle_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"
#include "fls_gen/transpose/transpose.hpp"

namespace fastlanes {
template <typename T>
static void rle_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	const auto* in_arr      = reinterpret_cast<const T*>(src_vec.buf_arr[stt.cur_src_buff + 0].data());
	auto*       pos_arr     = reinterpret_cast<rle_idx_t*>(src_vec.buf_arr[stt.cur_src_buff + 1].mutable_data());
	auto*       tmp_pos_arr = reinterpret_cast<rle_idx_t*>(des_vec.buf_arr[stt.cur_des_buff + 1].mutable_data());

	rle_idx_t pos_val;
	for (n_t i {0}; i < vec_n_tup(); ++i) {
		auto cur_val = in_arr[i];

		if (i == 0) {
			cur_val = in_arr[0];
			pos_val = 0;
			des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAppend(&cur_val, sizeof(T));
			tmp_pos_arr[i] = pos_val;
			continue;
		}

		if (cur_val != in_arr[i - 1]) {
			des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAppend(&cur_val, sizeof(T));
			pos_val += 1;
		}
		tmp_pos_arr[i] = pos_val;
	}

	generated::transpose::fallback::scalar::transpose_i(tmp_pos_arr, pos_arr);

	stt.cur_src_buff += 1;
	stt.cur_des_buff += 1;

	FLS_PLOG_KEY_VALUE("pos_arr", ToStr::to_str<rle_idx_t>(pos_arr));
	FLS_PLOG_KEY_VALUE("tmp_pos_arr", ToStr::to_str<rle_idx_t>(tmp_pos_arr));
}

template <typename T>
cmpr_fun_t rle::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return rle_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return rle_compress<uint64_t>;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return rle_compress<uint32_t>;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return rle_compress<uint32_t>;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, rle::ResolveCompressFunc)

} // namespace fastlanes