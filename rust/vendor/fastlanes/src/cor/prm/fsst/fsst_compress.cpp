#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/engine.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/fsst/fsst.h"
#include "fls/cor/prm/fsst/fsst_prm.hpp"
#include <cstdint>     // for uint64_t, uint32_t, uint16_t, uint8_t
#include <sys/cdefs.h> // for __restrict

namespace fastlanes {
void fls_fsst_compress(Vec& src_vec, Vec& des_vec, CompressState& stt) {
	auto*    encoder = reinterpret_cast<fsst_encoder_t*>(stt.eng_state.analyze_state_up->fsst_encoder);
	uint8_t* str_arr = src_vec.buf_arr[stt.cur_src_buff + 0].mutable_data();
	auto*    off_arr = reinterpret_cast<uint32_t*>(src_vec.buf_arr[stt.cur_src_buff + 1].mutable_data());
	auto     tmp     = fsst_wrapper::offset_to_pointer(1024, off_arr, str_arr);

	auto* out_p   = des_vec.buf_arr[stt.cur_des_buff + 0].mutable_data();
	auto* len_out = reinterpret_cast<uint32_t*>(des_vec.buf_arr[stt.cur_des_buff + 1].mutable_data());
	auto* str_out = reinterpret_cast<uint8_t**>(des_vec.buf_arr[stt.cur_des_buff + 2].mutable_data());

	/*
	    fsst_encoder_t *encoder,    IN: encoder obtained from fsst_create().
	    size_t          nstrings,   IN: number of strings in batch to compress.
	    size_t          len_in[],   IN: byte-lengths of the inputs
	    unsigned char  *str_in[],   IN: input string start pointers.
	    size_t          outsize,    IN: byte-length of output buffer.
	    unsigned char  *output,     OUT: memory buffer to put the compressed strings in (one after the other).
	    size_t          len_out[],  OUT: byte-lengths of the compressed strings.
	    unsigned char  *str_out[]   OUT: output string start pointers. Will all point into [output,output+size).*/

	fsst_compress(encoder, 1024, off_arr, tmp->data(), 1024 * 8, out_p, len_out, str_out);

	stt.cur_des_buff += 3;
	stt.cur_src_buff += 2;
}

template <typename T>
cmpr_fun_t fsst_wrapper::ResolveCompressFunc() {
	return fls_fsst_compress;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_FTS(cmpr_fun_t, fsst_wrapper::ResolveCompressFunc)

} // namespace fastlanes