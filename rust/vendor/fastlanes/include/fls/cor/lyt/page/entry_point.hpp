#ifndef FLS_COR_LYT_PAGE_ENTRY_POINT_HPP
#define FLS_COR_LYT_PAGE_ENTRY_POINT_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include <vector>

/* Rep -> data[arr_c]_32 : array of 32-bit integers as offset could be 32 bit
 * First Entry Point is always arrays of zero -> we start storing from entry_point[1];
 *
 */

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Page;

/*--------------------------------------------------------------------------------------------------------------------*/

class EpArr {
public:
	explicit EpArr(); //
public:
	void InitDecompress(Page& page); //
	void InitCompress(Page& page);   //
	void Reset();                    //
public:
	void load_and_next(); //
	n_t  sz();            // return sz of one element;
public:
	ep_t           arr[CFG::PG::BUF_C]; //
	uint16_t       m_vec_c;             //
	uint16_t       m_vec_num;           //
	const uint8_t* m_start_p;           //
	uint8_t        m_arr_c;             //
};
} // namespace fastlanes
#endif // FLS_COR_LYT_PAGE_ENTRY_POINT_HPP
