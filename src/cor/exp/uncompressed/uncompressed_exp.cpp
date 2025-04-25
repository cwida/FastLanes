#include "fls/cor/exp/uncompressed/uncompressed_exp.hpp"

namespace fastlanes {
template <typename T>
uncompressed_exp::Exp<T>::Exp(ExpT exp_t, uint8_t variant)
    : TExp<T>(exp_t, variant) {
}

template <typename T>
const RPN* uncompressed_exp::Exp<T>::cmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &UNCOMPRESSED_CMPR;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return nullptr;
}

template <typename T>
n_t uncompressed_exp::Exp<T>::arw_c() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return UNCOMPRESSED_CMPR.des_buf_c;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return 0;
}

template <typename T>
const RPN* uncompressed_exp::Exp<T>::decmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &UNCOMPRESSED_DCMPR;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(uncompressed_exp::Exp)
} // namespace fastlanes