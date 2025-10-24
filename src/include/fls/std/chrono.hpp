// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/std/chrono.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_STD_CHRONO_HPP
#define FLS_STD_CHRONO_HPP

#ifdef COMPATIABLE_CXX17_HEADER
#include "fls/std/hh_date.hpp"
namespace std { namespace chrono {
using date::January;

using date::day;
using date::month;
using date::year;
using date::year_month_day;

using date::days;
using date::sys_days;
}} // namespace std::chrono
#else
#include <chrono>
#endif

namespace fastlanes {
} // namespace fastlanes

#endif // FLS_STD_CHRONO_HPP
