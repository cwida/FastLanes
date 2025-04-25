#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/b_ffor_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"
#include "fls_gen/unffor/unffor.hpp"

namespace fastlanes {
template <typename T>
static void b_ffor_decompress(PageParam src, VecParam des, DecompressState& stt) {
}

template <typename T>
de_cmpr_fun_t b_ffor_prm::ResolveDecompressFunc() {
	if constexpr (std::is_same<T, int64_t>()) {
		return b_ffor_decompress<uint64_t>;
	} else if constexpr (std::is_same<T, uint64_t>()) {
		return b_ffor_decompress<uint64_t>;
	} else if constexpr (std::is_same<T, int32_t>()) {
		return b_ffor_decompress<uint32_t>;
	} else if constexpr (std::is_same<T, uint32_t>()) {
		return b_ffor_decompress<uint32_t>;
	} else if constexpr (std::is_same<T, uint16_t>()) {
		return b_ffor_decompress<uint16_t>;
	} else if constexpr (std::is_same<T, uint8_t>()) {
		return b_ffor_decompress<uint8_t>;
	}

	FLS_ABORT("THIS IS NOT SUPPORTED!")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, b_ffor_prm::ResolveDecompressFunc)
// FLS_FTS(de_cmpr_fun_t, b_ffor_prm::ResolveDecompressFunc, parquet::FixedLenByteArray)
// FLS_FTS(de_cmpr_fun_t, b_ffor_prm::ResolveDecompressFunc, parquet::Int96)
// FLS_FTS(de_cmpr_fun_t, b_ffor_prm::ResolveDecompressFunc, parquet::ByteArray)
} // namespace fastlanes