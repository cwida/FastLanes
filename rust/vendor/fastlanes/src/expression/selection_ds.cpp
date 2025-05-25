#include "fls/expression/selection_ds.hpp"

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
	for (idx_t value_idx {0}; value_idx < idx_arr.size(); ++value_idx) {
		idx_arr[value_idx] = 0;
	}

	// set
	for (idx_t idx {}; idx < bitmap.size(); ++idx) {
		idx_arr[idx] = 0;
	}

	// size
	n_selected_values = 0;
}

} // namespace fastlanes
