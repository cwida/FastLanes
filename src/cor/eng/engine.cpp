#include "fls/cor/eng/engine.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/eng/executor.hpp"
#include "fls/cor/eng/sampler.hpp"
#include "fls/cor/lyt/dic/dic.hpp"
#include <memory>

namespace fastlanes {
template <typename PT>
Engine<PT>::Engine() {
	m_compressor_up   = std::make_unique<TCompressor<PT>>();
	m_analyzer_up     = std::make_unique<Analyzer<PT>>();
	m_decompressor_up = std::make_unique<Decompressor<PT>>();
}

template <typename PT>
void Engine<PT>::Analyze(const PT* data_p, n_t c, EngineState& eng_state) {
	m_analyzer_up->Analyze(data_p, c, *eng_state.analyze_state_up);
}

template <typename PT>
void Engine<PT>::Compress(Vec& src_vec, EngineState& eng_state) {
	return m_compressor_up->Compress(src_vec, *eng_state.compress_state_up);
}

template <typename PT>
void Engine<PT>::Decompress(Vec& des) {
	FLS_ASSERT_NOT_NULL_POINTER(m_decompressor_up.get())

	m_decompressor_up->Decompress(des);
}

template <typename PT>
Vec* Engine<PT>::Decompress(DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(m_decompressor_up.get())

	return m_decompressor_up->Decompress(stt);
}

template <typename PT>
void Engine<PT>::InitCompress(EngineState& eng_state) {
	m_compressor_up->Init(eng_state);
}

template <typename PT>
void Engine<PT>::InitDeCompress(const uint8_t* p) {
	m_decompressor_up->Init(p);
}

template <typename PT>
void Engine<PT>::ResetPage() {
	m_compressor_up->ResetPage();
}

/*---------------------------------------------------------------------------------------------------------------------\
+ specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Engine)
// CHECK
// {
// template class Engine<parquet::FixedLenByteColChunk>;
// template class Engine<parquet::Int96>;
// template class Engine<parquet::ByteColChunk>;
// }

/*---------------------------------------------------------------------------------------------------------------------\
 * State
\---------------------------------------------------------------------------------------------------------------------*/
EngineState::EngineState() {
	analyze_state_up  = std::make_unique<AnalyzeState>(*this);
	compress_state_up = std::make_unique<CompressState>(*this);
}

void EngineState::Set(uint8_t exp_t, uint8_t var_t) {
	analyze_state_up->Set(exp_t, var_t);
}
} // namespace fastlanes