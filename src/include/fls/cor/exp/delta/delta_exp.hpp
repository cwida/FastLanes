#ifndef FLS_COR_EXP_DELTA_DELTA_EXP_HPP
#define FLS_COR_EXP_DELTA_DELTA_EXP_HPP

#include "fls/cor/exp/exp.hpp"      //
#include "fls/cor/exp/rpn.hpp"      //
#include "fls/cor/prm/prm_type.hpp" //
#include <cstddef>                  // for byte
#include <stdint.h>                 // for uint8_t

namespace fastlanes {
class delta_exp { // NOLINT
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

	enum class var_t : uint8_t { // NOLINT.
		NO_PATCH    = 1,
		LL_PATCH    = 2,
		S_PATCH     = 3,
		B_PATCH     = 4,
		B_PATCH_REC = 5,
	};

	class Cfg {
	public:
		inline static constexpr n_t    VERSION   = 1;    //
		inline static constexpr double EXC_RATIO = 0.05; //
	};

	/* data -> delta_bases | base | bit | bitpacked_data */
	inline constexpr static RPN NO_PATCH_CMPR = {1, //
	                                             4,
	                                             4,
	                                             true,
	                                             {prm_t::TRS, prm_t::RSUM, prm_t::ANALYZE, prm_t::FFOR}, //
	                                             {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                             {},
	                                             16};
	/* delta_bases | base | bit | bitpacked_data -> data
	 * -> +1 helper at des side. */
	inline constexpr static RPN NO_PATCH_DECMPR = {4, //
	                                               2,
	                                               2,
	                                               true,
	                                               {prm_t::RSUM, prm_t::FFOR},
	                                               {fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                               {},
	                                               16};
	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN LL_PATCH_CMPR = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::LL_PATCH, prm_t::FFOR},
	    {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	    {},
	    24};

	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN LL_PATCH_DECMPR = {6,
	                                               2,
	                                               3,
	                                               true,
	                                               {prm_t::RSUM, prm_t::LL_PATCH, prm_t::FFOR},
	                                               {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                               {},
	                                               24};

	/* exc_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN S_PATCH_CMPR = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::S_PATCH, prm_t::FFOR},
	    {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	    {},
	    24};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN S_PATCH_DECMPR = {6, //
	                                              2,
	                                              3,
	                                              true,
	                                              {prm_t::RSUM, prm_t::S_PATCH, prm_t::FFOR},
	                                              {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                              {},
	                                              24};

	/* exc_vec | exc_c_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN B_PATCH_CMPR = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::B_PATCH, prm_t::FFOR},
	    {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	    {},
	    24};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN B_PATCH_DECMPR = {6,
	                                              2,
	                                              3,
	                                              true,
	                                              {prm_t::RSUM, prm_t::B_PATCH, prm_t::FFOR},
	                                              {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                              {},
	                                              20};

	/* exc_vec | exc_c_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN B_PATCH_CMPR_REC = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::B_PATCH, prm_t::FFOR},
	    {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	    {false, true},
	    24};
};
} // namespace fastlanes
#endif // FLS_COR_EXP_DELTA_DELTA_EXP_HPP
