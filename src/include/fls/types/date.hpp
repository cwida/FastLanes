// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/types/date.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_TYPES_DATE_HPP
#define FLS_TYPES_DATE_HPP

#include "fls/std/string.hpp"

namespace fastlanes {

int32_t parse_date(string_view val_str);
string  date_formatter(int32_t days_since_epoch);

} // namespace fastlanes

#endif // FLS_TYPES_DATE_HPP
