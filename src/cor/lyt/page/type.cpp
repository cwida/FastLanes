#include "fls/cor/lyt/page/type.hpp"
#include "fls/common/common.hpp"
#include <string>

namespace fastlanes {
std::string to_string(PageT t) {
	switch (t) {
	case PageT::COMPRESS:
		return {"COMPRESS"};
	case PageT::DECOMPRESS:
		return {"DECOMPRESS"};
	case PageT::INVALID:
	default:
		return {"INVALID"};
	}

	return {};
}
} // namespace fastlanes