#ifndef FLS_COR_LYT_PAGE_TYPE_HPP
#define FLS_COR_LYT_PAGE_TYPE_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
enum class PageT : uint8_t { // NOLINT
	INVALID    = 0,
	COMPRESS   = 1,
	DECOMPRESS = 2,
};

std::string to_string(PageT t);
} // namespace fastlanes

#endif // FLS_COR_LYT_PAGE_TYPE_HPP
