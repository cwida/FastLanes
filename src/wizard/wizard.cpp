#include "fls/wizard/wizard.hpp"
#include "fls/common/alias.hpp"             // for n_t, up, idx_t, make_unique
#include "fls/common/common.hpp"            // for FLS_UNREACHABLE
#include "fls/connection.hpp"               // for Connector
#include "fls/encoder/exp_col_encoder.hpp"  // for AllExpEncodedCol, ExpEnc...
#include "fls/encoder/rowgroup_encoder.hpp" // for RowgroupEncodingResult
#include "fls/expression/data_type.hpp"     // for DataType, get_physical_type
#include "fls/expression/new_rpn.hpp"       // for Operator, Operand, NewRPN
#include "fls/footer/rowgroup_footer.hpp"   // for ColumnMetadata, Footer
#include "fls/std/variant.hpp"              // for visit
#include "fls/std/vector.hpp"               // for vector
#include "fls/table/rowgroup.hpp"           // for Rowgroup, TypedCol (ptr ...
#include <memory>                           // for unique_ptr, make_unique
#include <stdexcept>                        // for runtime_error
#include <variant>                          // for visit, monostate, variant

namespace fastlanes {

up<Footer> Wizard::Spell(const Connection& fls) {

	/*
	 * 1) c3
	 * 2) encode data choose best exp
	 * 3) ...
	 */
	const auto& rowgroup = fls.rowgroup();

	auto footer = make_unique<Footer>(fls.rowgroup());

	// check constant columns.
	constant_check(rowgroup, *footer);

	// c3
	equality_check(rowgroup, *footer);
	map_1t1_check(rowgroup, *footer);
	expression_check(rowgroup, *footer); // all left over columns are expression encoded.

	// TODO[SAMPLE]
	// const RowgroupEncoder tab_encoder(TEMPORARY, WITHOUT_VERIFICATION);
	// auto                  tab_compression_result = tab_encoder.Encode(fls);
	// ChooseExpr(ExpressionChoosingStrategy::BEST_COMPRESSION_RATIO, tab_compression_result, *footer);

	return footer;
}

void Wizard::ChooseExpr(ExpressionChoosingStrategy strategy, RowgroupEncodingResult& result, Footer& plan) {
	switch (strategy) {
	case ExpressionChoosingStrategy::BEST_COMPRESSION_RATIO: {

		auto& col_res_vec = result.col_result_vec;
		for (idx_t i {0}; i < col_res_vec.size(); ++i) {
			// auto& col_res = col_res_vec[i];
			//
			// // only when there is result
			// if (col_res.exp_result_vec.empty()) { continue; }
			//
			// [[maybe_unused]] auto best_exp_res = col_res.GetBest();
			// plan[i].expression = best_exp_res.expression;
		}
	} break;
	case ExpressionChoosingStrategy::INVALID:
	default: {
		throw std::runtime_error("INVALID EXPRESSION!");
	}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
struct constant_visitor {
	ColumnMetadata& sub_plan;

	void operator()(std::monostate&) { FLS_UNREACHABLE(); }
	template <typename PT>
	void operator()(const up<TypedCol<PT>>& typed_col) {
		if (typed_col->m_stats.is_constant) {
			sub_plan.encoding_rpn.operators.emplace_back(OperatorType::CONSTANT, get_physical_type<PT>());
			sub_plan.m_is_determined = true;
		}
	}
	void operator()(auto&) { FLS_UNREACHABLE(); }
};

void constant_visit(const col_pt& col, ColumnMetadata& sub_plan) {
	//
	visit(constant_visitor {sub_plan}, col);
}

void Wizard::constant_check(const Rowgroup& rowgroup, Footer& footer) {
	for (n_t col_idx {0}; col_idx < rowgroup.internal_rowgroup.size(); col_idx++) {
		constant_visit(rowgroup.internal_rowgroup[col_idx], footer.column_metadatas[col_idx]);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Wizard::equality_check(const Rowgroup& rowgroup, Footer& compression_plan) {
	const auto n_col = rowgroup.internal_rowgroup.size();

	// brute_force
	for (n_t first_col_idx {0}; first_col_idx < n_col; first_col_idx++) {
		for (n_t second_col_idx {first_col_idx + 1}; second_col_idx < n_col; second_col_idx++) {
			auto& col_mtd = compression_plan[second_col_idx];
			if (col_mtd.IsDetermined()) { continue; }

			if (const auto is_equal = rowgroup.Equal(first_col_idx, second_col_idx); is_equal) {
				col_mtd.encoding_rpn.operators.emplace_back(OperatorType::EQUAL, col_mtd.data_type);
				col_mtd.m_is_determined = true;
			}
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Wizard::expression_check(const Rowgroup& rowgroup, Footer& footer) {
	for (n_t col_idx {0}; col_idx < rowgroup.internal_rowgroup.size(); col_idx++) {

		if (auto& column_metadata = footer[col_idx]; !column_metadata.IsDetermined()) {
			column_metadata.encoding_rpn.operators.emplace_back(OperatorType::ZERO_COPY, column_metadata.data_type);
			column_metadata.encoding_rpn.operands.emplace_back(col_idx);
			column_metadata.m_is_determined = true;
		}
	}
}

/*--------------------------------------------------------------------------------------------------------------------*/
void Wizard::map_1t1_check(const Rowgroup& rowgroup, Footer& compression_plan) {
	const auto n_col = rowgroup.internal_rowgroup.size();

	// brute_force
	for (n_t first_col_idx {0}; first_col_idx < n_col; first_col_idx++) {
		auto& first_subplan = compression_plan[first_col_idx];
		if (first_subplan.IsDetermined()) { continue; }

		for (n_t second_col_idx {first_col_idx + 1}; second_col_idx < n_col; second_col_idx++) {
			auto& second_subplan = compression_plan[second_col_idx];
			if (second_subplan.IsDetermined()) { continue; }
			if (!rowgroup.is_good_for_ditionary_encoding(first_col_idx)) { continue; }

			if (const auto is_map_1t1 = rowgroup.IsMap1t1(first_col_idx, second_col_idx); is_map_1t1) {
				first_subplan.encoding_rpn.operators.emplace_back(OperatorType::DICT,
				                                                  first_subplan.data_type); // todo
				first_subplan.encoding_rpn.operators.emplace_back(OperatorType::SUB_EXPRESSION, DataType::UINT16);
				first_subplan.m_is_determined = true;

				second_subplan.encoding_rpn.operators.emplace_back(OperatorType::FIXME, second_subplan.data_type);
				second_subplan.m_is_determined = true;
			}
		}
	}
}

} // namespace fastlanes
