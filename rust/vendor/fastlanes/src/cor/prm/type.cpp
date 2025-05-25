#include "fls/cor/prm/prm_type.hpp"
#include <string>

namespace fastlanes {
std::string to_string(prm_t prm_t) {
	switch (prm_t) {
	case prm_t::INVALID:
		break;
	case prm_t::ANALYZE:
		return {"ANALYZE"};
	case prm_t::PA_ANALYZE:
		return {"PA_ANALYZE"};
	case prm_t::MEM_CPY:
		return {"MEM_CPY"};
	case prm_t::TRS:
		return {"TRS"};
	case prm_t::MEM_TRS:
		return {"MEM_TRS"};
	case prm_t::LL_PATCH:
		return {"LL_PATCH"};
	case prm_t::B_FFOR:
		return {"B_FFOR"};
	case prm_t::RLE:
	case prm_t::RSUM:
	case prm_t::BITPACK:
	case prm_t::FACTOR:
	case prm_t::FSST:
	case prm_t::B_PATCH:
	case prm_t::S_PATCH:
	case prm_t::FFOR:
	case prm_t::ZER_CPY:
		// TODO [FIXME]
	default:
		break;
	}

	return {};
}
} // namespace fastlanes