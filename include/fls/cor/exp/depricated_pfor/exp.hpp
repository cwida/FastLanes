#ifndef FLS_EXP_PFOR_EXP_HPP
#define FLS_EXP_PFOR_EXP_HPP

/*
  PFOR

 -Expand-------> FUN_P(FUN_+(FUN_B(COL_0, VAL_0), VAL_1), COL_1)

 -Rpn----------> COL_O, VAL_O, FUN_B, VAL_1, FUN_+, COL_1, FUN_P

 -Separate-----> [[VAL_0, VAL_1], [COL_0, COL_1], [FUN_B, FUN_+, FUN_P]]

 -Store--------> [[2,2,3,-], [VAL_0, VAL_1], [COL_0, COL_1], [FUN_B, FUN_+ , FUN_P]]

 -Represent----> [[8, 8, 8], [64,64], [32,32], [16,16,16]]

 -Init---------> states_tab

 todo Don't like it. flexible pfor is better.
 */

#include "fls/exp/hdr.hpp"      // for Hdr
#include "fls/exp/pfor/pyl.hpp" // for Pyl
#include <cstddef>              // for byte
#include <stdint.h>             // for uint8_t
#include <type_traits>          // for is_pod, is_standard_layout, is_trivial
namespace fast_lanes { namespace pfor {
struct Exp {
public:
	Exp() = default; /**/
public:
	void Load(std::byte* p); /**/
	void Load(uint8_t* p);   /**/
public:
	exp::Hdr  hdr; /**/
	pfor::Pyl pyl; /**/
};
static_assert(std::is_trivial<pfor::Exp>(), "fast_lanes::pfor::Exp should be a POD.");
static_assert(std::is_pod<pfor::Exp>(), "fast_lanes::pfor::Exp should be a POD.");
static_assert(std::is_standard_layout<pfor::Exp>(), "fast_lanes::pfor::Exp should be a POD.");
static_assert(sizeof(pfor::Exp) == 44, "fast_lanes::Header should be of size 8.");
}}     // namespace fast_lanes::pfor
#endif // FLS_EXP_PFOR_EXP_HPP
