#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/trs_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls_gen/transpose/transpose.hpp"
#include <cstring>

namespace fastlanes {
template <typename T>
static void trs_cmpr(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	T* in_arr = reinterpret_cast<T*>(src_vec.buf_arr[stt.cur_src_buff].mutable_data());

	FLS_PLOG_KEY_VALUE("before transpose", ToStr::to_str<T>(in_arr));
	/* Fixme: not efficient. implement inplace_transpose */
	T tmp[vec_n_tup()];
	generated::transpose::fallback::scalar::transpose_i(in_arr, tmp);
	std::memcpy(in_arr, tmp, vec_bsz<T>());
	FLS_PLOG_KEY_VALUE("after transpose", ToStr::to_str<T>(in_arr));
}

template <typename T>
cmpr_fun_t trs::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return trs_cmpr<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return trs_cmpr<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return trs_cmpr<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return trs_cmpr<uint32_t>;
	} else if constexpr (std::is_same<T, int16_t>()) {
		return trs_cmpr<uint16_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return trs_cmpr<uint16_t>;
	} else if constexpr (std::is_same<T, int8_t>()) {
		return trs_cmpr<uint8_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return trs_cmpr<uint8_t>;
	} else if constexpr (std::is_same_v<T, dbl_pt>) {
		return trs_cmpr<dbl_pt>;
	}

	FLS_ABORT("THIS IS NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, trs::ResolveCompressFunc)

} // namespace fastlanes