#include "fls/utl/bit_util.hpp"

namespace fastlanes {
void bit::set(uint64_t& unit, uint16_t pos) {
	if (pos == 0) {
		unit |= 1ULL;
	} else {
		unit |= 1ULL << pos;
	}
}

bsz_t bit::to_bytes(const bsz_t bits) {
	return (bits + 7) / 8;
}
} // namespace fastlanes