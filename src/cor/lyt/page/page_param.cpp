#include "fls/cor/lyt/page/page_param.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include <type_traits>

namespace fastlanes {
void PageParam::Init(Page& page) {
	/* Pointer = start_p + offset! */
	for (size_t i {0}; i < page.arr_c; ++i) {
		arr[i] = page.start_p + page.off_arr.arr[i];
	}
}
} // namespace fastlanes