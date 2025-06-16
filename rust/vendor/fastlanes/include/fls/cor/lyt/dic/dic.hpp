#ifndef FLS_COR_LYT_DIC_DIC_HPP
#define FLS_COR_LYT_DIC_DIC_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/std/vector.hpp"
#include <cstdint>
#include <map>
#include <unordered_map>

/*
    0──────────4──────────8───────────────────────────8N───────────────────────────8M
    ▼─────────hdr─────────▼─────────────────────────payload─────────────────────────▼
    ┌──────────┬──────────┬────────────────────────────┬────────────────────────────┐
    │version   │ent_c     │offset_buf ...              │byte_arr_buf ...            │
    └──────────┴──────────┴────────────────────────────┴────────────────────────────┘
                            dict_lyt: uint32_t N,M | M > N
                                    e.g. type int64_t
*/

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class AnalyzeState;
class DecompressState;
class CompressState;
class HzlCmp;
class HzlDeCmp;

/*--------------------------------------------------------------------------------------------------------------------*/

class DictHdrT {
public:
	static DictHdrT load(const uint8_t* p); //
public:
	ExpT     exp_t;
	uint8_t  emp_1;
	uint8_t  emp_2;
	uint8_t  version;
	uint32_t entry_c;
};
constexpr static n_t DICT_HEADER_SIZE = 8;
static_assert(sizeof(DictHdrT) == DICT_HEADER_SIZE);

/* TODO: Remove base */
class Dic {
public:
	Dic() = delete;
	explicit Dic(AnalyzeState& stt);
	explicit Dic(DecompressState& stt);
	virtual ~Dic(); //
public:
	virtual up<idx_vec_t> get_idx_vec(const ofs_t* offset_arr, const void* byte_arr) = 0; // [fixme] allocate
	virtual void          Decompress(const uint8_t* src_p, DecompressState& stt)     = 0; //
	virtual void          Compress(CompressState& stt)                               = 0; //
	virtual void          Write(Buf& buf, CompressState& stt)                        = 0; //
	virtual void          repetition_to_index()                                      = 0; //
	virtual n_t           size()                                                     = 0; //
public:
	Buf&     data_buf;            //
	Buf&     offs_buf;            //
	Buf&     compressed_data_buf; //
	Buf&     compressed_offs_buf; //
	DictHdrT dict_hdr;
};

template <typename T>
class TDic : public Dic {
	template <class U>
	friend class dict_fac; //
public:
	explicit TDic(AnalyzeState& stt);    //
	explicit TDic(DecompressState& stt); //
	~TDic() override;                    //
public:
	// [fixme] allocates a vec everytime!
	up<idx_vec_t> get_idx_vec(const ofs_t* offset_arr, const void* byte_arr) override; //
	void          Decompress(const uint8_t* src_p, DecompressState& stt) override;     //
	void          Compress(CompressState& stt) override;                               //
	void          Write(Buf& buf, CompressState& stt) override;                        //
	n_t           size() override;                                                     //
public:
	std::unordered_map<T, idx_t> map;           //
	std::unordered_map<T, idx_t> exc_map;       //
	sp<HzlCmp>                   hzl_cmp_sp;    //
	sp<HzlDeCmp>                 hzl_de_cmp_sp; //
private:
	void serialize(); //
private:
	void repetition_to_index() override; //
};

} // namespace fastlanes
#endif // FLS_COR_LYT_DIC_DIC_HPP
