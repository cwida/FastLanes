#include "fls/cor/exp/ffor/ffor_exp.hpp"
#include "fls/cor/exp/exp.hpp"

namespace fastlanes {
template <typename T>
ffor_exp::Exp<T>::Exp(ExpT exp_t, uint8_t variant)
    : fastlanes::TExp<T>(exp_t, variant) {
}

template <typename T>
const RPN* ffor_exp::Exp<T>::cmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::S_PATCH:
		return &S_PATCH_CMPR;
	case var_t::B_PATCH:
		return &B_PATCH_CMPR;
	case var_t::LL_PATCH:
		return &LL_PATCH_CMPR;
	case var_t::NO_PATCH:
		return &NO_PATCH_CMPR;
	case var_t::S_PATCH_REC:
		return &S_PATCH_REC_CMPR;
	}
}

template <typename T>
n_t ffor_exp::Exp<T>::arw_c() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::S_PATCH:
		return S_PATCH_CMPR.des_buf_c;
	case var_t::B_PATCH:
		return B_PATCH_CMPR.des_buf_c;
	case var_t::LL_PATCH:
		return LL_PATCH_CMPR.des_buf_c;
	case var_t::NO_PATCH:
		return NO_PATCH_CMPR.des_buf_c;
	case var_t::S_PATCH_REC:
		return S_PATCH_REC_CMPR.des_buf_c;
	}
}

template <typename T>
const RPN* ffor_exp::Exp<T>::decmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::S_PATCH:
		return &S_PATCH_DECMPR;
	case var_t::B_PATCH:
		return &B_PATCH_DECMPR;
	case var_t::LL_PATCH:
		return &LL_PATCH_DECMPR;
	case var_t::NO_PATCH:
		return &NO_PATCH_DECMPR;
	case var_t::S_PATCH_REC:
		return &S_PATCH_DECMPR;
	}
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(ffor_exp::Exp)
// CHECK
// {
// template class ffor_exp::Exp<parquet::FixedLenByteArray>;
// template class ffor_exp::Exp<parquet::Int96>;
// template class ffor_exp::Exp<parquet::ByteArray>;
// }
} // namespace fastlanes