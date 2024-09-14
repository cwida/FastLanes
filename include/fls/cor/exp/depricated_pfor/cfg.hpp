#ifndef FLS_EXP_PFOR_CFG_HPP
#define FLS_EXP_PFOR_CFG_HPP

#include "fls/cmn/common.hpp"
#include "fls/cor/cfg.hpp"
#include "fls/exp/pfor/exp.hpp"

namespace fast_lanes { namespace pfor {
class Cfg {
public:
	static constexpr count_t  VERSION    = 1;
	static constexpr count_t  VAL_O      = fast_lanes::Cfg::HDR_SZ + 8; /* From start of FLS_SEGMENT. */
	static constexpr count_t  COL_O      = VAL_O + 8 + 8;               /* 2 VAL of SIZE 8. */
	static constexpr count_t  FUN_O      = COL_O + 4 + 4;               /* 2 COL_OFFSET of SIZE 4. */
	static constexpr count_t  FUN_C      = 3;                           /* 3 FUN_OFFSET of SIZE 4. */
	static constexpr count_t  EXP_SZ     = 44;                          /**/
	static constexpr count_t  START      = 44;                          /**/
	static constexpr count_t  BULK_RATIO = 2;                           /**/
	static constexpr double   EXC_RATIO  = 0.05;                        /* We accept only 0.05 percent exception. */
	static constexpr exp::Hdr EXPR_HDR {
	    FUN_C,
	    VAL_O,
	    COL_O,
	    FUN_O,
	};
};
}}     // namespace fast_lanes::pfor
#endif // FLS_EXP_PFOR_CFG_HPP
