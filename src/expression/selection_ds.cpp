// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/expression/selection_ds.cpp
// ────────────────────────────────────────────────────────
#include "fls/expression/selection_ds.hpp"
#include "fls/common/alias.hpp"

namespace fastlanes {

// TOOD[predicate_pushdown] : always start with bitmap
SelectionDS::SelectionDS(const LogicalExpr& logical_expression)
    : logical_expression(logical_expression)
    , idx_arr()
    , n_selected_values(0)
    , bitmap()
    , use_bitmap(false) {
	//
}

void SelectionDS::Reset() {
	// set index array to zero
	for (n_t value_idx {0}; value_idx < idx_arr.size(); ++value_idx) {
		idx_arr[value_idx] = 0;
	}

	// set
	for (n_t idx {}; idx < bitmap.size(); ++idx) {
		idx_arr[idx] = 0;
	}

	// size
	n_selected_values = 0;
}

} // namespace fastlanes
