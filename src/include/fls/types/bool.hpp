#ifndef FLS_TYPES_bool_HPP
#define FLS_TYPES_bool_HPP

#include "fls/std/string.hpp"
#include <cstdint>

namespace fastlanes {

uint8_t parse_bool(string_view val_str);
string  bool_formatter(uint8_t value);

} // namespace fastlanes

#endif // FLS_TYPES_bool_HPP
