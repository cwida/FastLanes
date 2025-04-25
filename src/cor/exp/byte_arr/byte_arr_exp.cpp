#include "fls/cor/exp/byte_arr/byte_arr_exp.hpp"

namespace fastlanes {
template <typename T>
byte_arr::Exp<T>::Exp(ExpT exp_t, uint8_t variant)
    : fastlanes::TExp<T>(exp_t, variant) {
}

template <typename T>
const RPN* byte_arr::Exp<T>::cmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &STR_CMPR;
	case var_t::DELTA_NO_PATCH:
		return &WITH_DELTA_NO_PATCH_CMPR;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return nullptr;
}

template <typename T>
n_t byte_arr::Exp<T>::arw_c() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return STR_CMPR.des_buf_c;
	case var_t::DELTA_NO_PATCH:
		return WITH_DELTA_NO_PATCH_CMPR.des_buf_c;
	default:
		FLS_ABORT("NOT SUPPORTED!")
	}

	return 0;
}

template <typename T>
const RPN* byte_arr::Exp<T>::decmpr_rpn() {
	switch (static_cast<var_t>(this->variant)) {
	case var_t::UNCOMPRESSED:
		return &STR_DECMPR;
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
FLS_ALL_CTS(byte_arr::Exp)
// CHECK
// {
// template class byte_arr::Exp<parquet::FixedLenByteArray>;
// template class byte_arr::Exp<parquet::Int96>;
// template class byte_arr::Exp<parquet::ByteArray>;
// }
} // namespace fastlanes