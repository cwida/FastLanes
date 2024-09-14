#include "fls/utl/util.hpp"
#include "fls/common/assert.hpp"

namespace fastlanes {
uint64_t MAX_BIT(uint64_t bw) {
	FLS_ASSERT_CORRECT_BW(bw);

	return (1UL << bw) - 1UL;
}
} // namespace fastlanes