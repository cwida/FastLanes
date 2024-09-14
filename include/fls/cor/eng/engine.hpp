#ifndef FLS_COR_ENG_ENGINE_HPP
#define FLS_COR_ENG_ENGINE_HPP

#include "fls/common/common.hpp"

// clang-format off

namespace fastlanes {
template <typename T> class Analyzer;
template <typename T> class TCompressor;
template <typename T> class Decompressor;
class History;
class Vec;
class Page;
class AnalyzeState;
class SampleState;
class ScanState;
class CompressState;
class DecompressState;
class ColEncoder;
} // namespace fastlanes
// clang-format on

namespace fastlanes {
class EngineState {
public:
	EngineState(); //
public:
	up<AnalyzeState>  analyze_state_up;
	up<CompressState> compress_state_up;
	void              Set(uint8_t exp_t, uint8_t var_t);
};

template <typename PT>
class Engine {
public:
	explicit Engine(); //
public:
	void Analyze(const PT* data_p, n_t c, EngineState& eng_state); //
	void InitCompress(EngineState& eng_state);                     //
	void Compress(Vec& src_vec, EngineState& eng_state);           //
	void InitDeCompress(const uint8_t* p);                         //
	void Decompress(Vec& des);                                     //
	Vec* Decompress(DecompressState& stt);                         //
	void ResetPage();                                              //
public:
	up<TCompressor<PT>>  m_compressor_up;   //
	up<Decompressor<PT>> m_decompressor_up; //
	up<Analyzer<PT>>     m_analyzer_up;     //
};
} // namespace fastlanes
#endif // FLS_COR_ENG_ENGINE_HPP