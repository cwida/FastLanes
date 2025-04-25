#include "fls/cor/eng/decompressor.hpp"
#include "fls/cor/eng/engine.hpp"
#include "fls/cor/eng/executor.hpp"
#include "fls/cor/eng/hzl_de_cmp_fac.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/exp/exp_fac.hpp"
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/lyt/dic/dic.hpp"
#include "fls/cor/prm/fsst/fsst.h"
#include "fls/cor/prm/fsst12/fsst12.h"

namespace fastlanes {
template <typename T>
Decompressor<T>::Decompressor()
    : m_exe_up {std::make_unique<Exe<T>>()} {
}

template <typename T>
void Decompressor<T>::Decompress(Vec& des) {
}

template <typename T>
void Decompressor<T>::Init(const uint8_t* p) {
	page.Reset();
	auto  cur_exp_t = static_cast<ExpT>(p[0]);
	var_t cur_var_t = p[1];
	// [fixme] static exp factory
	m_exp_sp = ExpFac<T>::Create(cur_exp_t, cur_var_t); // create exp.

	page.InitDecompress(p, m_exp_sp);

	m_hzl_de_cmp_sp = HzlDeCmpFac<T>::Create(cur_exp_t, cur_var_t, PageT::DATA_PAGE);
	m_hzl_de_cmp_sp->Decompress(m_exp_sp, page);

	m_exe_up->ResDecmpr(m_exp_sp); // config executor.

	vec_params = vec.vec_param();

	vec.m_exp_t = cur_exp_t; //[fixme] a little hacky
}

template <typename T>
Vec* Decompressor<T>::Decompress(DecompressState& stt) {
	vec.tup_c = stt.tup_c;
	m_exe_up->Execute(page.page_params(), vec_params, stt);

	return &vec;
}

template <typename T>
void Decompressor<T>::InitDict(const uint8_t* p, DecompressState& stt) {
	FLS_ASSERT_NOT_NULL_POINTER(p)

	DictHdrT dict_hdr = DictHdrT::load(p);

	stt.exp_t = dict_hdr.exp_t;

	switch (dict_hdr.exp_t) {
	case ExpT::INVALID:
	case ExpT::UNDECIDED:
	case ExpT::UNCOMPRESSED:
	case ExpT::BYTE_ARR:
	case ExpT::FFOR:
	case ExpT::DELTA:
	case ExpT::ALP:
	case ExpT::RLE: {
		this->vec.dict_up = nullptr;
		return;
	}
	case ExpT::FSST: {
		fsst_decoder_t fsst_decoder;
		fsst_import(&fsst_decoder, p + sizeof(dict_hdr));
		this->vec.fsst_decoder_up = std::make_unique<fsst_decoder_t>(fsst_decoder);
		return;
	}
	case ExpT::FSST12: {
		fsst12_decoder_t fsst12_decoder;
		fsst12_import(&fsst12_decoder, p + sizeof(dict_hdr));
		this->vec.fsst12_decoder_up = std::make_unique<fsst12_decoder_t>(fsst12_decoder);
		return;
	}
	case ExpT::DICT:
	case ExpT::DICT_FRQ:
	case ExpT::DICT_VAL:
	case ExpT::DICT_RLE: {
		auto dic      = std::make_unique<TDic<T>>(stt);
		dic->dict_hdr = dict_hdr;
		dic->Decompress(p, stt);
		this->vec.dict_up = std::move(dic);
		return;
	}
	default:
		FLS_ABORT("IMPLEMENT ME")
		throw std::runtime_error("IMPELEMENT ME");
	}
}

template <typename T>
Decompressor<T>::~Decompressor() = default;

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(Decompressor)
// template class Decompressor<parquet::FixedLenByteArray>;
// template class Decompressor<parquet::Int96>;
// template class Decompressor<parquet::ByteArray>;

/*---------------------------------------------------------------------------------------------------------------------\
 * State
\---------------------------------------------------------------------------------------------------------------------*/
} // namespace fastlanes