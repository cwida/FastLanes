#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/rsum_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"
#include "fls_gen/unrsum/unrsum.hpp"

namespace fastlanes {
template <typename T>
static void rsum_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto* in_arr = reinterpret_cast<T*>(src_vec.buf_arr[stt.cur_src_buff + 0].mutable_data());

	/* delta_bases_arr -> des[i + 0] */
	des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAppend(in_arr, 1024 / 8);

	/* rsum_data -> src[i + 0] */
	generated::unrsum::fallback::scalar::unrsum_inplace(in_arr);

	stt.cur_des_buff += 1;

	FLS_PLOG_KEY_VALUE("in_arr after unrsum", ToStr::to_str<T>(in_arr));
}

template <typename T>
cmpr_fun_t rsum::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return rsum_compress<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return rsum_compress<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return rsum_compress<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return rsum_compress<uint32_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return rsum_compress<uint16_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return rsum_compress<uint8_t>;
	}

	FLS_ABORT("THIS IT NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, rsum::ResolveCompressFunc)

} // namespace fastlanes