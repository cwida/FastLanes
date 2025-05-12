#ifndef FLS_EXPRESSION_NEW_RPN_HPP
#define FLS_EXPRESSION_NEW_RPN_HPP

#include "fls/footer/operator_token_generated.h"
#include "fls/footer/rpn_generated.h"
#include "fls/std/string.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct InterpreterState;
/*--------------------------------------------------------------------------------------------------------------------*/
std::ostream& operator<<(std::ostream& os, const RPNT& rpn);

/*--------------------------------------------------------------------------------------------------------------------*/
/* Helper Functions */
/*--------------------------------------------------------------------------------------------------------------------*/
string token_to_string(OperatorToken token);
bool   is_1_to_1(OperatorToken token);

} // namespace fastlanes

#endif // FLS_EXPRESSION_NEW_RPN_HPP
