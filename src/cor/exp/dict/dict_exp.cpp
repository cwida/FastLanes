#include "fls/cor/exp/dict/dict_exp.hpp"

namespace fastlanes {
template <typename T>
dict_exp::Exp<T>::Exp(ExpT exp_t, uint8_t variant)
    : TExp<T>(exp_t, variant) {
}

template <typename T>
const RPN* dict_exp::Exp<T>::cmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &UNCOMPRESSED_CMPR;
	case var_t::FFOR_NO_PATCH:
		return &FFOR_NO_PATCH_CMPR;
	case var_t::FFOR_LL_PATCH:
		return &FFOR_LL_PATCH_CMPR;
	case var_t::FFOR_S_PATCH:
		return &FFOR_S_PATCH_CMPR;
	case var_t::FFOR_B_PATCH:
		return &FFOR_B_PATCH_CMPR;
	case var_t::FFOR_S_PATCH_REC:
		return &FFOR_S_PATCH_REC_CMPR;
	case var_t::DELTA_NO_PATCH:
		return &DELTA_NO_PATCH_CMPR;
	case var_t::DELTA_LL_PATCH:
		return &DELTA_LL_PATCH_CMPR;
	case var_t::DELTA_S_PATCH:
		return &DELTA_S_PATCH_CMPR;
	case var_t::DELTA_B_PATCH:
		return &DELTA_B_PATCH_CMPR;
	case var_t::DELTA_B_PATCH_REC:
		return &DELTA_B_PATCH_REC_CMPR;
	}
}

template <typename T>
n_t dict_exp::Exp<T>::arw_c() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return UNCOMPRESSED_CMPR.des_buf_c;
	case var_t::FFOR_NO_PATCH:
		return FFOR_NO_PATCH_CMPR.des_buf_c;
	case var_t::FFOR_LL_PATCH:
		return FFOR_LL_PATCH_CMPR.des_buf_c;
	case var_t::FFOR_S_PATCH:
		return FFOR_S_PATCH_CMPR.des_buf_c;
	case var_t::FFOR_B_PATCH:
		return FFOR_B_PATCH_CMPR.des_buf_c;
	case var_t::FFOR_S_PATCH_REC:
		return FFOR_S_PATCH_REC_CMPR.des_buf_c;
	case var_t::DELTA_NO_PATCH:
		return DELTA_NO_PATCH_CMPR.des_buf_c;
	case var_t::DELTA_LL_PATCH:
		return DELTA_LL_PATCH_CMPR.des_buf_c;
	case var_t::DELTA_S_PATCH:
		return DELTA_S_PATCH_CMPR.des_buf_c;
	case var_t::DELTA_B_PATCH:
		return DELTA_B_PATCH_CMPR.des_buf_c;
	case var_t::DELTA_B_PATCH_REC:
		return DELTA_B_PATCH_REC_CMPR.des_buf_c;
	}
}

template <typename T>
const RPN* dict_exp::Exp<T>::decmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &UNCOMPRESSED_DECMPR;
	case var_t::FFOR_NO_PATCH:
		return &FFOR_NO_PATCH_DECMPR;
	case var_t::FFOR_LL_PATCH:
		return &FFOR_LL_PATCH_DECMPR;
	case var_t::FFOR_S_PATCH:
		return &FFOR_S_PATCH_DECMPR;
	case var_t::FFOR_B_PATCH:
		return &FFOR_B_PATCH_DECMPR;
	case var_t::FFOR_S_PATCH_REC:
		return &FFOR_S_PATCH_DECMPR;
	case var_t::DELTA_NO_PATCH:
		return &DELTA_NO_PATCH_DECMPR;
	case var_t::DELTA_LL_PATCH:
		return &DELTA_LL_PATCH_DECMPR;
	case var_t::DELTA_S_PATCH:
		return &DELTA_S_PATCH_DECMPR;
	case var_t::DELTA_B_PATCH:
		return &DELTA_B_PATCH_DECMPR;
	case var_t::DELTA_B_PATCH_REC:
		return &DELTA_B_PATCH_DECMPR;
	}
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(dict_exp::Exp)
// CHECK
//{
// template class dict_exp::Exp<parquet::FixedLenByteArray>;
// template class dict_exp::Exp<parquet::Int96>;
// template class dict_exp::Exp<parquet::ByteArray>;
// }
} // namespace fastlanes