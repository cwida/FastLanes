#ifndef FLS_EXPRESSION_SELECTION_DS_HPP
#define FLS_EXPRESSION_SELECTION_DS_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/std/array.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class LogicalExpr;
/*--------------------------------------------------------------------------------------------------------------------*/

class SelectionDS {
	using bitmap_unit_t = uint64_t;

public:
	explicit SelectionDS(const LogicalExpr&);
	SelectionDS(const SelectionDS&)            = delete; // non construction-copyable
	SelectionDS& operator=(const SelectionDS&) = delete; // non copyable
public:
	void Reset();

public:
	///! the logical expression this selectionds belongs to
	const LogicalExpr&            logical_expression;
	array<vec_idx_t, CFG::VEC_SZ> idx_arr;
	vec_idx_t                     n_selected_values;
	array<bitmap_unit_t, 16>      bitmap;
	bool                          use_bitmap;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_SELECTION_DS_HPP
