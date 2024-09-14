#ifndef FLS_EXPRESSION_INTERPRETER_HPP
#define FLS_EXPRESSION_INTERPRETER_HPP

#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class PhysicalExpr;
class NewRPN;
class Rowgroup;
class Buf;
class HorizontalColumn;
/*--------------------------------------------------------------------------------------------------------------------*/
class Interpreter {
public:
	struct State {
		n_t cur_opr {0};
	};
	class Encoding {
	public:
		static up<PhysicalExpr> Interpret(const NewRPN& rpn, const Rowgroup& rowgroup);
	};
	class Decoding {
	public:
		static void Interpret(const NewRPN& new_rpn, PhysicalExpr& expr, State state);
	};
};
} // namespace fastlanes

#endif // FLS_EXPRESSION_INTERPRETER_HPP
