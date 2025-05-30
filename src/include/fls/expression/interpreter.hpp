#ifndef FLS_EXPRESSION_INTERPRETER_HPP
#define FLS_EXPRESSION_INTERPRETER_HPP

#include "fls/std/vector.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class PhysicalExpr;
struct RPNT;
class Buf;
class ColumnView;
struct ColumnDescriptorT;
class RowgroupReader;
/*--------------------------------------------------------------------------------------------------------------------*/

struct InterpreterState {
	explicit InterpreterState();

	//
	n_t cur_operator;
	n_t cur_operand;
	n_t n_segments;
};

class Interpreter {
public:
	class Encoding {
	public:
		static sp<PhysicalExpr>
		Interpret(ColumnDescriptorT& column_descriptor, const rowgroup_pt& physical_rowgroup, InterpreterState& state);
	};
	class Decoding {
	public:
		static void Interpret(const ColumnDescriptorT& column_descriptor,
		                      const ColumnView&        column_view,
		                      PhysicalExpr&            physical_expr,
		                      InterpreterState&        state,
		                      RowgroupReader&          reader);
	};
};

sp<PhysicalExpr> make_decoding_expression(const ColumnDescriptorT& column_descriptor,
                                          const ColumnView&        column_view,
                                          RowgroupReader&          reader,
                                          InterpreterState&        state);
} // namespace fastlanes

#endif // FLS_EXPRESSION_INTERPRETER_HPP
