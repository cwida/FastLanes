// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/analyze_operator_unsigned.cpp
// ────────────────────────────────────────────────────────
// Unsigned-type explicit instantiations of enc_analyze_opr.
// The template definitions live in analyze_operator.cpp.
// This file exists solely to parallelize compilation.
// ────────────────────────────────────────────────────────
#include "analyze_operator_impl.hpp"
#include "fls/common/alias.hpp"
#include "fls/expression/analyze_operator.hpp"

namespace fastlanes {

template struct enc_analyze_opr<u64_pt, false>;
template struct enc_analyze_opr<u32_pt, false>;
template struct enc_analyze_opr<u16_pt, false>;
template struct enc_analyze_opr<u08_pt, false>;
template struct enc_analyze_opr<u64_pt, true>;
template struct enc_analyze_opr<u32_pt, true>;
template struct enc_analyze_opr<u16_pt, true>;
template struct enc_analyze_opr<u08_pt, true>;

} // namespace fastlanes
