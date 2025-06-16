#ifndef FLS_COR_PAGE_TYPE_HPP
#define FLS_COR_PAGE_TYPE_HPP

#include <cstdint>

namespace fastlanes {
enum class PageT : uint8_t {
	DICT_PAGE = 0,
	DATA_PAGE = 1,
}; //
} // namespace fastlanes
#endif // FLS_COR_PAGE_TYPE_HPP
