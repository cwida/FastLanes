#include "fls/cor/exp/dict_rle/dict_rle_exp.hpp"
#include "fls/cor/exp/exp.hpp"

namespace fastlanes {
template <typename T>
dict_rle_exp::Exp<T>::Exp(ExpT exp_t, uint8_t variant)
    : fastlanes::TExp<T>(exp_t, variant) {
}

template <typename T>
const RPN* dict_rle_exp::Exp<T>::cmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &UNCOMPRESSED_CMPR;
	case var_t::DELTA_NO_PATCH:
		return &DELTA_NO_PATCH_CMPR;
	case var_t::UNCOMPRESSED_REC:
		return &SIMPLE_REC_CMPR;
	case var_t::DELTA_NO_PATCH_REC:
		return &DELTA_NO_PATCH_CMPR_REC;
	case var_t::DELTA_NO_PATCH_REC2:
		return &DELTA_NO_PATCH_CMPR_REC2;
	default:
		FLS_ABORT("NOT SUPPORTED")
	}

	FLS_ABORT("NOT SUPPORTED")
	return nullptr;
}

template <typename T>
n_t dict_rle_exp::Exp<T>::arw_c() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return UNCOMPRESSED_CMPR.des_buf_c;
	case var_t::DELTA_NO_PATCH:
		return DELTA_NO_PATCH_CMPR.des_buf_c;
	case var_t::UNCOMPRESSED_REC:
		return SIMPLE_REC_CMPR.des_buf_c;
	case var_t::DELTA_NO_PATCH_REC:
		return DELTA_NO_PATCH_CMPR_REC.des_buf_c;
	case var_t::DELTA_NO_PATCH_REC2:
		return DELTA_NO_PATCH_CMPR_REC2.des_buf_c;
	default:
		FLS_ABORT("NOT SUPPORTED")
	}

	FLS_ABORT("NOT SUPPORTED")
	return 0;
}

template <typename T>
const RPN* dict_rle_exp::Exp<T>::decmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &UNCOMPRESSED_DECMPR;
	case var_t::UNCOMPRESSED_REC:
		return &UNCOMPRESSED_DECMPR;
	case var_t::DELTA_NO_PATCH:
		return &DELTA_NO_PATCH_DECMPR;
	case var_t::DELTA_NO_PATCH_REC:
		return &DELTA_NO_PATCH_DECMPR;
	case var_t::DELTA_NO_PATCH_REC2:
		return &DELTA_NO_PATCH_DECMPR;
	default:
		FLS_ABORT("NOT SUPPORTED")
	}
	FLS_ABORT("NOT SUPPORTED")
	return nullptr;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(dict_rle_exp::Exp)
// CHECK
// {
// template class dict_rle_exp::Exp<parquet::FixedLenByteArray>;
// template class dict_rle_exp::Exp<parquet::Int96>;
// template class dict_rle_exp::Exp<parquet::ByteArray>;
// }
} // namespace fastlanes