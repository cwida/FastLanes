#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/fsst/fsst_prm.hpp"
#include "fls/logger/logger.hpp"
#include "fls/printer/to_str.hpp"

namespace fastlanes {
static void fls_fsst_decompress(PageParam src, VecParam des, DecompressState& stt) {}

template <typename T>
de_cmpr_fun_t fsst::ResolveDecompressFunc() {
	return fls_fsst_decompress;
}
/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(de_cmpr_fun_t, fsst::ResolveDecompressFunc)

} // namespace fastlanes