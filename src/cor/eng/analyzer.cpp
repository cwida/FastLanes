#include "fls/cor/eng/analyzer.hpp"
#include "alp.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/common/str.hpp"
#include "fls/cor/eng/sampler.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/lyt/dic/dic.hpp"
#include "fls/cor/lyt/dic/dic_fac.hpp"
#include "fls/cor/prm/fsst/libfsst.hpp"
#include "fls/cor/prm/fsst12/libfsst12.hpp"
#include "fls/encoder/col_encoder.hpp"

namespace fastlanes {
template <typename PT>
Analyzer<PT>::Analyzer() {
	m_sampler_up = std::make_unique<Sampler<PT>>();
};

template <typename PT>
void Analyzer<PT>::Analyze(const PT* data_p, n_t n, AnalyzeState& stt) {

	/* TODO WIZARD */
	/* TODO SAMPLER */

	FLS_ASSERT_NULL_POINTER(stt.dic_up)
	FLS_ASSERT_NULL_POINTER(stt.fsst_encoder)

	if constexpr (std::is_same_v<PT, i64_pt>) {
		switch (stt.m_exp_t) {
		case ExpT::DICT_RLE:
		case ExpT::DICT_FRQ:
		case ExpT::DICT_VAL:
		case ExpT::DICT: {
			// [fixme] perfect_create is experimental, change it to create
			stt.dic_up = dict_fac<PT>::perfect_create(data_p, n, stt);
			return;
		}
		case ExpT::UNCOMPRESSED:
		case ExpT::FFOR:
		case ExpT::DELTA:
		case ExpT::RLE: {
			return;
		}
		case ExpT::BYTE_ARR:
		case ExpT::FSST: {
			FLS_ABORT("IS NOT SUPPORTED!")
			return;
		}
		case ExpT::INVALID: {
			FLS_ABORT("CANNOT BE INVALID!")
			return;
		}
		case ExpT::ALP: {
			FLS_ABORT("WRONG EXPRESSION!")
		}
		case ExpT::UNDECIDED:
		case ExpT::TGT_EQUALITY:
		case ExpT::TGT_1TN:
		case ExpT::TGT_1T1:
			// TODO [FIXME]
		default:
			break;
		}

	}
	/**/
	else if constexpr (std::is_same_v<PT, str_pt>) {
		switch (stt.m_exp_t) {
		case ExpT::FSST: {
			auto decoupled_vec = Str::decouple(n, const_cast<str_pt*>(data_p));
			stt.fsst_encoder   = ::fsst_create(n, decoupled_vec.first.data(), decoupled_vec.second.data(), 0);
			return;
		}
		case ExpT::FSST12: {
			auto decoupled_vec = Str::decouple(n, const_cast<str_pt*>(data_p));
			stt.fsst12_encoder = ::fsst12_create(n, decoupled_vec.first.data(), decoupled_vec.second.data(), 0);
			return;
		}
		case ExpT::DICT_RLE:
		case ExpT::DICT_FRQ:
		case ExpT::DICT_VAL:
		case ExpT::DICT:
			// [fixme] perfect_create is experimental, change it to create
			stt.dic_up = dict_fac<PT>::perfect_create(data_p, n, stt);
			return;
		case ExpT::UNCOMPRESSED:
		case ExpT::BYTE_ARR:
			return;
		case ExpT::FFOR:
		case ExpT::DELTA:
		case ExpT::RLE:
			FLS_ABORT("IS NOT SUPPORTED!")

		case ExpT::UNDECIDED:
		case ExpT::TGT_EQUALITY:
		case ExpT::TGT_1T1:
		case ExpT::TGT_1TN:
			// TODO [FIXME]
		case ExpT::INVALID:
		default:
			FLS_ABORT("CANNOT BE INVALID!")
			break;
		}
	}
	/**/
	else if constexpr (std::is_same_v<PT, i64_pt> || std::is_same_v<PT, dbl_pt>) {
		switch (stt.m_exp_t) {
		case ExpT::DICT_RLE:
		case ExpT::DICT_FRQ:
		case ExpT::DICT_VAL:
		case ExpT::DICT: {
			// [fixme] perfect_create is experimental, change it to create
			stt.dic_up = dict_fac<PT>::perfect_create(data_p, n, stt);
			return;
		}
		case ExpT::UNCOMPRESSED:
		case ExpT::FFOR:
		case ExpT::DELTA:
		case ExpT::RLE: {
			return;
		}
		case ExpT::BYTE_ARR:
		case ExpT::FSST: {
			FLS_ABORT("IS NOT SUPPORTED!")
			return;
		}
		case ExpT::INVALID: {
			FLS_ABORT("CANNOT BE INVALID!")
			return;
		}
		case ExpT::ALP: {
			auto* smp_arr = new double[1024];
			alp::encoder<double>::init(data_p, 0, n, smp_arr, *stt.alp_dbl_state_up);
			delete[] smp_arr;
			return;
		}
		case ExpT::UNDECIDED:
		case ExpT::TGT_EQUALITY:
		case ExpT::TGT_1TN:
		case ExpT::TGT_1T1:
			// TODO [FIXME]
		default:
			break;
		}

	}
	/**/
	else {
		FLS_ABORT("WRONG TYPE")
	}
}

template <typename PT>
void Analyzer<PT>::Sample(const PT* data_p, n_t n, AnalyzeState& eng_state) {
	m_sampler_up->Sample(data_p, n, *eng_state.sample_state_up);
}

template <typename PT>
void Analyzer<PT>::AdaptiveSample(const PT* data_p, n_t n, AnalyzeState& eng_state) {
	m_sampler_up->AdaptiveSample(data_p, n, *eng_state.sample_state_up);
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Analyzer)

/*---------------------------------------------------------------------------------------------------------------------\
 * State
\---------------------------------------------------------------------------------------------------------------------*/
AnalyzeState::AnalyzeState(EngineState& eng_state)
    : eng_state(eng_state)
    , fsst_encoder {nullptr}
    , fsst12_encoder {nullptr} {
	sample_state_up  = std::make_unique<SampleState>();
	alp_dbl_state_up = std::make_unique<alp::state<double>>();
}

void AnalyzeState::Set(uint8_t exp_t, uint8_t var_t) {
	FLS_ASSERT_CORRECT_EXP_T(exp_t)

	m_exp_t = static_cast<enum ExpT>(exp_t);
	m_var_t = var_t;
}

AnalyzeState::~AnalyzeState() {
	if (fsst_encoder) { fsst_destroy(static_cast<fsst_encoder_t*>(fsst_encoder)); }
	if (fsst12_encoder) { fsst12_destroy(static_cast<fsst12_encoder_t*>(fsst12_encoder)); }
}
} // namespace fastlanes