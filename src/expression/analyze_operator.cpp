// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/analyze_operator.cpp
// ────────────────────────────────────────────────────────
// Signed-type instantiations + Histogram class instantiations.
// Unsigned-type instantiations are in analyze_operator_unsigned.cpp.
// ────────────────────────────────────────────────────────
#include "fls/expression/analyze_operator.hpp"
#include "analyze_operator_impl.hpp" // NOLINT(misc-include-cleaner) — template definitions needed for explicit instantiations below
#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/expression/data_type.hpp"

namespace fastlanes {

template <typename PT>
void AnalyzeHistogram<PT>::Cal(PT* data) {
	val_vec.clear();
	rep_vec.clear();

	/* Sort. */
	std::sort(data, data + CFG::VEC_SZ);

	/* Push the first one. */
	val_vec.push_back(data[0]);
	rep_vec.push_back(1);

	/* Make the histogram. */
	for (n_t i = 1; i < CFG::VEC_SZ; ++i) {
		/* Same value. Increase the rep*/
		if (data[i] == data[i - 1]) {
			rep_vec.back() += 1;
		}
		/* New seq. add it to vec. Set the rep to one. */
		else {
			val_vec.push_back(data[i]);
			rep_vec.push_back(1);
		}
	}
}

template <typename PT>
void AnalyzeHistogram<PT>::Reset() {
	val_vec.clear();
	rep_vec.clear();
} //

template class AnalyzeHistogram<u08_pt>;
template class AnalyzeHistogram<u16_pt>;
template class AnalyzeHistogram<u32_pt>;
template class AnalyzeHistogram<u64_pt>;
template class AnalyzeHistogram<i08_pt>;
template class AnalyzeHistogram<i16_pt>;
template class AnalyzeHistogram<i32_pt>;
template class AnalyzeHistogram<i64_pt>;

template struct enc_analyze_opr<i64_pt, false>;
template struct enc_analyze_opr<i32_pt, false>;
template struct enc_analyze_opr<i16_pt, false>;
template struct enc_analyze_opr<i08_pt, false>;
template struct enc_analyze_opr<i64_pt, true>;
template struct enc_analyze_opr<i32_pt, true>;
template struct enc_analyze_opr<i16_pt, true>;
template struct enc_analyze_opr<i08_pt, true>;

} // namespace fastlanes
