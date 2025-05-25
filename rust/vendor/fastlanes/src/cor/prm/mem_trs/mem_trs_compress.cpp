#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/mem_trs.hpp"
#include "fls/utl/util.hpp"
#include "fls_gen/transpose/transpose.hpp"
#include <type_traits>

namespace fastlanes {
static void Compress64(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto           size = src_vec.buf_arr[stt.cur_src_buff].length();
	const uint8_t* in_p = src_vec.buf_arr[stt.cur_src_buff++].mutable_data();

	/* Fixme: not efficient. could be easily solved by a better local buffer anf memory pool manager */
	uint8_t tmp[1024 * 8];
	generated::transpose::fallback::scalar::transpose_i(reinterpret_cast<const uint64_t*>(in_p),
	                                                    reinterpret_cast<uint64_t*>(tmp));

	des_vec.buf_arr[stt.cur_des_buff++].UnsafeAppend(tmp, size);
}

static void Compress32(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto           size = src_vec.buf_arr[stt.cur_src_buff].length();
	const uint8_t* in_p = src_vec.buf_arr[stt.cur_src_buff++].mutable_data();

	uint8_t tmp[1024 * 8];
	generated::transpose::fallback::scalar::transpose_i(reinterpret_cast<const uint32_t*>(in_p),
	                                                    reinterpret_cast<uint32_t*>(tmp));

	des_vec.buf_arr[stt.cur_des_buff++].UnsafeAppend(tmp, size);
}

template <typename T>
cmpr_fun_t mem_trs::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return Compress64;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return Compress64;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return Compress32;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return Compress32;
	}

	FLS_ABORT("IT IS NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, mem_trs::ResolveCompressFunc)

} // namespace fastlanes