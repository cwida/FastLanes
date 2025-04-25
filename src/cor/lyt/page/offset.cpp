#include "fls/cor/lyt/page/offset.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/logger/logger.hpp"
#include "fls/utl/to_str.hpp"
#include <cstring>
#include <sstream>

namespace fastlanes {
OffArr::OffArr() = default;

void OffArr::InitDecompress(Page& page) {
	FLS_ASSERT_CORRECT_N(page.arr_c)
	FLS_ASSERT_NOT_NULL_POINTER(page.start_p)

	m_arr_c = page.arr_c;
	memcpy(arr, page.start_p + CFG::PG::HDR_SZ, m_arr_c * CFG::PG::OFFSET_SZ);
	FLS_PLOG_KEY_VALUE("off_arr", ToStr::to_str(*this).c_str())
}

void OffArr::InitCompress(n_t arr_c) {
	FLS_ASSERT_CORRECT_N(arr_c)
	m_arr_c = arr_c;
}

n_t OffArr::ttl_sz() {
	FLS_ASSERT_CORRECT_SZ(m_arr_c)
	return m_arr_c * CFG::PG::OFFSET_SZ;
}
n_t OffArr::arr_c() {
	return m_arr_c;
}
} // namespace fastlanes
