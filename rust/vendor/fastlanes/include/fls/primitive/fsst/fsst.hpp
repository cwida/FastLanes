#ifndef FLS_PRIMITIVE_FSST_FSST_HPP
#define FLS_PRIMITIVE_FSST_FSST_HPP

#include "fls/common/alias.hpp"
#include "fls/cor/prm/fsst/fsst.h"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class FlsStrColumnView;
class Buf;
/*--------------------------------------------------------------------------------------------------------------------*/
class fsst_helper {
public:
	static fsst_encoder_t* make_fsst(const FlsStrColumnView& col);

	static fsst_encoder_t* make_fsst(n_t n_vals, Buf& length_buf, Buf& string_p_buf);

	static size_t fsst_compress(
	    fsst_encoder_t* encoder,    /* IN: encoder obtained from fsst_create(). */
	    size_t          nstrings,   /* IN: number of strings in batch to compress. */
	    uint32_t        len_in[],   /* IN: byte-lengths of the inputs */
	    unsigned char*  str_in[],   /* IN: input string start pointers. */
	    size_t          outsize,    /* IN: byte-length of output buffer. */
	    unsigned char*  output,     /* OUT: memory buffer to put the compressed strings in (one after the other). */
	    ofs_t*          out_offsets /* OUT: output string start pointers. Will all point into [output,output+size). */
	);
};

} // namespace fastlanes

#endif