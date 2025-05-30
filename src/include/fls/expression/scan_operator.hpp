#ifndef FLS_EXPRESSION_SCAN_EXPRESSION_HPP
#define FLS_EXPRESSION_SCAN_EXPRESSION_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/reader/segment.hpp"
#include "fls/table/chunk.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Segment;
struct ColumnDescriptorT;
class PhysicalExpr;
struct InterpreterState;
class ColumnView;
struct InterpreterState;
class RowgroupReader;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*\
* dec_scan_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_scan_opr {
public:
	explicit dec_scan_opr(const ColumnView& column_view, InterpreterState& state);

public:
	void PointTo(n_t vec_n);
	void Scan(n_t vec_idx);
	PT   data[CFG::VEC_SZ];

public:
	SegmentView data_segment;
};
} // namespace fastlanes
#endif