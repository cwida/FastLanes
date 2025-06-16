#ifndef FLS_COR_EXP_EXP_FAC_HPP
#define FLS_COR_EXP_EXP_FAC_HPP

#include "fls/common/common.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
enum class ExpT : uint8_t;
class PageHdr;
class AnalyzeState;
template <typename T>
class TExp;
/*--------------------------------------------------------------------------------------------------------------------*/

//[FIXME] static!
template <typename PT>
class ExpFac {
public:
	ExpFac() = delete; //
public:
	static sp<TExp<PT>> Create(AnalyzeState& analyze_state);  //
	static sp<TExp<PT>> Create(PageHdr page_hdr);             //
	static sp<TExp<PT>> Create(ExpT& exp_t, uint8_t variant); //
};
} // namespace fastlanes
#endif // FLS_COR_EXP_EXP_FAC_HPP
