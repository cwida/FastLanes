#include "fls/primitive/predicate/equal.hpp"
#include "fls/expression/selection_ds.hpp"

namespace fastlanes {

/*--------------------------------------------------------------------------------------------------------------------*\
 * equality
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void euqality_pt_func(const PT* __restrict array_pointer, PT value, uint64_t* __restrict bitmap) {
	//
	// TOOD[predicate_pushdown] : implement this
}

template <typename PT>
vec_idx_t euqality_pt_func(const PT* __restrict array_pointer, PT value, vec_idx_t* __restrict idx_arr) {

	vec_idx_t n_selected_values {0};
	for (vec_idx_t value_idx {0}; value_idx < CFG::VEC_SZ; ++value_idx) {
		// naive implemention
		if (array_pointer[value_idx] == value) {
			idx_arr[n_selected_values] = value_idx;
			n_selected_values++;
		}
	}
	return n_selected_values;
}

template <typename PT>
void eq_vector_constant_func(const PT* __restrict array_pointer, PT value, SelectionDS& selection_ds) {
	auto& bitmap  = selection_ds.bitmap;
	auto& idx_arr = selection_ds.idx_arr;

	if (selection_ds.use_bitmap) {
		euqality_pt_func(array_pointer, value, bitmap.data());
	} else {
		selection_ds.n_selected_values = euqality_pt_func(array_pointer, value, idx_arr.data());
	}
}

template void      euqality_pt_func<i64_pt>(const i64_pt* input_span, i64_pt value, uint64_t* __restrict bitmap);
template vec_idx_t euqality_pt_func<i64_pt>(const i64_pt* input_span, i64_pt value, vec_idx_t* __restrict idx_arr);
template void      eq_vector_constant_func<i64_pt>(const i64_pt* input_span, i64_pt value, SelectionDS& selection_ds);
/*--------------------------------------------------------------------------------------------------------------------*\
 * greaterthan
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void ge_tvec_cvec(const PT* __restrict r_vec, const PT* l_vec, SelectionDS& selection_ds) {
	auto& idx_arr           = selection_ds.idx_arr;
	auto& n_selected_values = selection_ds.n_selected_values;

	const auto value = *l_vec;

	for (vec_idx_t value_idx {0}; value_idx < CFG::VEC_SZ; ++value_idx) {
		// naive implemention
		if (r_vec[value_idx] > value) {
			idx_arr[n_selected_values] = value_idx;
			n_selected_values++;
		}
	}
}

template <typename PT>
void ge_tvec_tvec(const PT* __restrict r_vec, const PT* l_vec, SelectionDS& selection_ds) {
	auto& idx_arr = selection_ds.idx_arr;

	auto& n_selected_values = selection_ds.n_selected_values;
	for (vec_idx_t value_idx {0}; value_idx < CFG::VEC_SZ; ++value_idx) {
		// naive implemention
		if (r_vec[value_idx] > l_vec[value_idx]) {
			idx_arr[n_selected_values] = value_idx;
			n_selected_values++;
		}
	}
}

template void ge_tvec_tvec<i64_pt>(const i64_pt* input_span, const i64_pt* value, SelectionDS& selection_ds);
template void ge_tvec_cvec<i64_pt>(const i64_pt* input_span, const i64_pt* value, SelectionDS& selection_ds);
/*--------------------------------------------------------------------------------------------------------------------*\
 * lessthan
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void lessthan_func(const PT* __restrict array_pointer, PT value, SelectionDS& selection_ds) {
	auto& idx_arr           = selection_ds.idx_arr;
	auto& n_selected_values = selection_ds.n_selected_values;

	for (vec_idx_t value_idx {0}; value_idx < CFG::VEC_SZ; ++value_idx) {
		// naive implemention
		if (array_pointer[value_idx] < value) {
			idx_arr[n_selected_values] = value_idx;
			n_selected_values++;
		}
	}
}

template void lessthan_func<i64_pt>(const i64_pt* input_span, i64_pt value, SelectionDS& selection_ds);

/*--------------------------------------------------------------------------------------------------------------------*\
 * and selection ds
\*--------------------------------------------------------------------------------------------------------------------*/
void and_selection_ds_func(const SelectionDS& selection_ds_0,
                           const SelectionDS& selection_ds_1,
                           SelectionDS&       selection_ds_2) {

	size_t i = 0, j = 0, k = 0;
	while (i < selection_ds_0.n_selected_values && j < selection_ds_1.n_selected_values) {
		if (selection_ds_0.idx_arr[i] < selection_ds_1.idx_arr[j]) {
			i++;
		} else if (selection_ds_0.idx_arr[i] > selection_ds_1.idx_arr[j]) {
			j++;
		} else {
			selection_ds_2.idx_arr[k] = (selection_ds_0.idx_arr[i]);
			i++;
			j++;
			k++;
			selection_ds_2.n_selected_values++;
		}
	}
}
}; // namespace fastlanes