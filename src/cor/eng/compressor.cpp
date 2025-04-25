#include "fls/cor/eng/compressor.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/cor/eng/analyzer.hpp"
#include "fls/cor/eng/engine.hpp"
#include "fls/cor/eng/executor.hpp"
#include "fls/cor/eng/hzl_cmp_fac.hpp"
#include "fls/cor/exp/exp.hpp"
#include "fls/cor/exp/exp_fac.hpp"
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/lyt/vec.hpp"
#include "fls/cor/prm/fsst/libfsst.hpp"

namespace fastlanes {
template <typename T>
TCompressor<T>::TCompressor()
    : m_exe_up {std::make_unique<Exe<T>>()} {};

template <typename T>
void TCompressor<T>::Init(EngineState& eng_state) {
	/* Todo: [op_op]: static. */
	m_exp_sp = ExpFac<T>::Create(*eng_state.analyze_state_up);

	m_rec_cmpr_sp = HzlCmpFac<T>::Create(*eng_state.analyze_state_up, PageT::DATA_PAGE);
	m_rec_cmpr_sp->Reset();

	m_page.InitCompress(m_exp_sp);

	m_exe_up->ResCmpr(m_exp_sp);

	eng_state.compress_state_up->vec_n_in_pg = 0;
}

template <typename T>
void TCompressor<T>::Compress(Vec& src_m_vec, CompressState& compress_state) {
	m_exe_up->Execute(src_m_vec, m_vec, compress_state);
	compress_state.vec_n_in_pg += 1;
	compress_state.vec_n_in_rg += 1;
}

template <typename T>
bool TCompressor<T>::TryFlushVec(CompressState& compress_state) {
	if (compress_state.vec_n_in_pg == 0) {
		flush_vec();
		return true;
	}

	n_t next_m_vec_sz  = m_page.size_of(m_vec); // sizeof(ep_arr) if exist + sizeof(m_vec)
	n_t after_flush_sz = m_page.m_ttl_sz + next_m_vec_sz;

	if (after_flush_sz >= CFG::PQ::DATA_PG_SZ) {
		n_t improved_sz       = RecCompress(compress_state);
		n_t after_rec_cmpr_sz = after_flush_sz - improved_sz;

		if (after_rec_cmpr_sz >= CFG::PQ::DATA_PG_SZ) {
			return false;
		}
		m_page.m_ttl_sz -= improved_sz;
	}

	flush_vec();
	return true;
}

template <typename T>
void TCompressor<T>::flush_vec() {
	m_page.Absorb(m_vec);
}

template <typename T>
void TCompressor<T>::FlushPage(Buf& buf, CompressState& compress_state) {
	RecCompress(compress_state);
	FinalizeRecCompress();
	m_rec_cmpr_sp->Swap(m_exp_sp, m_page);

	/* append hdr. */
	buf.UnsafeAppend(&m_page.pg_hdr, sizeof(fastlanes::CFG::PG::HDR_SZ));

	m_page.OffsetToSink(buf);

	/* append entry_point. */
	buf.UnsafeAppend(m_page.ep_arr_buf.data(), m_page.ep_arr_buf.length());

	//	FLS_ASSERT_TRUE(m_page.Verify())
	/* append arr_arr */
	for (size_t i {0}; i < m_exp_sp->arw_c(); ++i) {
		buf.UnsafeAppend(m_page.buf_arr[i].data(), m_page.buf_arr[i].length());
	}
}

template <typename T>
void TCompressor<T>::ResetPage() {
	m_page.Reset();
}

template <typename T>
n_t TCompressor<T>::RecCompress(CompressState& compress_state) {
	return m_rec_cmpr_sp->Compress(m_exp_sp, m_page, compress_state);
}

template <typename T>
void TCompressor<T>::FinalizeRecCompress() {
	m_rec_cmpr_sp->Finalize(m_exp_sp, m_page);
}

template <typename T>
TCompressor<T>::~TCompressor() = default;

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
FLS_ALL_CTS(TCompressor)

/*---------------------------------------------------------------------------------------------------------------------\
 * State
\---------------------------------------------------------------------------------------------------------------------*/
CompressState::CompressState(EngineState& eng_state)
    : eng_state {eng_state}
    , fsst_encoder {nullptr} {
}

CompressState::~CompressState() {
	if (fsst_encoder) {
		auto encoder = (struct ::Encoder*)fsst_encoder;
		delete encoder;
	}
}
} // namespace fastlanes