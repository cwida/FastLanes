#include "fls/cor/exp/fsst/fsst_exp.hpp"

namespace fastlanes {
template <typename T>
fsst_exp::Exp<T>::Exp(ExpT exp_t, uint8_t variant)
    : TExp<T>(exp_t, variant) {}

template <typename T>
const RPN* fsst_exp::Exp<T>::cmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &FSST_CMPR;
	case var_t::DELTA_NO_PATCH:
		return &WITH_DELTA_NO_PATCH_CMPR;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return nullptr;
}

template <typename T>
n_t fsst_exp::Exp<T>::arw_c() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return FSST_CMPR.des_buf_c;
	case var_t::DELTA_NO_PATCH:
		return WITH_DELTA_NO_PATCH_CMPR.des_buf_c;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return 0;
}

template <typename T>
const RPN* fsst_exp::Exp<T>::decmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &FSST_DECMPR;
	case var_t::DELTA_NO_PATCH:
		return &WITH_DELTA_NO_PATCH_DECMPR;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(fsst_exp::Exp)
// CHECK
// {
// template class fsst_exp::Exp<parquet::FixedLenByteArray>;
// template class fsst_exp::Exp<parquet::Int96>;
// template class fsst_exp::Exp<parquet::ByteArray>;
// }
} // namespace fastlanes