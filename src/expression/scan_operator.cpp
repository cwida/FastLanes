#include "fls/expression/scan_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/primitive/copy/fls_copy.hpp"
#include "fls/reader/column_view.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_scan_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
dec_scan_opr<PT>::dec_scan_opr(const ColumnView& column_view, InterpreterState& state)
    : data_segment(column_view.GetSegment(2)) {
}

template <typename PT>
void dec_scan_opr<PT>::PointTo(const n_t vec_n) {
	data_segment.PointTo(vec_n);
}

template <typename PT>
void dec_scan_opr<PT>::Scan(n_t vec_idx) {
	PointTo(vec_idx);

	copy<PT>(reinterpret_cast<PT*>(data_segment.data), data);
}

template struct dec_scan_opr<u32_pt>;

} // namespace fastlanes