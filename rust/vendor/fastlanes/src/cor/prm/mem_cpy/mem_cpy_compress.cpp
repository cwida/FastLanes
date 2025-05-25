#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/mem_cpy_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"

namespace fastlanes {
template <typename T>
static void mem_cpy_cmpr(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	T* in_arr = reinterpret_cast<T*>(src_vec.buf_arr[stt.cur_src_buff].mutable_data());

	des_vec.buf_arr[stt.cur_des_buff].UnsafeAppend(in_arr, src_vec.buf_arr[stt.cur_src_buff].length());

	FLS_PLOG_KEY_VALUE("cur_vec", ToStr::to_str<T>(in_arr));

	stt.cur_des_buff += 1;
	stt.cur_src_buff += 1;
}

static void off_mem_cpy_cmpr(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto* in_arr = src_vec.buf_arr[stt.cur_src_buff].mutable_data();

	/* in smart offset array the last tuple show the number of bytes. */
	uint32_t byte_c = reinterpret_cast<uint32_t*>(src_vec.buf_arr[stt.cur_src_buff + 1].mutable_data())[1023];
	// FLS_ASSERT_LE(byte_c, CFG::BUF::SZ) // todo[buf]

	des_vec.buf_arr[stt.cur_des_buff].UnsafeAppend(in_arr, byte_c);

	FLS_PLOG_KEY_VALUE("cur_vec", ToStr::to_str<uint8_t>(in_arr));

	stt.cur_des_buff += 1;
	stt.cur_src_buff += 1;
}

template <typename T>
cmpr_fun_t mem_cpy::ResolveCompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return mem_cpy_cmpr<uint64_t>;
	} else if constexpr (std::is_same_v<T, uint64_t>) {
		return mem_cpy_cmpr<uint64_t>;
	} else if constexpr (std::is_same_v<T, int32_t>) {
		return mem_cpy_cmpr<uint32_t>;
	} else if constexpr (std::is_same_v<T, uint32_t>) {
		return mem_cpy_cmpr<uint32_t>;
	} else if constexpr (std::is_same_v<T, uint16_t>) {
		return mem_cpy_cmpr<uint16_t>;
	} else if constexpr (std::is_same_v<T, uint8_t>) {
		return mem_cpy_cmpr<uint8_t>;
	} else if constexpr (std::is_same_v<T, str_pt>) {
		return off_mem_cpy_cmpr;
	} else if constexpr (std::is_same_v<T, dbl_pt>) {
		return mem_cpy_cmpr<dbl_pt>;
	}

	FLS_ABORT("IT IS NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, mem_cpy::ResolveCompressFunc)

} // namespace fastlanes