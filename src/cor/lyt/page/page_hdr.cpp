#include "fls/cor/lyt/page/page_hdr.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp"
#include <type_traits>

namespace fastlanes {
void PageHdr::Load(const uint8_t* p) {
	FLS_ASSERT_NOT_NULL_POINTER(p)

	*this = *reinterpret_cast<const PageHdr*>(p);
}

uint32_t PageHdr::Serialize() {
	return 0;
}

void PageHdr::AddCompressedArrBitMap() {
}
void PageHdr::Reset() {
	vec_c = 0;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Static Assert:
\---------------------------------------------------------------------------------------------------------------------*/
static_assert(std::is_standard_layout<PageHdr>() && std::is_trivial<PageHdr>(),
              "PageHdr should be a standard-layout trivial type.");
static_assert(sizeof(PageHdr) == CFG::PG::HDR_SZ, "PageHdr should be 4-byte long.");
} // namespace fastlanes