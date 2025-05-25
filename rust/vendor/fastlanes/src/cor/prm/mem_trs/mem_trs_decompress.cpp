#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/mem_trs.hpp"
#include "fls_gen/untranspose/untranspose.hpp"

namespace fastlanes {
static void Decompress64(PageParam src, VecParam des, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(des.arr[stt.cur_des_arr])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr])

	generated::untranspose::fallback::scalar::untranspose_i(reinterpret_cast<uint64_t*>(src.arr[stt.cur_src_arr++]),
	                                                        reinterpret_cast<uint64_t*>(des.arr[stt.cur_des_arr++]));
}

static void Decompress32(PageParam src, VecParam des, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(des.arr[stt.cur_des_arr])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr])

	generated::untranspose::fallback::scalar::untranspose_i(reinterpret_cast<uint32_t*>(src.arr[stt.cur_src_arr++]),
	                                                        reinterpret_cast<uint32_t*>(des.arr[stt.cur_des_arr++]));
}

template <typename T>
de_cmpr_fun_t mem_trs::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return Decompress64;
	}
	if constexpr (std::is_same<T, uint64_t>()) {
		return Decompress64;
	}
	if constexpr (std::is_same<T, int32_t>()) {
		return Decompress32;
	}
	if constexpr (std::is_same<T, uint32_t>()) {
		return Decompress32;
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, mem_trs::ResolveDecompressFunc)

} // namespace fastlanes