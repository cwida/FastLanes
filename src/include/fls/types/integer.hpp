// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/types/integer.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_TYPES_INTEGER_HPP
#define FLS_TYPES_INTEGER_HPP

#include "fls/std/string.hpp"
#include "fls/types/integer.hpp"

namespace fastlanes {

template <typename INTEGER_T>
INTEGER_T parse_integer(const string& val_str);

} // namespace fastlanes

#endif // FLS_TYPES_INTEGER_HPP
