#ifndef FLS_EXPRESSION_NEW_RPN_HPP
#define FLS_EXPRESSION_NEW_RPN_HPP

#include "fls/expression/data_type.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * OperatorType
\*--------------------------------------------------------------------------------------------------------------------*/
enum class OperatorType : uint16_t {
	COLUMN   = 0,
	VARIABLE = 1,
	// encoding
	ZERO_COPY       = 2,
	CAST            = 3,
	SUB_EXPRESSION  = 4,
	DICT            = 5,
	DICT_EXPRESSION = 6,
	UNCOMPRESSED    = 7,
	SEGMENT         = 8,
	FFOR            = 9,
	ALP_RD          = 10,
	TRANSPOSE       = 11,
	FIXME           = 12,
	EQUAL           = 13,
	CONSTANT        = 14,
	// encoding
	VECTORIZED_STORE = 15,
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * Operator
\*--------------------------------------------------------------------------------------------------------------------*/
struct Operator {
	Operator(OperatorType operator_type, const DataType data_type)
	    : operator_type(operator_type)
	    , data_type(data_type) {}
	OperatorType operator_type;
	DataType     data_type;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * Operand
\*--------------------------------------------------------------------------------------------------------------------*/
struct Operand {
	explicit Operand(uint16_t col_idx)
	    : col_idx(col_idx) {}
	uint16_t col_idx;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * RPN
\*--------------------------------------------------------------------------------------------------------------------*/
class NewRPN {
public:
	vector<Operator> operators;
	vector<Operand>  operands;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_NEW_RPN_HPP
