// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// rust/vendor/fastlanes/include/fls/stt/type.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_STT_TYPE_HPP
#define FLS_STT_TYPE_HPP

#include <cstdint>

namespace fastlanes {
enum class SttT : uint8_t {
	MINMAX,
	HISTOGRAM,
};
} // namespace fastlanes
#endif // FLS_STT_TYPE_HPP
