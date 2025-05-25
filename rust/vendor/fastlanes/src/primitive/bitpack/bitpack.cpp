#include "fls/primitive/bitpack/bitpack.hpp"
#include "fls/cfg/cfg.hpp"

namespace fastlanes {
uint64_t calculate_bitpacked_vector_size(uint8_t bw) {
	constexpr uint64_t SIZE_OF_BYTE = 8;

	FLS_ASSERT_LE(bw, 64)

	return bw * CFG::VEC_SZ / SIZE_OF_BYTE;
}
} // namespace fastlanes