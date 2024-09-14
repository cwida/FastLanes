#ifndef FLS_EXP_PFOR_PYL_HPP
#define FLS_EXP_PFOR_PYL_HPP

#include <iosfwd>      // for string
#include <stdint.h>    // for uint32_t, uint64_t
#include <type_traits> // for is_pod, is_standard_layout, is_trivial

namespace fast_lanes { namespace pfor {
struct __attribute__((packed)) Pyl {
public:
	uint64_t     bit_c;                        /**/
	std::byte    base[8];                      /* base can be negative! treat is as 64-bit data. */
	uint32_t     bitpacked_col;                /**/
	uint32_t     exception_col;                /**/
	uint32_t     bitpack_f;                    /**/
	uint32_t     plus_f;                       /**/
	uint32_t     patch_f;                      /**/
	std::string& operator<<(std::string& lhs); /**/
	std::string  ToString();                   /**/
public:
};
static_assert(std::is_trivial<pfor::Pyl>(), "pfor::Pyl should be TRIVIAL.");
static_assert(std::is_pod<pfor::Pyl>(), "pfor::Pyl should be a POD.");
static_assert(std::is_standard_layout<pfor::Pyl>(), "pfor::Pyl should have STANDARD layout.");
static_assert(sizeof(pfor::Pyl) == 36, "pfor::Pyl should be of size 36.");
}}     // namespace fast_lanes::pfor
#endif // FLS_EXP_PFOR_PYL_HPP
