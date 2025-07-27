// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/expression/data_parallelize_patch_operator.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_EXPRESSION_DATA_PARALLEL_PATCH_OPERATOR_HPP
#define FLS_EXPRESSION_DATA_PARALLEL_PATCH_OPERATOR_HPP

#include "fls/cuda/common.hpp"
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
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_alp_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct enc_data_parallel_patch_opr {
	explicit enc_data_parallel_patch_opr(const PhysicalExpr& expr,
	                                     const col_pt&       column,
	                                     ColumnDescriptorT&  column_descriptor,
	                                     InterpreterState&   state);
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_DATA_PARALLEL_PATCH_OPERATOR_HPP
