#ifndef FLS_COR_LYT_PAGE_PAGE_PARAM_HPP
#define FLS_COR_LYT_PAGE_PAGE_PARAM_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"

// clang-format off
namespace fastlanes { class Page; }
// clang-format on

namespace fastlanes {
class PageParam {
public:
	void Init(Page& page); //
public:
	uint8_t* arr[CFG::PG::BUF_C]; //
};
} // namespace fastlanes
#endif // FLS_COR_LYT_PAGE_PAGE_PARAM_HPP
