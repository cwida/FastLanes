#ifndef FLS_COR_LYT_PAGE_PAGE_HDR_HPP
#define FLS_COR_LYT_PAGE_PAGE_HDR_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp_type.hpp"

namespace fastlanes {
class PageHdr {
public:
	void     Load(const uint8_t* p);   //
	uint32_t Serialize();              //
	void     AddCompressedArrBitMap(); //
public:
	ExpT     exp_t;
	uint8_t  m_var_t;
	uint16_t reserved_for_compressed_arr;
	uint16_t vec_c;
	uint16_t not_reserved;
	void     Reset();
};
} // namespace fastlanes
#endif // FLS_COR_LYT_PAGE_PAGE_HDR_HPP
