#ifndef FLS_COR_PRM_FSST_FSST_PRM_HPP
#define FLS_COR_PRM_FSST_FSST_PRM_HPP

#include "fls/cor/fun.hpp"
#include "fls/cor/prm/fsst/fsst.h"
#include "fls/std/vector.hpp"

namespace fastlanes {
class fsst_wrapper {
public:
	/* Calibrate a FSST symboltable from a batch of strings (it is best to provide at least 16KB of data). */
	/* byte_c: byte-lengths of the inputs */
	/* str_arr: string start pointers. */
	static fsst_encoder_t* build_fsst_encoder(n_t n_values, ofs_t offset_arr[], uint8_t str_arr[]);
	/* Convert offsets to array of pointer.*/
	static up<vector<uint8_t*>> offset_to_pointer(n_t n_values, const ofs_t offset_arr[], uint8_t str_arr[]);
	/* Convert offsets to array of pointer.*/
	static void offset_to_pointer(uint8_t* in_byte_arr, const ofs_t* in_offset_arr, uint8_t** output_str_arr);
	/* Convert offsets to array of pointer.*/
	static up<vector<ofs_t>> offset_to_length(n_t n_values, const ofs_t offset_arr[]);
	// clang-format off
	template <typename T> static cmpr_fun_t ResolveCompressFunc();
	template <typename T> static de_cmpr_fun_t ResolveDecompressFunc();
};
} // namespace fast_lanes
#endif // FLS_COR_PRM_FSST_FSST_PRM_HPP
