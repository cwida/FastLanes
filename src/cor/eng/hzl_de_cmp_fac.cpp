#include "fls/cor/eng/hzl_de_cmp_fac.hpp"
#include "fls/api/exp.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/hzl_de_cmp.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/printer/print.hpp"

namespace fastlanes {
template <typename T>
sp<HzlDeCmp> HzlDeCmpFac<T>::Create(ExpT exp_t, uint8_t m_var_t, PageT type) {
	switch (type) {
	case PageT::DICT_PAGE: {
		static auto T_HZL_DE_CMP = std::make_shared<THzlDeCmp<FT>>();
		return T_HZL_DE_CMP;
	}
	case PageT::DATA_PAGE:
		switch (exp_t) {
		case ExpT::DICT:
		case ExpT::DICT_RLE:
		case ExpT::DICT_FRQ:
		case ExpT::DICT_VAL: {
			static auto T_HZL_DE_CMP = std::make_shared<THzlDeCmp<idx_t>>();
			return T_HZL_DE_CMP;
		}
		case ExpT::BYTE_ARR:
		case ExpT::FFOR:
		case ExpT::DELTA:
		case ExpT::UNCOMPRESSED:
		case ExpT::RLE: {
			static auto T_HZL_DE_CMP = std::make_shared<THzlDeCmp<uint64_t>>();
			return T_HZL_DE_CMP;
		}
		case ExpT::FSST: {
			static auto T_HZL_DE_CMP = std::make_shared<THzlDeCmp<FT>>();
			return T_HZL_DE_CMP;
		}
		case ExpT::FSST12: {
			static auto T_HZL_DE_CMP = std::make_shared<THzlDeCmp<FT>>();
			return T_HZL_DE_CMP;
		}
		case ExpT::ALP: {
			static auto T_HZL_DE_CMP = std::make_shared<THzlDeCmp<dbl_pt>>();
			return T_HZL_DE_CMP;
		}
		case ExpT::INVALID:
		case ExpT::UNDECIDED:
			// TODO [FIXME]
		default: {
			FLS_ABORT("NOT SUPPORTED!")
			return nullptr;
		}
		}
	}

	FLS_ABORT("RETURN OVERPASSED!")
	return nullptr;
}

template <typename T>
sp<HzlDeCmp> HzlDeCmpFac<T>::Create(AnalyzeState& analyze_state, PageT type) {
	return HzlDeCmpFac<T>::Create(analyze_state.m_exp_t, analyze_state.m_var_t, type);
}

template <typename T>
sp<HzlDeCmp> HzlDeCmpFac<T>::Create(PageHdr pg_hdr, PageT type) {
	return HzlDeCmpFac<T>::Create(pg_hdr.exp_t, pg_hdr.m_var_t, type);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Specialization
\*--------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(HzlDeCmpFac)

} // namespace fastlanes