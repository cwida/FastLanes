#ifndef FLS_EXPRESSION_PREDICATE_OPERATOR_HPP
#define FLS_EXPRESSION_PREDICATE_OPERATOR_HPP

#include "fls/primitive/predicate/equal.hpp"
#include "fls/table/chunk.hpp"

namespace fastlanes {
struct predicate_eq_vector_constant_i64 {
	explicit predicate_eq_vector_constant_i64(const fls_vec& ds_0, const fls_vec& ds_1, SelectionDS& selection_ds)
	    : selection_ds(selection_ds) {
		bool find_vec {false};
		bool find_val {false};

		// vector
		auto visitor = overloaded {[&](auto&) { FLS_UNREACHABLE(); },
		                           [&](const up<TypedVector<i64_pt>>& typed_vector) {
			                           data     = typed_vector->m_data;
			                           find_vec = true;
		                           },
		                           [&](const up<ConstantVector<i64_pt>>& constant_vector) {
			                           value    = constant_vector->value;
			                           find_val = true;
		                           }};

		visit(visitor, ds_0);
		visit(visitor, ds_1);

		if (!find_vec || !find_val) {
			FLS_UNREACHABLE();
		}
	}

	void execute() {
		eq_vector_constant_func<i64_pt>(data, value, selection_ds);
	}

	const i64_pt* data;
	i64_pt        value;
	SelectionDS&  selection_ds;
};

struct predicate_GT_i64 {
public:
	explicit predicate_GT_i64(const fls_vec& ds_0, const fls_vec& ds_1, SelectionDS& selection_ds)
	    : selection_ds(selection_ds) {
		n_t n_vector {0};
		n_t n_constant {0};

		// vector
		auto visitor = overloaded {[&](auto&) { FLS_UNREACHABLE(); },
		                           [&](const up<TypedVector<i64_pt>>& typed_vector) {
			                           if (n_vector == 0) {
				                           vec_1 = typed_vector->m_data;
			                           } else {
				                           vec_2 = typed_vector->m_data;
			                           }
			                           n_vector++;
		                           },
		                           [&](const up<ConstantVector<i64_pt>>& constant_vector) {
			                           vec_2 = &constant_vector->value;
			                           n_constant++;
		                           }};

		visit(visitor, ds_0);
		visit(visitor, ds_1);

		if (n_vector == 1 && n_constant == 1) {
			primitive = ge_tvec_cvec<i64_pt>;
		} else if (n_vector == 2) {
			primitive = ge_tvec_tvec<i64_pt>;
		} else {
			FLS_UNREACHABLE();
		}
	}

public:
	predicate_GT_i64(const predicate_GT_i64&)            = delete; // non construction-copyable
	predicate_GT_i64& operator=(const predicate_GT_i64&) = delete; // non copyable
public:
	void execute() {
		primitive(vec_1, vec_2, selection_ds);
	}

	predicate_func_p<i64_pt> primitive;
	const i64_pt*            vec_1;
	const i64_pt*            vec_2;
	SelectionDS&             selection_ds;
};

struct predicate_LE_i64 {
public:
	explicit predicate_LE_i64(const fls_vec& ds_0, const fls_vec& ds_1, SelectionDS& selection_ds)
	    : selection_ds(selection_ds) {
		bool find_vec {false};
		bool find_val {false};

		// vector
		auto visitor = overloaded {[&](auto&) { FLS_UNREACHABLE(); },
		                           [&](const up<TypedVector<i64_pt>>& typed_vector) {
			                           data     = typed_vector->m_data;
			                           find_vec = true;
		                           },
		                           [&](const up<ConstantVector<i64_pt>>& constant_vector) {
			                           value    = constant_vector->value;
			                           find_val = true;
		                           }};

		visit(visitor, ds_0);
		visit(visitor, ds_1);

		if (!find_vec || !find_val) {
			FLS_UNREACHABLE();
		}
	}

public:
	predicate_LE_i64(const predicate_LE_i64&)            = delete; // non construction-copyable
	predicate_LE_i64& operator=(const predicate_LE_i64&) = delete; // non copyable
public:
	void execute() {
		lessthan_func<i64_pt>(data, value, selection_ds);
	}

	const i64_pt* data;
	i64_pt        value;
	SelectionDS&  selection_ds;
};

struct predicate_and_selection_ds {
public:
	explicit predicate_and_selection_ds(SelectionDS& selection_ds_0,
	                                    SelectionDS& selection_ds_1,
	                                    SelectionDS& selection_ds_2)
	    : selection_ds_0(selection_ds_0)
	    , selection_ds_1(selection_ds_1)
	    , selection_ds_2(selection_ds_2) {
	}

	predicate_and_selection_ds(const predicate_and_selection_ds&)            = delete; // non construction-copyable
	predicate_and_selection_ds& operator=(const predicate_and_selection_ds&) = delete; // non copyable
public:
	void execute() {
		and_selection_ds_func(selection_ds_0, selection_ds_1, selection_ds_2);
	}

	const SelectionDS& selection_ds_0;
	const SelectionDS& selection_ds_1;
	SelectionDS&       selection_ds_2;
};
} // namespace fastlanes
#endif // FLS_EXPRESSION_PREDICATE_OPERATOR_HPP
