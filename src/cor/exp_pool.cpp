#include "fls/cor/exp/exp_pool.hpp"
#include "fls/api/exp.hpp"
#include "fls/printer/to_str.hpp"
#include <ostream>

namespace fastlanes {

std::ostream& operator<<(std::ostream& stream, const Expression& expression_hdr) {
	stream << ""
	       << "," << ToStr::to_str(expression_hdr.exp) << "," << ToStr::to_str(expression_hdr.var, expression_hdr.exp);

	return stream;
}
Expression::Expression()
    : var(0)
    , exp(ExpT::INVALID) {}

Expression::Expression(const uint8_t var, const ExpT exp)
    : var(var)
    , exp(exp) {}

template <typename PT>
scheme_pool_t ExpPool<PT>::get_pool() {
	if constexpr (std::is_same_v<PT, i64_pt>) {
		scheme_pool_t pool;
		pool.emplace(0, Expression {static_cast<uint8_t>(uncompressed_exp::var_t::UNCOMPRESSED), ExpT::UNCOMPRESSED});
		pool.emplace(1, Expression {static_cast<uint8_t>(ffor_exp::var_t::NO_PATCH), ExpT::FFOR});
		pool.emplace(2, Expression {static_cast<uint8_t>(ffor_exp::var_t::S_PATCH), ExpT::FFOR});
		pool.emplace(3, Expression {static_cast<uint8_t>(ffor_exp::var_t::S_PATCH_REC), ExpT::FFOR});
		pool.emplace(4, Expression {static_cast<uint8_t>(ffor_exp::var_t::B_PATCH), ExpT::FFOR});
		pool.emplace(5, Expression {static_cast<uint8_t>(ffor_exp::var_t::LL_PATCH), ExpT::FFOR});
		pool.emplace(6, Expression {static_cast<uint8_t>(rle_exp::var_t::DELTA_NO_PATCH), ExpT::RLE});
		pool.emplace(7, Expression {static_cast<uint8_t>(rle_exp::var_t::UNCOMPRESSED), ExpT::RLE});
		pool.emplace(8, Expression {static_cast<uint8_t>(rle_exp::var_t::UNCOMPRESSED_REC), ExpT::RLE});
		pool.emplace(9, Expression {static_cast<uint8_t>(rle_exp::var_t::DELTA_NO_PATCH_REC), ExpT::RLE});
		pool.emplace(10, Expression {static_cast<uint8_t>(rle_exp::var_t::DELTA_NO_PATCH_REC2), ExpT::RLE});
		pool.emplace(11, Expression {static_cast<uint8_t>(delta_exp::var_t::NO_PATCH), ExpT::DELTA});
		pool.emplace(12, Expression {static_cast<uint8_t>(delta_exp::var_t::S_PATCH), ExpT::DELTA});
		pool.emplace(13, Expression {static_cast<uint8_t>(delta_exp::var_t::B_PATCH), ExpT::DELTA});
		pool.emplace(14, Expression {static_cast<uint8_t>(delta_exp::var_t::LL_PATCH), ExpT::DELTA});
		pool.emplace(15, Expression {static_cast<uint8_t>(delta_exp::var_t::B_PATCH_REC), ExpT::DELTA});
		pool.emplace(16, Expression {static_cast<uint8_t>(dict_exp::var_t::UNCOMPRESSED), ExpT::DICT});
		pool.emplace(17, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_NO_PATCH), ExpT::DICT});
		pool.emplace(18, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_B_PATCH), ExpT::DICT});
		pool.emplace(19, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH), ExpT::DICT});
		pool.emplace(20, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_LL_PATCH), ExpT::DICT});
		pool.emplace(21, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT});
		pool.emplace(22, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_NO_PATCH), ExpT::DICT});
		pool.emplace(23, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_S_PATCH), ExpT::DICT});
		pool.emplace(24, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_LL_PATCH), ExpT::DICT});
		pool.emplace(25, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH), ExpT::DICT});
		pool.emplace(26, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT});
		pool.emplace(27, Expression {static_cast<uint8_t>(dict_rle_exp::var_t::DELTA_NO_PATCH_REC), ExpT::DICT_RLE});
		pool.emplace(28, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::UNCOMPRESSED), ExpT::DICT_FRQ});
		pool.emplace(29, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(30, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(31, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(32, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(33, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT_FRQ});
		pool.emplace(34, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(35, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(36, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(37, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(38, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT_FRQ});
		return pool;
	}
	/**/
	else if constexpr (std::is_same_v<PT, str_pt>) {
		scheme_pool_t pool;

		pool.emplace(0, Expression {static_cast<uint8_t>(byte_arr::var_t::UNCOMPRESSED), ExpT::BYTE_ARR});
		pool.emplace(1, Expression {static_cast<uint8_t>(byte_arr::var_t::DELTA_NO_PATCH), ExpT::BYTE_ARR});
		pool.emplace(2, Expression {static_cast<uint8_t>(dict_exp::var_t::UNCOMPRESSED), ExpT::DICT});
		pool.emplace(3, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_NO_PATCH), ExpT::DICT});
		pool.emplace(4, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_LL_PATCH), ExpT::DICT});
		pool.emplace(5, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH), ExpT::DICT});
		pool.emplace(6, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_B_PATCH), ExpT::DICT});
		pool.emplace(7, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT});
		pool.emplace(8, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_NO_PATCH), ExpT::DICT});
		pool.emplace(9, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_LL_PATCH), ExpT::DICT});
		pool.emplace(10, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_S_PATCH), ExpT::DICT});
		pool.emplace(11, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH), ExpT::DICT});
		pool.emplace(12, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT});
		pool.emplace(13, Expression {static_cast<uint8_t>(fsst_exp::var_t::UNCOMPRESSED), ExpT::FSST});
		pool.emplace(14, Expression {static_cast<uint8_t>(fsst_exp::var_t::DELTA_NO_PATCH), ExpT::FSST});
		pool.emplace(15, Expression {static_cast<uint8_t>(dict_rle_exp::var_t::UNCOMPRESSED), ExpT::DICT_RLE});
		pool.emplace(16, Expression {static_cast<uint8_t>(dict_rle_exp::var_t::DELTA_NO_PATCH), ExpT::DICT_RLE});
		pool.emplace(17, Expression {static_cast<uint8_t>(dict_exp::var_t::UNCOMPRESSED), ExpT::DICT_FRQ});
		pool.emplace(18, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(19, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(20, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(21, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(22, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT_FRQ});
		pool.emplace(23, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(24, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(25, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(26, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(27, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT_FRQ});
		pool.emplace(28, Expression {static_cast<uint8_t>(fsst12_exp::var_t::UNCOMPRESSED), ExpT::FSST12});
		pool.emplace(29, Expression {static_cast<uint8_t>(fsst12_exp::var_t::DELTA_NO_PATCH), ExpT::FSST12});

		return pool;
	}
	/**/
	if constexpr (std::is_same_v<PT, dbl_pt>) {
		scheme_pool_t pool;
		pool.emplace(0, Expression {static_cast<uint8_t>(uncompressed_exp::var_t::UNCOMPRESSED), ExpT::UNCOMPRESSED});
		pool.emplace(1, Expression {static_cast<uint8_t>(alp_exp::var_t::ALP), ExpT::ALP});
		pool.emplace(6, Expression {static_cast<uint8_t>(rle_exp::var_t::DELTA_NO_PATCH), ExpT::RLE});
		pool.emplace(7, Expression {static_cast<uint8_t>(rle_exp::var_t::UNCOMPRESSED), ExpT::RLE});
		pool.emplace(8, Expression {static_cast<uint8_t>(rle_exp::var_t::UNCOMPRESSED_REC), ExpT::RLE});
		pool.emplace(9, Expression {static_cast<uint8_t>(rle_exp::var_t::DELTA_NO_PATCH_REC), ExpT::RLE});
		pool.emplace(10, Expression {static_cast<uint8_t>(rle_exp::var_t::DELTA_NO_PATCH_REC2), ExpT::RLE});
		pool.emplace(16, Expression {static_cast<uint8_t>(dict_exp::var_t::UNCOMPRESSED), ExpT::DICT});
		pool.emplace(17, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_NO_PATCH), ExpT::DICT});
		pool.emplace(18, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_B_PATCH), ExpT::DICT});
		pool.emplace(19, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH), ExpT::DICT});
		pool.emplace(20, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_LL_PATCH), ExpT::DICT});
		pool.emplace(21, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT});
		pool.emplace(22, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_NO_PATCH), ExpT::DICT});
		pool.emplace(23, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_S_PATCH), ExpT::DICT});
		pool.emplace(24, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_LL_PATCH), ExpT::DICT});
		pool.emplace(25, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH), ExpT::DICT});
		pool.emplace(26, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT});
		pool.emplace(27, Expression {static_cast<uint8_t>(dict_rle_exp::var_t::DELTA_NO_PATCH_REC), ExpT::DICT_RLE});
		pool.emplace(28, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::UNCOMPRESSED), ExpT::DICT_FRQ});
		pool.emplace(29, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(30, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(31, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(32, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(33, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT_FRQ});
		pool.emplace(34, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(35, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(36, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(37, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(38, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT_FRQ});

		return pool;
	}
	/**/
	else {
		FLS_UNREACHABLE()
	}
}

template <typename PT>
scheme_pool_t ExpPool<PT>::get_dict_pool() {
	if constexpr (std::is_same_v<PT, i64_pt>) {
		scheme_pool_t pool;
		pool.emplace(16, Expression {static_cast<uint8_t>(dict_exp::var_t::UNCOMPRESSED), ExpT::DICT});
		pool.emplace(17, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_NO_PATCH), ExpT::DICT});
		pool.emplace(18, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_B_PATCH), ExpT::DICT});
		pool.emplace(19, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH), ExpT::DICT});
		pool.emplace(20, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_LL_PATCH), ExpT::DICT});
		pool.emplace(21, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT});
		pool.emplace(22, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_NO_PATCH), ExpT::DICT});
		pool.emplace(23, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_S_PATCH), ExpT::DICT});
		pool.emplace(24, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_LL_PATCH), ExpT::DICT});
		pool.emplace(25, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH), ExpT::DICT});
		pool.emplace(26, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT});
		return pool;
	}
	/**/
	else if constexpr (std::is_same_v<PT, str_pt>) {
		scheme_pool_t pool;
		pool.emplace(2, Expression {static_cast<uint8_t>(dict_exp::var_t::UNCOMPRESSED), ExpT::DICT});
		pool.emplace(3, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_NO_PATCH), ExpT::DICT});
		pool.emplace(4, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_LL_PATCH), ExpT::DICT});
		pool.emplace(5, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH), ExpT::DICT});
		pool.emplace(6, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_B_PATCH), ExpT::DICT});
		pool.emplace(7, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT});
		pool.emplace(8, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_NO_PATCH), ExpT::DICT});
		pool.emplace(9, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_LL_PATCH), ExpT::DICT});
		pool.emplace(10, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_S_PATCH), ExpT::DICT});
		pool.emplace(11, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH), ExpT::DICT});
		pool.emplace(12, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT});

		return pool;
	} else if constexpr (std::is_same_v<PT, dbl_pt>) {
		scheme_pool_t pool;

		pool.emplace(16, Expression {static_cast<uint8_t>(dict_exp::var_t::UNCOMPRESSED), ExpT::DICT});
		pool.emplace(17, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_NO_PATCH), ExpT::DICT});
		pool.emplace(18, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_B_PATCH), ExpT::DICT});
		pool.emplace(19, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH), ExpT::DICT});
		pool.emplace(20, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_LL_PATCH), ExpT::DICT});
		pool.emplace(21, Expression {static_cast<uint8_t>(dict_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT});
		pool.emplace(22, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_NO_PATCH), ExpT::DICT});
		pool.emplace(23, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_S_PATCH), ExpT::DICT});
		pool.emplace(24, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_LL_PATCH), ExpT::DICT});
		pool.emplace(25, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH), ExpT::DICT});
		pool.emplace(26, Expression {static_cast<uint8_t>(dict_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT});
		pool.emplace(27, Expression {static_cast<uint8_t>(dict_rle_exp::var_t::DELTA_NO_PATCH_REC), ExpT::DICT_RLE});
		pool.emplace(28, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::UNCOMPRESSED), ExpT::DICT_FRQ});
		pool.emplace(29, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(30, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(31, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(32, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(33, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::FFOR_S_PATCH_REC), ExpT::DICT_FRQ});
		pool.emplace(34, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_NO_PATCH), ExpT::DICT_FRQ});
		pool.emplace(35, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_S_PATCH), ExpT::DICT_FRQ});
		pool.emplace(36, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_LL_PATCH), ExpT::DICT_FRQ});
		pool.emplace(37, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_B_PATCH), ExpT::DICT_FRQ});
		pool.emplace(38, Expression {static_cast<uint8_t>(dict_frq_exp::var_t::DELTA_B_PATCH_REC), ExpT::DICT_FRQ});
		return pool;
	}
	/**/
	else {
		FLS_ABORT(" NOT SUPPORTED! ")
	}
	return {};
}

template <typename PT>
Expression ExpPool<PT>::get_expression(const n_t expr_id) {
	auto       pool = ExpPool<PT>::get_pool();
	const auto it   = pool.find(expr_id);
	if (it == pool.end()) { throw std::runtime_error("exp does not  exist!"); }
	return it->second;
}

template class ExpPool<i64_pt>;
template class ExpPool<str_pt>;
template class ExpPool<double>;

} // namespace fastlanes