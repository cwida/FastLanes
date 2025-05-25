#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/ffor_prm.hpp"
#include "fls/ffor.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"

namespace fastlanes {
template <typename T>
static void ffor_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto* base_p = reinterpret_cast<const T*>(stt.base);
	auto* in_arr = reinterpret_cast<T*>(src_vec.buf_arr[stt.cur_src_buff].mutable_data());
	auto  out_p  = reinterpret_cast<T*>(des_vec.buf_arr[stt.cur_des_buff + 2].mutable_data());

	generated::ffor::fallback::scalar::ffor(in_arr, out_p, stt.bw, base_p);

	des_vec.buf_arr[stt.cur_des_buff + 0].UnsafeAppend(&stt.bw, 1);
	des_vec.buf_arr[stt.cur_des_buff + 1].UnsafeAppend(stt.base, sizeof(T));
	des_vec.buf_arr[stt.cur_des_buff + 2].UnsafeAdvance(ffor_prm<T>::vec_sz(stt.bw));

	FLS_PLOG_KEY_VALUE("VEC", ToStr::to_str<T>(const_cast<T*>(in_arr)))
	FLS_PLOG_KEY_VALUE("BW", std::to_string(stt.bw))
	FLS_PLOG_KEY_VALUE("BASE", ToStr::to_hex(stt.base, sizeof(T)));

	stt.cur_des_buff += 3;
}

template <typename T>
cmpr_fun_t ffor_prm<T>::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return ffor_compress<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return ffor_compress<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return ffor_compress<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return ffor_compress<uint32_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return ffor_compress<uint16_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return ffor_compress<uint8_t>;
	}

	FLS_ABORT("THIS IS NOT SUPPORTED!")
	return nullptr;
}

template <typename T>
n_t ffor_prm<T>::vec_sz(uint8_t bw) {
	FLS_ASSERT_CORRECT_BW(bw)

	return bw * vec_sz_1bit();
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(ffor_prm)

} // namespace fastlanes