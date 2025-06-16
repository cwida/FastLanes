#ifndef FLS_COR_LYT_PAGE_PAGE_HPP
#define FLS_COR_LYT_PAGE_PAGE_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/cor/lyt/page/entry_point.hpp"
#include "fls/cor/lyt/page/offset.hpp"
#include "fls/cor/lyt/page/page_hdr.hpp"
#include "fls/cor/lyt/page/page_param.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Exp;
class Vec;
class BufferBuilder;

/*--------------------------------------------------------------------------------------------------------------------*/

class Page {
public:
	Page();  //
	~Page(); //
public:
	void      InitCompress(const sp<Exp>& exp_sp);                     //
	void      InitDecompress(const uint8_t* p, const sp<Exp>& exp_up); //
	void      Reset();                                                 //
	void      Absorb(Vec& vec);                                        //
	void      OffsetToSink(Buf& sink);                                 //
	PageHdr   hdr();                                                   //
	void      vec_c_inc();                                             //
	n_t       size_of(Vec& vec);                                       //
	uint16_t  vec_c();                                                 //
	PageParam page_params();                                           //
	n_t       get_total_sz();                                          //
	bool      Verify();                                                //
public:
	Buf       buf_arr[CFG::PG::BUF_C]; //
	Buf       ep_arr_buf;              //
	uint8_t   arr_c;                   //
	n_t       tup_c;                   //
	n_t       m_ttl_sz;                //
	PageHdr   pg_hdr;                  //
	OffArr    off_arr;                 //
	EpArr     ep_arr;                  //
	PageParam params;                  //
	uint8_t*  start_p;                 //
};
} // namespace fastlanes
#endif // FLS_COR_LYT_PAGE_PAGE_HPP
