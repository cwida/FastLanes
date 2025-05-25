#ifndef FLS_COR_ENG_DECOMPRESSOR_HPP
#define FLS_COR_ENG_DECOMPRESSOR_HPP

#include "fls/cor/eng/hzl_de_cmp.hpp"
#include "fls/cor/lyt/page/page.hpp"
#include "fls/cor/lyt/vec.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class EngineState;
template <typename T>
class Exe;
template <typename T>
class TExp;

/*--------------------------------------------------------------------------------------------------------------------*/

class DecompressState {
public:
	ExpT   exp_t;
	n_t    cur_src_arr {0};
	n_t    cur_des_arr {0};
	n_t    tup_c {0};
	base_t base;
	Buf    data_buf;              //
	Buf    offs_buf;              //
	Buf    decompressed_data_buf; //
	Buf    decompressed_offs_buf; //
};

template <typename T>
class Decompressor {
public:
	explicit Decompressor(); //
	~Decompressor();         //
public:
	void Decompress(Vec& des);                             //
	Vec* Decompress(DecompressState& stt);                 //
	void Init(const uint8_t* p);                           //
	void InitDict(const uint8_t* p, DecompressState& stt); //
public:
	Vec          vec;             //
	Page         page;            //
	sp<TExp<T>>  m_exp_sp;        //
	up<Exe<T>>   m_exe_up;        //
	VecParam     vec_params;      //
	sp<HzlDeCmp> m_hzl_de_cmp_sp; //
};
} // namespace fastlanes
#endif // FLS_COR_ENG_DECOMPRESSOR_HPP
