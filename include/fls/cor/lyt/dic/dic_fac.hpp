#ifndef FLS_COR_LYT_DIC_DIC_FAC_HPP
#define FLS_COR_LYT_DIC_DIC_FAC_HPP

#include "fls/common/common.hpp"
#include "fls/std/vector.hpp"
#include <unordered_map>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class ColChunk;
class AnalyzeState;
template <typename T>
class TDic;

/*--------------------------------------------------------------------------------------------------------------------*/

template <typename PT>
using dic_t = std::unordered_map<PT, idx_t>;

template <typename PT>
class dict_fac {
public:
	dict_fac() = delete; //
public:
	static up<TDic<PT>> adaptive_create(const PT* data_p, n_t n, AnalyzeState& stt); //
	static up<TDic<PT>> perfect_create(const PT* data_p, n_t n, AnalyzeState& stt);  //[TODO] experimental
	static bsz_t        multi_dic_create(const std::vector<PT>&     src_col,
	                                     AnalyzeState&              src_stt,
	                                     const std::vector<i64_pt>& tgt_col,
	                                     AnalyzeState&              tgt_stt); //
	static bsz_t        multi_dic_create(const std::vector<PT>&     src_col,
	                                     AnalyzeState&              src_stt,
	                                     const std::vector<str_pt>& tgt_col,
	                                     AnalyzeState&              tgt_stt); //

	/*Experimental */
public:
	static bsz_t exp_multi_dic_create(const std::vector<PT>&     src_col,
	                                  const std::vector<i64_pt>& tgt_col); //
	static bsz_t exp_multi_dic_create(const std::vector<PT>&     src_col,
	                                  const std::vector<str_pt>& tgt_col); //
	static bsz_t exp_multi_dic_create(const std::vector<PT>&     src_col,
	                                  const std::vector<dbl_pt>& tgt_col); //
	static bsz_t exp_multi_dic_create(const std::vector<PT>& src_col);     //
private:
	static up<TDic<PT>>
	m_create_random(const PT* data_p, n_t possible_sample_c, vector<bool>& is_processed, AnalyzeState& stt); //
	static up<TDic<PT>> m_create_from(const PT* data_p, n_t sample_num, AnalyzeState& stt);                  //
	static n_t          m_compare(dic_t<PT>& l, dic_t<PT>& r);                                               //
	static void         m_combine(dic_t<PT>& left, dic_t<PT>& right);                                        //
};

} // namespace fastlanes
#endif // FLS_COR_LYT_DIC_DIC_FAC_HPP
