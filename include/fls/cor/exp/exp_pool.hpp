#ifndef FLS_COR_EXP_EXP_POOL_HPP
#define FLS_COR_EXP_EXP_POOL_HPP

#include "fls/common/alias.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include <cstdint> // for uint32_t, uint8_t
#include <ostream>
#include <unordered_map>
#include <vector> // for vector

namespace fastlanes {
/**/
class Expression {
public:
	Expression();
	Expression(uint8_t var, ExpT exp);

public:
	uint8_t var;
	ExpT    exp;

public:
	friend std::ostream& operator<<(std::ostream& stream, const Expression& expression_hdr);
};

inline Expression INVALID_EXPRESSION() {
	static Expression INVALID_EXPRESSION_STATIC = {0, ExpT::INVALID};
	return INVALID_EXPRESSION_STATIC;
}

using scheme_pool_t = std::unordered_map<n_t, Expression>;

template <typename PT>
class ExpPool {
public:
	static scheme_pool_t get_pool();
	static scheme_pool_t get_dict_pool();
	///
	static Expression get_expression(n_t expression_id);
};

} // namespace fastlanes

#endif // FLS_COR_EXP_EXP_POOL_HPP
