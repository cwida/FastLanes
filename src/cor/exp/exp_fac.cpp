#include "fls/cor/exp/exp_fac.hpp"
#include "fls/api/exp.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/exp/exp_type.hpp"

namespace fastlanes {
template <typename PT>
sp<TExp<PT>> ExpFac<PT>::Create(ExpT& exp_t, uint8_t m_var_t) {
	switch (exp_t) {
	case ExpT::UNCOMPRESSED: {
		static uncompressed_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<uncompressed_exp::Exp<PT>>(EXP);
	}
	case ExpT::BYTE_ARR: {
		static byte_arr::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<byte_arr::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::FFOR: {
		static ffor_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<ffor_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::DELTA: {
		static delta_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<delta_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::RLE: {
		static rle_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<rle_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::DICT_RLE: {
		static dict_rle_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<dict_rle_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::DICT:
	case ExpT::DICT_FRQ:
	case ExpT::DICT_VAL: {
		static dict_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<dict_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::FSST: {
		static fsst_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<fsst_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::FSST12: {
		static fsst12_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<fsst12_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::ALP: {
		static alp_exp::Exp<PT> EXP(exp_t, m_var_t);
		return std::make_unique<alp_exp::Exp<PT>>(exp_t, m_var_t);
	}
	case ExpT::INVALID:
	case ExpT::UNDECIDED:
	default:
		FLS_ABORT("NOT SUPPORTED")
	}

	FLS_ABORT("NOT SUPPORTED")
	return nullptr;
}

template <typename PT>
sp<TExp<PT>> ExpFac<PT>::Create(AnalyzeState& analyze_state) {
	return ExpFac<PT>::Create(analyze_state.m_exp_t, analyze_state.m_var_t);
}

template <typename PT>
sp<TExp<PT>> ExpFac<PT>::Create(PageHdr pg_hdr) {
	return ExpFac<PT>::Create(pg_hdr.exp_t, pg_hdr.m_var_t);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(ExpFac)
} // namespace fastlanes