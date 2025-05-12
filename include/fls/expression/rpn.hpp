#ifndef FLS_EXPRESSION_NEW_RPN_HPP
#define FLS_EXPRESSION_NEW_RPN_HPP

#include "fls/footer/operator_token_generated.h"
#include "fls/std/string.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct InterpreterState;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * RPN
\*--------------------------------------------------------------------------------------------------------------------*/
class RPN {
public:
	vector<OperatorToken> operator_tokens;
	vector<n_t>           operand_tokens;
	//
	n_t                  ConsumeOperandToken(InterpreterState& state) const;
	friend std::ostream& operator<<(std::ostream& os, const RPN& rpn);
};

/*--------------------------------------------------------------------------------------------------------------------*/
/* Helper Functions */
/*--------------------------------------------------------------------------------------------------------------------*/
string token_to_string(OperatorToken token);
bool   is_1_to_1(OperatorToken token);

} // namespace fastlanes

#endif // FLS_EXPRESSION_NEW_RPN_HPP
