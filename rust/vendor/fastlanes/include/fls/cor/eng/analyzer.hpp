#ifndef FLS_COR_ENG_ANALYZER_HPP
#define FLS_COR_ENG_ANALYZER_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/lyt/buf.hpp"

namespace alp {
template <typename PT>
struct state;
}

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class ColEncoder;
class Dic;
class Buf;
class EngineState;
class SampleState;
template <typename T>
class Sampler;
/*--------------------------------------------------------------------------------------------------------------------*/

class AnalyzeState {
public:
	explicit AnalyzeState(EngineState& eng_state); //
	~AnalyzeState();                               //
public:
	void Set(uint8_t exp_t, uint8_t var_t); //
public:
	up<SampleState> sample_state_up; //
	ExpT            m_exp_t;         //
	uint8_t         m_var_t;         //
	EngineState&    eng_state;       //
	/* DICT */
	up<Dic> dic_up;              //
	Buf     data_buf;            //
	Buf     offs_buf;            //
	Buf     compressed_data_buf; //
	Buf     compressed_offs_buf; //
	/* ALP */
	up<alp::state<double>> alp_dbl_state_up; //
	/* FSST */
	void* fsst_encoder; //
	/* FSST12 */
	void* fsst12_encoder; //
};

template <typename PT>
class Analyzer {
public:
	Analyzer(); //
public:
	void Sample(const PT* data_p, n_t n, AnalyzeState& eng_state);
	void AdaptiveSample(const PT* data_p, n_t n, AnalyzeState& eng_state);
	void Analyze(const PT* data_p, n_t n, AnalyzeState& analyze_state);

private:
	up<Sampler<PT>> m_sampler_up; //
};
} // namespace fastlanes
#endif // FLS_COR_ENG_ANALYZER_HPP
