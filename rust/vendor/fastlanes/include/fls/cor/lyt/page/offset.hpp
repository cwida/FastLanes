#ifndef FLS_COR_LYT_PAGE_OFFSET_HPP
#define FLS_COR_LYT_PAGE_OFFSET_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Page;

/*--------------------------------------------------------------------------------------------------------------------*/

class OffArr {
public:
	explicit OffArr(); //
public:
	void InitDecompress(Page& page); //
	void InitCompress(n_t arr_c);    //
	n_t  ttl_sz();                   // return sz of one element;
	n_t  arr_c();                    //
public:
	ofs_t arr[CFG::PG::BUF_C]; //
private:
	n_t m_arr_c; //
};
} // namespace fastlanes
#endif // FLS_COR_LYT_PAGE_OFFSET_HPP