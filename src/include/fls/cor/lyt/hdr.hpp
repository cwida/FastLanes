#ifndef FLS_COR_HDR_HPP
#define FLS_COR_HDR_HPP

#include "fls/cor/cfg.hpp"
#include "fls/cor/exp/exp_type.hpp" //
#include <cstddef>                  // for byte
#include <iosfwd>                   // for string
#include <stdint.h>                 // for uint8_t, uint32_t

namespace fast_lanes {
struct Hdr {
public:
	uint16_t code;    // Special code, unique to FAST_LANES.
	uint8_t  major_v; // major version.
	uint8_t  minor_v; // minor version.
	uint8_t  micro_v; // micro version.
	exp_t    expr_t;  // Expr type.
	uint8_t  exp_vrt; // Expr variant.
	uint8_t  has_dic; // Has Dictionary.
public:
	bool         IsFastLane();                 //
	static Hdr   Load(std::byte* p);           //
	static Hdr   Load(uint8_t* p);             //
	std::string  ToString();                   //
	std::string& operator<<(std::string& lhs); //
};

static constexpr Hdr FLS_HDR {
    CFG::SPECIAL_CODE,
    CFG::MAJOR_VERSION,
    CFG::MINOR_VERSION,
    CFG::MICRO_VERSION,
    exp_t::INVALID,
    0,
    0,
};
} // namespace fast_lanes
#endif // FLS_COR_HDR_HPP
