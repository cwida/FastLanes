#ifndef FLS_COR_EXP_BYTE_ARR_BYTE_ARR_EXP_HPP
#define FLS_COR_EXP_BYTE_ARR_BYTE_ARR_EXP_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp.hpp" //
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/prm/prm_type.hpp"
#include <cstddef>  // for byte
#include <stdint.h> // for uint8_t

namespace fastlanes {
class byte_arr { // NOLINT
public:
	template <typename T>
	class Exp : public fastlanes::TExp<T> {
	public:
		~Exp() override = default;                 //
		explicit Exp(ExpT exp_t, uint8_t variant); //
	public:
		const RPN* cmpr_rpn() override;   //
		const RPN* decmpr_rpn() override; //
		n_t        arw_c() override;
	};

	class cfg { // NOLINT
	public:
		inline static constexpr n_t VERSION = 1; //
	};

	enum class var_t : uint8_t { // NOLINT.
		UNCOMPRESSED   = 1,
		DELTA_NO_PATCH = 2,
	};

	inline constexpr static RPN STR_CMPR = {2, //
	                                        2,
	                                        3,
	                                        true,
	                                        {prm_t::MEM_CPY, prm_t::TRS, prm_t::MEM_CPY}, //
	                                        {fls_t::FLS_SMT, fls_t::FLS32_T, fls_t::FLS32_T},
	                                        {false},
	                                        8};

	inline constexpr static RPN STR_DECMPR = {2, //
	                                          2,
	                                          2,
	                                          true,
	                                          {prm_t::MEM_CPY, prm_t::MEM_CPY}, //
	                                          {fls_t::FLS_SMT, fls_t::FLS32_T},
	                                          {false},
	                                          8};

	/* data -> rle_bases | base | bit | bitpacked_data */
	inline constexpr static RPN WITH_DELTA_NO_PATCH_CMPR = {
	    2, //
	    5,
	    5,
	    true,
	    {prm_t::MEM_CPY, prm_t::TRS, prm_t::RSUM, prm_t::ANALYZE, prm_t::FFOR}, //
	    {fls_t::FLS_SMT, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	    {false},
	    20};

	/* rle_bases | base | bit | bitpacked_data -> data
	 * -> +1 helper at des side. */
	inline constexpr static RPN WITH_DELTA_NO_PATCH_DECMPR = {5, //
	                                                          3,
	                                                          3,
	                                                          true,
	                                                          {prm_t::MEM_CPY, prm_t::RSUM, prm_t::FFOR},
	                                                          {fls_t::FLS_SMT, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                          {false},
	                                                          20};
};
} // namespace fastlanes
#endif // FLS_COR_EXP_BYTE_ARR_BYTE_ARR_EXP_HPP
