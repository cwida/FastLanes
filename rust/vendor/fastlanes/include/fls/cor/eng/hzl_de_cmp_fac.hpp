#ifndef FLS_COR_ENG_HZL_DE_CMP_FAC_HPP
#define FLS_COR_ENG_HZL_DE_CMP_FAC_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/page_type.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class PageHdr;
class AnalyzeState;
class HzlDeCmp;
template <typename T>
class TExp;

/*--------------------------------------------------------------------------------------------------------------------*/

//[FIXME] static!
template <typename T>
class HzlDeCmpFac {
public:
	using FT = std::conditional_t<std::is_same_v<T, int64_t>,
	                              uint64_t,
	                              std::conditional_t<std::is_same_v<T, int32_t>, uint32_t, T>>; //
public:
	HzlDeCmpFac() = delete; //
public:
	static sp<HzlDeCmp> Create(AnalyzeState& analyze_state, PageT type); //
	static sp<HzlDeCmp> Create(PageHdr page_hdr, PageT type);            //
	static sp<HzlDeCmp> Create(ExpT exp_t, uint8_t variant, PageT type); //
};
} // namespace fastlanes

#endif // FLS_COR_ENG_HZL_DE_CMP_FAC_HPP
