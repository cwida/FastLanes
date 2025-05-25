#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/rsum_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls_gen/rsum/rsum.hpp"

namespace fastlanes {
template <typename T>
static void rsum_decompress(PageParam src, VecParam des, DecompressState& stt) {
	auto* in_p            = reinterpret_cast<const T*>(des.arr[stt.cur_des_arr - 0]);
	auto* out_p           = reinterpret_cast<T*>(des.arr[stt.cur_des_arr - 1]);
	auto* delta_bases_arr = reinterpret_cast<T*>(src.arr[stt.cur_src_arr]);

	generated::rsum::fallback::scalar::rsum(in_p, out_p, delta_bases_arr);

	FLS_PLOG_KEY_VALUE("cur_vec", ToStr::to_str<T>(reinterpret_cast<T*>(out_p)))
	FLS_PLOG_KEY_VALUE("delta_bases_arr", ToStr::to_str<T>(delta_bases_arr, 16));

	stt.cur_src_arr -= 1;
	stt.cur_des_arr -= 2;
}

template <typename T>
de_cmpr_fun_t rsum::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return rsum_decompress<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return rsum_decompress<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return rsum_decompress<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return rsum_decompress<uint32_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return rsum_decompress<uint16_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return rsum_decompress<uint8_t>;
	}

	FLS_ABORT("THIS IT NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, rsum::ResolveDecompressFunc)

} // namespace fastlanes