// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/data_parallelize_patch_operator.cpp
// ────────────────────────────────────────────────────────
#include "fls/expression/data_parallelize_patch_operator.hpp"
#include "fls/common/string.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/alp_expression.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/interpreter.hpp"
#include "fls/expression/physical_expression.hpp"
#include "fls/primitive/patch/patch.hpp"
#include "fls/reader/column_view.hpp"
#include "fls/reader/segment.hpp"
#include "fls/unffor.hpp"
#include <cstring>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*\
 * enc_data_parallel_patch_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
enc_data_parallel_patch_opr<PT>::enc_data_parallel_patch_opr(const PhysicalExpr& expr,
                                                             const col_pt&       column,
                                                             ColumnDescriptorT&  column_descriptor,
                                                             InterpreterState&   state) {
	visit(overloaded {
	          [&](const sp<enc_alp_opr<PT>>& opr) { opr->data_parallelize = true; },
	          [&](std::monostate&) { FLS_UNREACHABLE(); },
	          [&](auto& arg) { FLS_UNREACHABLE_WITH_TYPE(arg); },
	      },
	      expr.operators[state.cur_operator++]);
}

template struct enc_data_parallel_patch_opr<dbl_pt>;
template struct enc_data_parallel_patch_opr<flt_pt>;

} // namespace fastlanes
