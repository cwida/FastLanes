// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/validitymask_operator.cpp
// ────────────────────────────────────────────────────────
#include "fls/expression/validitymask_operator.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/alias.hpp"
#include "fls/common/assert.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"
#include "fls/std/vector.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/types/validitymask.hpp"
#include <cstdint> // for uint8_t
#include <utility> // for std::move"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_validitymask_opr
\*--------------------------------------------------------------------------------------------------------------------*/
enc_validitymask_opr::enc_validitymask_opr(const PhysicalExpr& physical_expr,
                                           const col_pt&       column,
                                           ColumnDescriptorT&  column_descriptor,
                                           InterpreterState&   state)
    : typed_column_view(column) {

	validitymask_segment = make_unique<Segment>();
}

void enc_validitymask_opr::to_validitymask() {
	FLS_ASSERT_NOT_NULL_POINTER(typed_column_view.Data())
	validitymask.encode(typed_column_view.Data());
	validitymask_segment->Flush(validitymask.data(), ValidityMask::byte_size());
}

void enc_validitymask_opr::PointTo(const n_t vec_idx) {
	typed_column_view.PointTo(vec_idx);
}

void enc_validitymask_opr::MoveSegments(vector<up<Segment>>& segments) {
	segments.push_back(std::move(validitymask_segment));
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_validitymask_opr
\*--------------------------------------------------------------------------------------------------------------------*/
dec_validitymask_opr::dec_validitymask_opr(const ColumnView& column_view, const n_t segment_idx)
    : data_segment(column_view.GetSegment(segment_idx)) {
}

void dec_validitymask_opr::PointTo(const n_t vec_n) {
	data_segment.PointTo(vec_n);
}

uint8_t* dec_validitymask_opr::Data() {
	return reinterpret_cast<uint8_t*>(data_segment.data);
}

void dec_validitymask_opr::Materialize(n_t vec_idx, TypedCol<uint8_t>& des_col) {
	const auto old_size = des_col.data.size();   // size *before* we grow
	des_col.data.resize(old_size + CFG::VEC_SZ); // make room for one vector

	uint8_t* bytemap = des_col.data.data() + old_size; // start of the new slice

	// If data_segment.data is really a uint8_t* (or similar), make sure the cast is
	// safe/aligned.  Using const here makes the intent clearer.
	ValidityMask::decode(reinterpret_cast<const uint64_t*>(data_segment.data), // source bitmap
	                     bytemap);                                             // destination bytes
}

} // namespace fastlanes
