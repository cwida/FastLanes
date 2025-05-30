#ifndef FLS_COR_LYT_VEC_HPP
#define FLS_COR_LYT_VEC_HPP

#include "fls/cfg/cfg.hpp"
#include "fls/common/common.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/lyt/buf.hpp"

struct fsst_decoder_t;
struct fsst12_decoder_t;

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Array;
class Buffer;
class EngineState;
class Page;
class Exp;
class Dic;
/*--------------------------------------------------------------------------------------------------------------------*/

class VecParam {
public:
	uint8_t* arr[CFG::VEC::MAX_VEC_ARR_C];
};

class Vec {
public:
	Vec();  //
	~Vec(); //
public:
	template <typename T>
	void     Init(const T* p, EngineState& stt); //
	void     FlushToPage(Page& page);            //
	void     Reset();                            //
	VecParam vec_param();                        //
public:
	template <typename T>
	void flatten_to(T* p); //
	void Log();            //
public:
	Buf                  buf_arr[CFG::VEC::MAX_VEC_ARR_C]; //
	n_t                  arr_c;                            //
	n_t                  tup_c;                            //
	up<fsst_decoder_t>   fsst_decoder_up;                  //
	up<fsst12_decoder_t> fsst12_decoder_up;                //
	up<Dic>              dict_up;                          //
	ExpT                 m_exp_t;                          //
};
} // namespace fastlanes
#endif // FLS_COR_LYT_VEC_HPP