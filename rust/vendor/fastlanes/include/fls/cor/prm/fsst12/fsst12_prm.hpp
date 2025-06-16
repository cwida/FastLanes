#ifndef FLS_COR_PRM_FSST12_FSST12_PRM_HPP
#define FLS_COR_PRM_FSST12_FSST12_PRM_HPP

#include "fls/common/common.hpp"
#include "fls/cor/fun.hpp"
#include "fls/cor/prm/fsst12/fsst12.h"
#include <vector>

namespace fastlanes {
class fsst12 {
public:
	/* Calibrate a FSST12 symboltable from a batch of strings (it is best to provide at least 16KB of data). */
	/* byte_c: byte-lengths of the inputs */
	/* str_arr: string start pointers. */
	static fsst12_encoder_t* build_fsst12_encoder(n_t c, ofs_t offset_arr[], uint8_t str_arr[]);
	/* Convert offsets to array of pointer.*/
	static up<std::vector<uint8_t*>> offset_to_pointer(n_t c, ofs_t offset_arr[], uint8_t str_arr[]);
	/* Convert offsets to array of pointer.*/
	static up<std::vector<ofs_t>> offset_to_length(n_t c, ofs_t offset_arr[]);
	// clang-format off
  template <typename T> static cmpr_fun_t ResolveCompressFunc();
  template <typename T> static de_cmpr_fun_t ResolveDecompressFunc();
};
} // namespace fast_lanes
#endif // FLS_COR_PRM_FSST12_FSST12_PRM_HPP
