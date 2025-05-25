#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/b_ffor_prm.hpp"
#include "fls/ffor.hpp"
#include "fls/utl/to_str.hpp"
#include "fls/utl/util.hpp"

namespace fastlanes {
template <typename T>
static void ffor_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
}

template <typename T>
cmpr_fun_t b_ffor_prm::ResolveCompressFunc() {
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

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, b_ffor_prm::ResolveCompressFunc)

} // namespace fastlanes