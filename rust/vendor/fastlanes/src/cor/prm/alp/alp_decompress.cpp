#include "alp.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/alp_prm.hpp"
#include "fls/primitive/unffor/unffor.hpp"

namespace fastlanes {
static void alp_decompress(PageParam src, VecParam des, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(des.arr[stt.cur_des_arr])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 5])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 4])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 3])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 2])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 1])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 0])

	auto* ffor_arr    = reinterpret_cast<const int64_t*>(src.arr[stt.cur_src_arr - 0]);
	auto* alp_mtd_arr = reinterpret_cast<const alp_mtd_t*>(src.arr[stt.cur_src_arr - 1]);
	auto* base_arr    = reinterpret_cast<const int64_t*>(src.arr[stt.cur_src_arr - 2]);
	// auto* exc_c_arr   = reinterpret_cast<const uint16_t*>(src.arr[stt.cur_src_arr - 3]);
	// auto* pos_arr     = reinterpret_cast<const uint16_t*>(src.arr[stt.cur_src_arr - 4]);
	// auto* exc_arr     = reinterpret_cast<const dbl_pt*>(src.arr[stt.cur_src_arr - 5]);

	auto* dec_dbl_arr = reinterpret_cast<dbl_pt*>(des.arr[stt.cur_des_arr]);

	int64_t unffor_arr[vec_sz()]; // TODO BUFFER_POOl
	auto    alp_mtd = alp_mtd_arr[0];

	generated::unffor::fallback::scalar::unffor(ffor_arr, unffor_arr, alp_mtd.bw, base_arr);
	alp::decoder<double>::decode(unffor_arr, alp_mtd.fac, alp_mtd.exp, dec_dbl_arr);
	// alp::decoder<double>::patch_exceptions(dec_dbl_arr, exc_arr, pos_arr, exc_c_arr); TODO

	stt.cur_src_arr -= 6;
}

template <typename T>
de_cmpr_fun_t alp_prm::ResolveDecompressFunc() {
	if constexpr (std::is_same_v<T, dbl_pt>) {
		return alp_decompress;
	} else {
		FLS_ABORT("ONLY WORKS FOR DOUBLE")
	}

	FLS_ABORT("THIS IS NOT SUPPORTED!")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, alp_prm::ResolveDecompressFunc)
} // namespace fastlanes