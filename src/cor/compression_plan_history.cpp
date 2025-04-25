#include "fls/cor/compression_plan_history.hpp"
#include "fls/cor/compression_plan.hpp"
#include <strstream>

namespace fast_lanes {
void History::Save(sp<IDebug> debug_sp) { /* NOLINT*/
	m_plan_sp_vec.push_back(debug_sp);
}

void History::Last(std::ostream& out) {
	m_plan_sp_vec.back()->ToCsv(out);
}
void History::ToTable(TxtTab& txt_tab) {
	m_plan_sp_vec.back()->ToTable(txt_tab);
}
} // namespace fast_lanes