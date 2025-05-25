#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/ffor_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls_gen/unffor/unffor.hpp"
#include <cstring>

namespace fastlanes {
template <typename T>
static void ffor_decompress(PageParam src, VecParam des, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(des.arr[stt.cur_des_arr])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 2])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 1])
	FLS_ASSERT_NOT_NULL_POINTER(src.arr[stt.cur_src_arr - 0])

	uint8_t bw     = *src.arr[stt.cur_src_arr - 2];
	auto*   base_p = reinterpret_cast<const T*>(src.arr[stt.cur_src_arr - 1]);
	auto*   in_p   = reinterpret_cast<const T*>(src.arr[stt.cur_src_arr - 0]);
	auto*   out_p  = reinterpret_cast<T*>(des.arr[stt.cur_des_arr]);

	generated::unffor::fallback::scalar::unffor(in_p, out_p, bw, base_p);

	FLS_PLOG_KEY_VALUE("VEC", ToStr::to_str<T>(reinterpret_cast<T*>(out_p)))
	FLS_PLOG_KEY_VALUE("BW", std::to_string(bw))
	FLS_PLOG_KEY_VALUE("BASE", ToStr::to_hex(stt.base, sizeof(T)));

	stt.cur_src_arr -= 3;
	std::memcpy(stt.base, base_p, sizeof(T));
}

template <typename T>
de_cmpr_fun_t ffor_prm<T>::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return ffor_decompress<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return ffor_decompress<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return ffor_decompress<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return ffor_decompress<uint32_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return ffor_decompress<uint16_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return ffor_decompress<uint8_t>;
	}

	FLS_ABORT("THIS IS NOT SUPPORTED!")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(ffor_prm)
} // namespace fastlanes