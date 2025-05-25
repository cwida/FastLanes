#ifndef FLS_COR_EXP_EXP_HPP
#define FLS_COR_EXP_EXP_HPP

#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/lyt/page/page_hdr.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class RPN;

/*--------------------------------------------------------------------------------------------------------------------*/
class Exp {
public:
	Exp(ExpT exp_t, var_t var_t); //
	virtual ~Exp()                  = default;
	virtual PageHdr    page_hdr()   = 0; //
	virtual n_t        arw_c()      = 0; //
	virtual const RPN* cmpr_rpn()   = 0; //
	virtual const RPN* decmpr_rpn() = 0; //
public:
	var_t variant; //
	ExpT  exp_t;   //
};

template <typename T>
class TExp : public Exp {
public:
	explicit TExp(ExpT exp_t, var_t variant); //
	~TExp() override = default;               //
public:
	PageHdr page_hdr() override; //
};
} // namespace fastlanes
#endif // FLS_COR_EXP_EXP_HPP
