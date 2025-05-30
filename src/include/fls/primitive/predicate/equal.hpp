#ifndef FLS_PRIMITIVE_PREDICATE_EQUAL_HPP
#define FLS_PRIMITIVE_PREDICATE_EQUAL_HPP

#include "fls/expression/data_type.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class SelectionDS;
/*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
void eq_vector_constant_func(const PT* __restrict array_pointer, PT value, SelectionDS& selection_ds);

template <typename PT>
void ge_tvec_tvec(const PT* __restrict array_pointer, const PT* value, SelectionDS& selection_ds);
template <typename PT>
void ge_tvec_cvec(const PT* __restrict array_pointer, const PT* value, SelectionDS& selection_ds);

template <typename PT>
void lessthan_func(const PT* __restrict array_pointer, PT value, SelectionDS& selection_ds);

void and_selection_ds_func(const SelectionDS& selection_ds_1,
                           const SelectionDS& selection_ds_2,
                           SelectionDS&       selection_ds_3);

template <typename PT>
using predicate_func_p = void (*)(const PT* __restrict left_vec,
                                  const PT* __restrict right_vec,
                                  SelectionDS& selection_ds);
} // namespace fastlanes
#endif // FLS_PRIMITIVE_PREDICATE_EQUAL_HPP
