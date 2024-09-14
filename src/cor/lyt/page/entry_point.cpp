#include "fls/cor/lyt/page/entry_point.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/logger/logger.hpp"
#include "fls/printer/to_str.hpp"
#include <cstring>
#include <sstream>

namespace fastlanes {
void ep_arr::InitDecompress(Page& page) {
	FLS_ASSERT_NOT_NULL_POINTER(page.start_p)
	FLS_ASSERT_CORRECT_N(page.vec_c())
	FLS_ASSERT_CORRECT_N(page.arr_c)

	m_vec_c   = page.vec_c();
	m_arr_c   = page.arr_c;
	m_vec_num = 0;
	m_start_p = page.start_p + page.off_arr.ttl_sz() + CFG::PG::HDR_SZ;
}

void ep_arr::load_and_next() {
	FLS_ASSERT_CORRECT_NUM(m_vec_num, m_vec_c)
	FLS_ASSERT_NOT_NULL_POINTER(m_start_p)
	FLS_ASSERT_CORRECT_N(m_vec_c)

	FLS_LOG_TABLE_KEY_VALUE("vec_n", std::to_string(m_vec_num))
	FLS_LOG_TABLE_KEY_VALUE("vec_c", std::to_string(m_vec_c))

	/* the first ep_arr is always 0 and has not been stored! */
	if (m_vec_num == 0) {
		memset(arr, 0, m_arr_c * CFG::PG::ENTRY_POINT_SZ);
		m_vec_num++;
		FLS_LOG_TABLE_KEY_VALUE("ep", ToStr::to_str(*this))
		return;
	}

	memcpy(arr, m_start_p, m_arr_c * CFG::PG::ENTRY_POINT_SZ);
	FLS_LOG_TABLE_KEY_VALUE("ep", ToStr::to_str(*this))
	m_start_p += m_arr_c * CFG::PG::ENTRY_POINT_SZ;
	m_vec_num++;
}

void ep_arr::InitCompress(Page& page) {
	FLS_ASSERT_CORRECT_N(page.arr_c)

	m_arr_c   = page.arr_c;
	m_vec_c   = 0;
	m_vec_num = 0;

	/* init all entry points to 0. */
	for (auto& ep : arr) {
		ep = 0;
	}
}

n_t  ep_arr::sz() { return m_arr_c * CFG::PG::ENTRY_POINT_SZ; }
void ep_arr::Reset() {
	m_vec_num = 0;
	m_vec_c   = 0;
}

ep_arr::ep_arr() = default;
} // namespace fastlanes
