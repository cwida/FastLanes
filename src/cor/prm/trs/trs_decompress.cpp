#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/trs_prm.hpp"

namespace fastlanes {
template <typename T>
static void trs_decmpr(PageParam src, VecParam des, DecompressState& stt) {
	//	auto *in_arr  = reinterpret_cast<const T *>(src.arr[stt.cur_src_arr - 0]);
	//	auto *out_arr = reinterpret_cast<T *>(des.arr[stt.cur_des_arr - 0]);
}

template <typename T>
de_cmpr_fun_t trs::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return trs_decmpr<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return trs_decmpr<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return trs_decmpr<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return trs_decmpr<uint32_t>;
	} else if constexpr (std::is_same<T, int16_t>()) {
		return trs_decmpr<uint16_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return trs_decmpr<uint16_t>;
	} else if constexpr (std::is_same<T, int8_t>()) {
		return trs_decmpr<uint8_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return trs_decmpr<uint8_t>;
	} else if constexpr (std::is_same<T, dbl_pt>()) {
		return trs_decmpr<dbl_pt>;
	}

	FLS_ABORT("THIS IS NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, trs::ResolveDecompressFunc)

} // namespace fastlanes