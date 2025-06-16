#ifndef FLS_COR_ENG_HZL_DE_CMP_HPP
#define FLS_COR_ENG_HZL_DE_CMP_HPP

#include "fls/common/alias.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Exp;
class Buf;
class Page;

/*--------------------------------------------------------------------------------------------------------------------*/

class HzlDeCmp {
public:
	virtual ~HzlDeCmp() = default; //
public:
	virtual void Decompress(const sp<Exp>& exp_sp, Page& a_page)                     = 0; //
	virtual void UNFFOR(uint8_t* src_p, Buf& des_buf)                                = 0; //
	virtual void UNALP(uint8_t* src_p, Buf& des_buf)                                 = 0; //
	virtual void UNFSST(uint8_t* string, Buf& offs_buff, Buf& data_buffs, n_t tup_c) = 0; //
private:
	virtual void decompress_buf(uint8_t* src_p, Buf& des_buf) = 0; //
};

template <typename T>
class THzlDeCmp final : public HzlDeCmp {
public:
	THzlDeCmp(); //
public:
	void Decompress(const sp<Exp>& exp_sp, Page& a_page) override;                     //
	void UNFFOR(uint8_t* src_p, Buf& des_buf) override;                                //
	void UNALP(uint8_t* src_p, Buf& des_buf) override;                                 //
	void UNFSST(uint8_t* string, Buf& offs_buff, Buf& data_buffs, n_t tup_c) override; //
private:
	void decompress_buf(uint8_t* src_p, Buf& des_buf) override; //
};
} // namespace fastlanes
#endif // FLS_COR_ENG_HZL_DE_CMP_HPP
