#ifndef FLS_COR_ENG_HZL_CMP_HPP
#define FLS_COR_ENG_HZL_CMP_HPP

#include "fls/common/common.hpp"
#include "fls/cor/lyt/page/page.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Buf;
class Page;
class CompressState;
template <typename T>
class TExp;
class Exp;

/*--------------------------------------------------------------------------------------------------------------------*/

class HzlCmp {
public:
	virtual ~HzlCmp() = default; //
public:
	virtual n_t  Compress(const sp<Exp>& exp_sp, Page& a_page, CompressState& compress_state) = 0; //
	virtual void Finalize(const sp<Exp>& exp_sp, Page& a_page)                                = 0; //
	virtual void Reset()                                                                      = 0; //
	virtual void Swap(const sp<Exp>& exp_sp, Page& a_page)                                    = 0; //
	virtual void FFOR(Buf& src_buf, Buf& des_buf, CompressState& compress_state)              = 0; //
	virtual void ALP(Buf& src_buf, Buf& des_buf, CompressState& compress_state)               = 0; //
	virtual void FSST(Buf&           src_data_buf,
	                  Buf&           src_ofs_buf,
	                  Buf&           des_data_buf,
	                  Buf&           des_ofs_buf,
	                  CompressState& compress_state)                                          = 0; //
private:
	virtual n_t  compress_buf(Buf& src_buf, Buf& des_buf, ofs_t& cur_src_off, CompressState& compress_state) = 0; //
	virtual void finalize_buf(Buf& src_buf, Buf& des_buf, ofs_t& cur_src_off)                                = 0; //
};

template <typename T>
class THzlCmp : public HzlCmp {
public:
	THzlCmp(); //
public:
	n_t  Compress(const sp<Exp>& exp_sp, Page& a_page, CompressState& compress_state) override; //
	void Finalize(const sp<Exp>& exp_sp, Page& a_page) override;                                //
	void Reset() override;                                                                      //
	void Swap(const sp<Exp>& exp_sp, Page& a_page) override;                                    //
	void FFOR(Buf& src_buf, Buf& des_buf, CompressState& compress_state) override;              //
	void FSST(Buf&           src_data_buf,
	          Buf&           src_ofs_buf,
	          Buf&           des_data_buf,
	          Buf&           des_ofs_buf,
	          CompressState& compress_state) override; //
	void ALP(Buf& src_buf, Buf& des_buf, CompressState& compress_state) override;

public:
	Page  m_page;                  //
	ofs_t off_arr[CFG::PG::BUF_C]; //
private:
	n_t  compress_buf(Buf& src_buf, Buf& des_buf, ofs_t& cur_src_off, CompressState& compress_state) override; //
	void finalize_buf(Buf& src_buf, Buf& des_buf, ofs_t& cur_src_off) override;                                //
};

} // namespace fastlanes
#endif // FLS_COR_ENG_HZL_CMP_HPP
