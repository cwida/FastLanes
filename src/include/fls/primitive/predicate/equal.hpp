// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/primitive/predicate/equal.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_PRIMITIVE_PREDICATE_EQUAL_HPP
#define FLS_PRIMITIVE_PREDICATE_EQUAL_HPP

#include "fls/common/restrict.hpp"
#include "fls/expression/data_type.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class SelectionDS;
/*--------------------------------------------------------------------------------------------------------------------*/

// MSVC strips __restrict from explicit template instantiation mangling,
// so declarations must omit it. Clang-cl needs it to match definitions.
#if defined(_MSC_VER) && !defined(__clang__)
#define FLS_PREDICATE_RESTRICT
#else
#define FLS_PREDICATE_RESTRICT FLS_RESTRICT
#endif

template <typename PT>
void eq_vector_constant_func(const PT* FLS_PREDICATE_RESTRICT array_pointer, PT value, SelectionDS& selection_ds);

template <typename PT>
void ge_tvec_tvec(const PT* FLS_PREDICATE_RESTRICT array_pointer, const PT* value, SelectionDS& selection_ds);
template <typename PT>
void ge_tvec_cvec(const PT* FLS_PREDICATE_RESTRICT array_pointer, const PT* value, SelectionDS& selection_ds);

template <typename PT>
void lessthan_func(const PT* FLS_PREDICATE_RESTRICT array_pointer, PT value, SelectionDS& selection_ds);

void and_selection_ds_func(const SelectionDS& selection_ds_1,
                           const SelectionDS& selection_ds_2,
                           SelectionDS&       selection_ds_3);

template <typename PT>
using predicate_func_p = void (*)(const PT* FLS_PREDICATE_RESTRICT left_vec,
                                  const PT* FLS_PREDICATE_RESTRICT right_vec,
                                  SelectionDS&                     selection_ds);
} // namespace fastlanes
#endif // FLS_PRIMITIVE_PREDICATE_EQUAL_HPP
