#include "fls/expression/logical_expression.hpp"
#include "fls/reader/reader.hpp"
#include "fls/reader/segment.hpp"
#include "fls/table/chunk.hpp"
#include "fls/table/rowgroup.hpp"
#include <sstream>

namespace fastlanes {
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * LogicalExpr
// \*--------------------------------------------------------------------------------------------------------------------*/
// LogicalExpr::~LogicalExpr() = default;
//
// void LogicalExpr::to_physical(PhysicalExpr& expr, Scanner& rowgroup) const {}
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * InvalidExp
// \*--------------------------------------------------------------------------------------------------------------------*/
// InvalidExpr::InvalidExpr() = default;
// void InvalidExpr::to_physical(PhysicalExpr& expr, Scanner& rowgroup) const {
// 	//
// 	FLS_UNREACHABLE();
// }
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * Column
// \*--------------------------------------------------------------------------------------------------------------------*/
// ColumnExpr::ColumnExpr(const n_t idx)
//     : m_col_idx(idx) {}
//
// void ColumnExpr::to_physical(PhysicalExpr& expr, Scanner& scanner) const {
// 	//
// 	// const auto& col = scanner.m_rowgroup.internal_rowgroup[m_col_idx];
// 	// expr.operands.emplace_back(col);
// }
//
// string ColumnExpr::to_string() const {
// 	std::stringstream res;
//
// 	res << "Column {";
// 	res << m_col_idx;
// 	res << "} ";
//
// 	return res.str();
// };
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * Value
// \*--------------------------------------------------------------------------------------------------------------------*/
// template <typename PT>
// Value<PT>::Value(const PT& val)
//     : m_value(val) {}
//
// template <typename PT>
// void Value<PT>::to_physical(PhysicalExpr& expr, Scanner& scanner) const {
// 	// init
// 	expr.operands.emplace_back(make_unique<ConstantVector<PT>>(m_value));
// }
//
// template <typename PT>
// string Value<PT>::to_string() const {
// 	std::stringstream res;
//
// 	res << "value {";
// 	res << m_value;
// 	res << "} ";
//
// 	return res.str();
// };
//
// FLS_ALL_CTS(Value);
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * EQ
// \*--------------------------------------------------------------------------------------------------------------------*/
// void EQ::to_physical(PhysicalExpr& expr, Scanner& scanner) const {
// 	m_e1->to_physical(expr, scanner);
// 	m_e2->to_physical(expr, scanner);
//
// 	FLS_ASSERT_TRUE(expr.operands.size() >= 2);
// 	scanner.m_selection_dses.emplace_back(make_unique<SelectionDS>(*this));
//
// 	expr.operators.emplace_back(
// 	    make_unique<predicate_eq_vector_constant_i64>(expr.operands[expr.operands.size() - 1], //
// 	                                                  expr.operands[expr.operands.size() - 2],
// 	                                                  *scanner.m_selection_dses.back()));
// }
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * GT
// \*--------------------------------------------------------------------------------------------------------------------*/
// void GT::to_physical(PhysicalExpr& expr, Scanner& scanner) const {
// 	m_e1->to_physical(expr, scanner);
// 	m_e2->to_physical(expr, scanner);
//
// 	FLS_ASSERT_TRUE(expr.operands.size() >= 2);
// 	scanner.m_selection_dses.emplace_back(make_unique<SelectionDS>(*this));
//
// 	expr.operators.emplace_back(make_unique<predicate_GT_i64>(expr.operands[expr.operands.size() - 2], //
// 	                                                          expr.operands[expr.operands.size() - 1],
// 	                                                          *scanner.m_selection_dses.back()));
// }
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * LT
// \*--------------------------------------------------------------------------------------------------------------------*/
// void LT::to_physical(PhysicalExpr& expr, Scanner& scanner) const {
// 	m_e1->to_physical(expr, scanner);
// 	m_e2->to_physical(expr, scanner);
//
// 	FLS_ASSERT_TRUE(expr.operands.size() >= 2);
// 	scanner.m_selection_dses.emplace_back(make_unique<SelectionDS>(*this));
//
// 	expr.operators.emplace_back(make_unique<predicate_LE_i64>(expr.operands[expr.operands.size() - 1], //
// 	                                                          expr.operands[expr.operands.size() - 2],
// 	                                                          *scanner.m_selection_dses.back()));
// }
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * And
// \*--------------------------------------------------------------------------------------------------------------------*/
// void AND::to_physical(PhysicalExpr& expr, Scanner& scanner) const {
// 	m_e1->to_physical(expr, scanner);
// 	m_e2->to_physical(expr, scanner);
//
// 	scanner.m_selection_dses.emplace_back(make_unique<SelectionDS>(*this));
//
// 	expr.operators.emplace_back(
// 	    make_unique<predicate_and_selection_ds>(*scanner.m_selection_dses[scanner.m_selection_dses.size() - 3], //
//
// 	                                            *scanner.m_selection_dses[scanner.m_selection_dses.size() - 2],
// 	                                            *scanner.m_selection_dses[scanner.m_selection_dses.size() - 1]));
// }
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * HardcodedExpr
// \*--------------------------------------------------------------------------------------------------------------------*/
// string HardcodedExpr::to_string() const { return "Hardcoded"; }
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * EqualityExpr
// \*--------------------------------------------------------------------------------------------------------------------*/
// string EqualityExpr::to_string() const {
// 	std::stringstream res;
//
// 	res << "equality {";
// 	res << col_idx;
// 	res << " , ";
// 	res << main_col_idx;
// 	res << "} ";
//
// 	return res.str();
// }
// EqualityExpr::EqualityExpr(n_t col_idx, n_t main_col_idx)
//     : col_idx(col_idx)
//     , main_col_idx(main_col_idx) {}
//
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * Map1to1
// \*--------------------------------------------------------------------------------------------------------------------*/
// string Dict::to_string() const {
//
// 	std::stringstream res;
// 	res << "Dict { dict_col_idx : ";
// 	res << dict_col_idx;
// 	res << " , codes_col_idx : ";
// 	res << codes_col_idx;
// 	res << "} ";
//
// 	return res.str();
// }
//
// Dict::Dict(n_t col_idx, n_t main_col_idx)
//     : dict_col_idx(col_idx)
//     , codes_col_idx(main_col_idx) {}

} // namespace fastlanes