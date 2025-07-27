// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/types/timestamp.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_TYPES_TIMESTAMP_HPP
#define FLS_TYPES_TIMESTAMP_HPP

#include "fls/std/string.hpp"
#include <cstdint>

namespace fastlanes {

/**
 * Parses an ISO-8601–like timestamp string into microseconds since
 * 1970-01-01T00:00:00 UTC.
 *
 * Supported format:
 *   "YYYY-MM-DDThh:mm:ss"
 *   "YYYY-MM-DDThh:mm:ss.ffffff"   (1–6 fractional digits; right-padded or truncated to microseconds)
 *
 * Examples:
 *   "2025-06-04T13:45:30"
 *   "2025-06-04T13:45:30.123"
 *   "2025-06-04T13:45:30.123456"
 *
 * @param ts_str
 *   Input timestamp string (interpreted as UTC)
 * @return
 *   Number of microseconds since Unix epoch (1970-01-01T00:00:00 UTC)
 * @throws std::invalid_argument
 *   If format is incorrect or numeric fields fail to parse
 * @throws std::out_of_range
 *   If the resulting timestamp exceeds int64_t range
 */
int64_t parse_timestamp(string_view ts_str);

/**
 * Formats a microseconds-since-epoch timestamp back into an ISO-8601 string:
 *   "YYYY-MM-DDThh:mm:ss.ffffff"
 * If the fractional microseconds are zero, the output is
 *   "YYYY-MM-DDThh:mm:ss"
 *
 * @param microseconds_since_epoch
 *   Microseconds since Unix epoch (1970-01-01T00:00:00 UTC)
 * @return
 *   Formatted ISO-8601 timestamp string in UTC
 * @throws std::runtime_error
 *   If the reconstructed date falls outside a valid range
 */
string timestamp_formatter(int64_t microseconds_since_epoch);

} // namespace fastlanes

#endif // FLS_TYPES_TIMESTAMP_HPP
