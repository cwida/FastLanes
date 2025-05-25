#include "fls/encoder/col_encoder.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/compressor.hpp"
#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/eng/engine.hpp"
#include "fls/cor/eng/sampler.hpp"
#include "fls/cor/lyt/dic/dic.hpp"
#include "fls/cor/prm/fsst/fsst.h"
#include "fls/cor/prm/fsst12/fsst12.h"

namespace fastlanes {

template <typename PT>
TColEncoder<PT>::TColEncoder() {
	eng_up     = std::make_unique<Engine<PT>>();
	eng_stt_up = std::make_unique<EngineState>();
}

template <typename PT>
TColEncoder<PT>::~TColEncoder() = default;

template <typename PT>
TColDecoder<PT>::TColDecoder() {
	eng_up       = std::make_unique<Engine<PT>>();
	eng_stt_up   = std::make_unique<EngineState>();
	decom_stt_up = std::make_unique<DecompressState>();
}

template <typename PT>
void TColEncoder<PT>::ExtInitCompress(ExpT exp, var_t var) {
	eng_stt_up->Set(static_cast<uint8_t>(exp), var);
	eng_up->InitCompress(*eng_stt_up);
}

template <typename PT>
void TColEncoder<PT>::ExtAnalyze(const PT* data_p, n_t n_tup) {
	eng_up->Analyze(data_p, n_tup, *eng_stt_up);
}

template <typename PT>
void TColEncoder<PT>::InitRead(const up<ReadState>& rd_stt) {
	// auto*& cur_p = rd_stt->m_cur_p;
	//
	// /**/
	// FLS_ASSERT_NOT_NULL_POINTER(cur_p)
	//
	// ep    = *reinterpret_cast<ColEncoderEP*>(cur_p);
	// cur_p = cur_p + sizeof(ColEncoderEP);
	//
	// bitmap.Read(rd_stt, ep.arr_0_bsz);
	// data.Read(rd_stt, ep.arr_1_bsz);
}

template <typename PT>
void TColEncoder<PT>::Reset() {
	eng_stt_up.reset();
	eng_stt_up = std::make_unique<EngineState>();
	eng_up.reset();
	eng_up = std::make_unique<Engine<PT>>();
}

template <typename PT>
void TColDecoder<PT>::Reset() {
	eng_stt_up.reset();
	eng_stt_up = std::make_unique<EngineState>();
	decom_stt_up.reset();
	decom_stt_up = std::make_unique<DecompressState>();
	eng_up.reset();
	eng_up = std::make_unique<Engine<PT>>();
}

template <typename PT>
n_t TColDecoder<PT>::NVector() {
	return eng_up->m_decompressor_up->page.vec_c();
}

template <typename PT>
void TColEncoder<PT>::ExtCompress(const PT* data, n_t n_vec) {
	Vec src_vec;
	for (idx_t vec_idx {0}; vec_idx < n_vec; ++vec_idx) {
		src_vec.Init<PT>(data + (vec_idx * CFG::VEC_SZ), *eng_stt_up);
		eng_up->Compress(src_vec, *eng_stt_up);
		eng_up->m_compressor_up->TryFlushVec(*eng_stt_up->compress_state_up);
	}
}

template <typename PT>
bsz_t TColEncoder<PT>::ExtDicFlush(Buf& buf) const {
	/* TODO REMOVE dict_bsz */
	FLS_ASSERT_ZERO(buf.Size())
	/* Dict Size*/
	n_t   dict_bsz {0};
	auto& stt = eng_stt_up->analyze_state_up;
	switch (stt->m_exp_t) {
	case ExpT::INVALID:
	case ExpT::UNDECIDED:
	case ExpT::UNCOMPRESSED:
	case ExpT::BYTE_ARR:
	case ExpT::FFOR:
	case ExpT::DELTA:
	case ExpT::RLE:
		dict_bsz = 0;
		break;
	case ExpT::FSST: {
		dict_bsz = FSST_MAXHEADER + sizeof(DictHdrT);
		break;
	}
	case ExpT::FSST12: {
		dict_bsz = FSST12_MAXHEADER + sizeof(DictHdrT);
		break;
	}
	case ExpT::DICT:
	case ExpT::DICT_RLE:
	case ExpT::DICT_FRQ:
	case ExpT::DICT_VAL: {
		dict_bsz = eng_stt_up->analyze_state_up->dic_up->size();
		break;
	}
		// TODO [FIXME]
	default:
		dict_bsz = 0;
		break;
	}

	/* Compress */
	switch (stt->m_exp_t) {
	case ExpT::INVALID:
	case ExpT::UNDECIDED:
	case ExpT::UNCOMPRESSED:
	case ExpT::BYTE_ARR:
	case ExpT::FFOR:
	case ExpT::DELTA:
	case ExpT::RLE:
	case ExpT::FSST:
	case ExpT::FSST12:
	case ExpT::ALP:
		break;
	case ExpT::DICT:
	case ExpT::DICT_RLE:
	case ExpT::DICT_FRQ:
	case ExpT::DICT_VAL: {
		eng_stt_up->analyze_state_up->dic_up->Compress(*eng_stt_up->compress_state_up);
	} break;
		// TODO [FIXME]
	default:
		FLS_ABORT("IMPLEMENT ME");
		throw std::runtime_error("IMPLEMENT ME");
	}

	/*Write*/
	// [fixme] push dw to FLS lib
	switch (stt->m_exp_t) {
	case ExpT::INVALID:
	case ExpT::UNDECIDED:
	case ExpT::UNCOMPRESSED:
	case ExpT::BYTE_ARR:
	case ExpT::FFOR:
	case ExpT::DELTA:
	case ExpT::RLE:
	case ExpT::ALP:
		break;
	case ExpT::FSST: {
		FLS_ASSERT_NOT_NULL_POINTER(stt->fsst_encoder);
		// write hdr
		DictHdrT dict_hdr = {ExpT::FSST, 0, 0, 0, 0};
		buf.UnsafeAppend(&dict_hdr, sizeof(DictHdrT));
		// export fsst
		auto length =
		    fsst_export(static_cast<fsst_encoder_t*>(stt->fsst_encoder), buf.mutable_data() + sizeof(DictHdrT));
		buf.Advance(length);
		break;
	}
	case ExpT::FSST12: {
		FLS_ASSERT_NOT_NULL_POINTER(stt->fsst12_encoder);
		// write hdr
		DictHdrT dict_hdr = {ExpT::FSST12, 0, 0, 0, 0};
		buf.UnsafeAppend(&dict_hdr, sizeof(DictHdrT));
		// export fsst
		auto length =
		    fsst12_export(static_cast<fsst12_encoder_t*>(stt->fsst12_encoder), buf.mutable_data() + sizeof(DictHdrT));
		buf.Advance(length);
		break;
	}
	case ExpT::DICT:
	case ExpT::DICT_RLE:
	case ExpT::DICT_FRQ:
	case ExpT::DICT_VAL: {
		eng_stt_up->analyze_state_up->dic_up->Write(buf, *eng_stt_up->compress_state_up);
	} break;
		// TODO [FIXME]
	default:
		FLS_ABORT("IMPLEMENT ME");
		throw std::runtime_error("IMPLEMENT ME");
	}

	return dict_bsz;
}

template <typename PT>
void TColDecoder<PT>::ExtInitDict(const uint8_t* p) {
	eng_up->m_decompressor_up->InitDict(p, *decom_stt_up);
}

template <typename PT>
void TColEncoder<PT>::ExtFlush(Buf& buf) {
	eng_up->m_compressor_up->FlushPage(buf, *eng_stt_up->compress_state_up);
}

template <typename PT>
void TColDecoder<PT>::InitDecompress(const uint8_t* p) {
	eng_up->InitDeCompress(p);
}

template <typename PT>
Vec* TColDecoder<PT>::Decompress() {
	return eng_up->Decompress(*decom_stt_up);
}

FLS_CTS(TColEncoder, i64_pt)
FLS_CTS(TColEncoder, str_pt)
FLS_CTS(TColEncoder, dbl_pt)

FLS_CTS(TColDecoder, i64_pt)
FLS_CTS(TColDecoder, str_pt)
FLS_CTS(TColDecoder, dbl_pt)
} // namespace fastlanes