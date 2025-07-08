#ifndef FLS_WIZARD_WIZARD_HPP
#define FLS_WIZARD_WIZARD_HPP

#include "fls/common/alias.hpp"  // for n_t, up, idx_t, make_unique
#include "fls/common/common.hpp" // for FLS_UNREACHABLE
#include "fls/common/string.hpp"
#include "fls/expression/data_type.hpp" // for DataType, get_physical_type
#include "fls/footer/operator_token_generated.h"
#include "fls/footer/rowgroup_descriptor.hpp" // for ColumnMetadata, RowgroupDescriptor
#include "fls/footer/table_descriptor.hpp"
#include "fls/std/variant.hpp" // for visit
#include "fls/table/rowgroup.hpp"
#include "fls/wizard/wizard_helpers.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Plan;
class RowGroupView;
class RowgroupEncodingResult;
class CorrelationGraph;
class Rowgroup;
struct TableDescriptorT;
/*--------------------------------------------------------------------------------------------------------------------*/
enum class ExpressionChoosingStrategy : uint8_t {
	INVALID                = 0,
	BEST_COMPRESSION_RATIO = 1,
};

template <typename Ctx>
concept WizardContext = requires(Ctx const& c) {
	{ c.IsForcedSchemaPool() } -> std::convertible_to<bool>;
	{ c.IsForcedSchema() } -> std::convertible_to<bool>;
	{ c.GetForcedSchemaPool() } -> std::same_as<const std::vector<OperatorToken>&>;
	{ c.GetForcedSchema() } -> std::same_as<const std::vector<OperatorToken>&>;
	{ c.GetSampleSize() } -> std::convertible_to<n_t>;
};

template <WizardContext Ctx>
class Wizard {
public:
	explicit Wizard(const Ctx& ctx)
	    : m_ctx(ctx) {
	}

public:
	void SpellRowGroup(const rowgroup_pt& rowgroup, RowgroupDescriptorT& footer) {
		RowGroupCheck(rowgroup, footer);
	};

private:
	template <typename PT>
	void TypedDecide(const rowgroup_pt& rowgroup, ColumnDescriptorT& column_descriptor, RowgroupDescriptorT& footer) {

		auto evaluate_expressions = [&](const auto& operator_token_list) {
			for (const auto& expr : operator_token_list) {
				n_t  size = TryExpr(rowgroup, column_descriptor, expr, footer, m_ctx.GetSampleSize());
				auto res  = std::make_unique<ExpressionResultT>();

				res->operator_token = expr;
				res->size           = size;

				column_descriptor.expr_space.push_back(std::move(res));
			}
		};

		if (m_ctx.IsForcedSchemaPool()) {
			evaluate_expressions(m_ctx.GetForcedSchemaPool());
		} else if (IsDictionaryEncodingRequired(column_descriptor)) {
			column_descriptor.encoding_rpn->operator_tokens.clear();
			const n_t index_type = column_descriptor.encoding_rpn->operand_tokens.back();
			column_descriptor.encoding_rpn->operand_tokens.clear();
			evaluate_expressions(get_dict_encoding_pool<PT>(index_type));
		} else if (IsDictionaryChoosingRequired(column_descriptor)) {
			column_descriptor.encoding_rpn->operator_tokens.clear();
			const n_t index_type = column_descriptor.encoding_rpn->operand_tokens.back();
			column_descriptor.encoding_rpn->operand_tokens.pop_back();
			evaluate_expressions(get_dict_pool<PT>(index_type));
		} else {
			const n_t index_type = static_cast<n_t>(FindBestDataTypeForColumn(rowgroup[column_descriptor.idx]));
			evaluate_expressions(get_dict_encoding_pool<PT>(index_type));
			evaluate_expressions(get_pool<PT>());
		}

		auto best_expr = ChooseBestExpr(column_descriptor.expr_space);
		column_descriptor.encoding_rpn->operator_tokens.emplace_back(best_expr);
	}

	void SetSchema(ColumnDescriptors& column_descriptors) {
		auto& forced_schema = m_ctx.GetForcedSchema();
		for (n_t col_idx {0}; col_idx < column_descriptors.size(); ++col_idx) {
			auto& column_descriptor = column_descriptors[col_idx];
			column_descriptor->encoding_rpn->operator_tokens.emplace_back(forced_schema[col_idx]);
		}
	}

	void ExpressionCheckColumn(const rowgroup_pt&   rowgroup,
	                           ColumnDescriptorT&   column_descriptor,
	                           RowgroupDescriptorT& footer) {
		if (IsDetermined(column_descriptor) && !IsDictionaryEncodingRequired(column_descriptor) &&
		    !IsDictionaryChoosingRequired(column_descriptor)) {
			return;
		}

		switch (column_descriptor.data_type) {
		case DataType::INT64: {
			TypedDecide<int64_t>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::INT32: {
			TypedDecide<int32_t>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::INT16: {
			TypedDecide<int16_t>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::UINT8: {
			TypedDecide<uint8_t>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::DOUBLE: {
			TypedDecide<dbl_pt>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::STRUCT: {
			column_descriptor.encoding_rpn->operator_tokens.emplace_back(OperatorToken::EXP_STRUCT);
			auto& struct_col = rowgroup[column_descriptor.idx];
			visit(overloaded {
			          [&](const up<Struct>& struct_cp) {
				          for (auto& child_column_descriptor : column_descriptor.children) {
					          ExpressionCheckColumn(struct_cp->internal_rowgroup, *child_column_descriptor, footer);
				          }
			          },
			          [](auto&) { FLS_UNREACHABLE() },
			      },
			      struct_col);

			break;
		}
		case DataType::FLS_STR: {
			TypedDecide<fls_string_t>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::INT8: {
			TypedDecide<int8_t>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::FLOAT: {
			TypedDecide<flt_pt>(rowgroup, column_descriptor, footer);
			break;
		}
		case DataType::STR:
		case DataType::INVALID:
		default:
			FLS_UNREACHABLE()
		}
	}

	void ExpressionCheck(const rowgroup_pt& rowgroup, RowgroupDescriptorT& footer) {
		auto& column_descriptors = footer.m_column_descriptors;

		for (n_t col_idx {0}; col_idx < rowgroup.size(); col_idx++) {
			auto& column_descriptor = column_descriptors[col_idx];
			ExpressionCheckColumn(rowgroup, *column_descriptor, footer);
		}
	}

	void RowGroupCheck(const rowgroup_pt& rowgroup, RowgroupDescriptorT& footer) {
		auto& column_descriptors = footer.m_column_descriptors;

		if (m_ctx.IsForcedSchema()) {
			SetSchema(column_descriptors);
			return;
		}

		if (m_ctx.IsForcedSchemaPool()) {
			ExpressionCheck(rowgroup, footer);
			return;
		}

		init(column_descriptors);
		gather_statistics(rowgroup, column_descriptors);
		constant_check(rowgroup, column_descriptors);
		equality_check(rowgroup, column_descriptors);
		null_check(rowgroup, column_descriptors);
		map_1t1_check(rowgroup, column_descriptors);
		ExpressionCheck(rowgroup, footer); // all left over columns are expression encoded.
	}

private:
	const Ctx& m_ctx;
};
} // namespace fastlanes

#endif // FLS_WIZARD_WIZARD_HPP
