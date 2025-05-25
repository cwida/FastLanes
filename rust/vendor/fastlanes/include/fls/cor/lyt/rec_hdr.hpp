#ifndef FLS_COR_LYT_REC_HDR_HPP
#define FLS_COR_LYT_REC_HDR_HPP
#include "fls/common/common.hpp"

namespace fastlanes {
class rec_hdr {
public:
	bw_t      bw;
	uint8_t   empty;
	rle_idx_t exc_c;
	base_t    base;
};
static_assert(sizeof(rec_hdr) == 12);

class alp_hdr {
public:
	n_t n_t;
};
static_assert(sizeof(alp_hdr) == 8);

} // namespace fastlanes
#endif // FLS_COR_LYT_REC_HDR_HPP
