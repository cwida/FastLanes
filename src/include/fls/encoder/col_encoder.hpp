#ifndef FLS_ENCODER_COL_ENCODER_HPP
#define FLS_ENCODER_COL_ENCODER_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class FileFormat;
class WriteState;
class ReadState;
class Buf;
class EngineState;
class DecompressState;
template <typename T>
class Engine;
/*--------------------------------------------------------------------------------------------------------------------*/

template <typename PT>
class TColEncoder {
public:
	TColEncoder();
	~TColEncoder(); // NOLINT
	void  InitRead(const up<ReadState>& read_state);
	void  Reset();
	void  ExtInitCompress(ExpT exp, var_t var);
	void  ExtCompress(const PT* vec, n_t n_vec);
	void  ExtFlush(Buf& buf);
	void  ExtAnalyze(const PT* data_p, n_t n_tup);
	bsz_t ExtDicFlush(Buf& buf) const;

public:
	up<Engine<PT>>  eng_up;
	up<EngineState> eng_stt_up;
};

template <typename PT>
class TColDecoder {
public:
	TColDecoder();
	void InitDecompress(const uint8_t* p);
	void ExtInitDict(const uint8_t* p);
	Vec* Decompress();
	void Reset();
	n_t  NVector();

public:
	up<DecompressState> decom_stt_up;
	up<Engine<PT>>      eng_up;
	up<EngineState>     eng_stt_up;
};

} // namespace fastlanes
#endif // FLS_ENCODER_COL_ENCODER_HPP
