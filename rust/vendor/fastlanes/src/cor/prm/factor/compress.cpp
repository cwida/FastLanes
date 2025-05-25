#include "fls/cor/prm/factor.hpp" // for pack
#include <cstdint>                // for uint64_t, uint32_t, uint16_t, uint8_t
#include <sys/cdefs.h>            // for __restrict

namespace fastlanes { namespace factor {
void Compress64(Vec& src_vec, Vec& des_vec, CompressState& compress_state) {
	/*	*/        /* Reinterpret. */
	              /*
auto *factor_col = reinterpret_cast<int64_t *>(state.col1);
auto  src_vec  = reinterpret_cast<int64_t *>(src);
auto  factor     = factor_col[0];
	          
*/ /* Compute. */ /*
  for (size_t i = 0; i < 1024; ++i) {
	  src_vec[i] = src_vec[i] - factor;
  }

  */ /* State. */ /*
//	state.col1 += 8;*/
}
}} // namespace fastlanes::factor