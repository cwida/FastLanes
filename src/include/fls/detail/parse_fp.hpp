#ifndef FLS_DETAIL_PARSE_FP_HPP
#define FLS_DETAIL_PARSE_FP_HPP

#include "fls/std/string.hpp"
#include <charconv> // for integer from_chars detection
#include <system_error>

// Detect FP from_chars support: advertised __cpp_lib_to_chars and not libc++
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611) && !defined(_LIBCPP_VERSION)
#define FASTLANES_HAS_FP_FROM_CHARS 1
#else
#define FASTLANES_HAS_FP_FROM_CHARS 0
#endif

namespace fastlanes::detail {

/// Parse a decimal string into FloatT (float or double),
/// throwing std::invalid_argument or std::out_of_range on error.
template <typename FloatT>
FloatT parse_fp(const std::string& s);

} // namespace fastlanes::detail

#endif // FLS_DETAIL_PARSE_FP_HPP
