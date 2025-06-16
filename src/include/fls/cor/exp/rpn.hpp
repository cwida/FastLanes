#ifndef FLS_COR_EXP_RPN_HPP
#define FLS_COR_EXP_RPN_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/cor/fls_data_type.hpp"
#include "fls/cor/prm/prm_type.hpp"

namespace fastlanes {
class RPN {
public:
	uint8_t src_buf_c;
	uint8_t des_buf_c;
	uint8_t prm_c;
	bool    is_transposed;
	prm_t   prm_arr[CFG::PRM::PRM_C];
	fls_t   typ_arr[CFG::PRM::PRM_C];
	bool    is_compressed[CFG::PRM::PRM_C];
	uint8_t header_sz;
};
} // namespace fastlanes
#endif // FLS_COR_EXP_RPN_HPP
