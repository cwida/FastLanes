#ifndef FLS_COR_ENG_COMPRESSOR_HPP
#define FLS_COR_ENG_COMPRESSOR_HPP

#include "fls/common/common.hpp"
#include "fls/cor/eng/hzl_cmp.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class EngineState;
class Buf;
template <typename T>
class TExp;
template <typename T>
class Exe;

/*--------------------------------------------------------------------------------------------------------------------*/

class CompressState {
	/*[fixme], specialize it add minmax and histo */
public:
	explicit CompressState(EngineState& eng_state); //
	~CompressState();                               //
public:
	EngineState& eng_state;
	n_t          cur_src_buff {0};
	n_t          cur_des_buff {0};
	rle_idx_t    exc_pos_arr[vec_n_tup()];
	uint64_t     tmp_vec[vec_n_tup()];
	n_t          c;
	rle_idx_t    exc_c;
	bw_t         bw;
	base_t       base;
	bitmap_t     bitmap;
	n_t          vec_n_in_rg {0}; // vec number in the current rowgroup
	n_t          vec_n_in_pg {0}; // vec number in the current page
	Buf          tmp_buf;
	void*        fsst_encoder; //
};

class Compressor {};

template <typename T>
class TCompressor : public Compressor {
public:
	explicit TCompressor(); //
	~TCompressor();         //
public:
	void Init(EngineState& eng_state);                          //
	void Compress(Vec& src_vec, CompressState& compress_state); //
	bool TryFlushVec(CompressState& compress_state);            //
	void FlushPage(Buf& buf, CompressState& compress_state);    //
	void ResetPage();                                           //
	void FinalizeRecCompress();                                 //
	n_t  RecCompress(CompressState& compress_state);            //
public:
	Vec         m_vec;    //
	sp<TExp<T>> m_exp_sp; //
	up<Exe<T>>  m_exe_up; //
	Page        m_page;   //
private:
	void flush_vec(); //
private:
	sp<HzlCmp> m_rec_cmpr_sp; //
};
} // namespace fastlanes
#endif // FLS_COR_ENG_COMPRESSOR_HPP
