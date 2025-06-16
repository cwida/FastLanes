#ifndef FLS_COR_EXP_FFOR_FFOR_EXP_HPP
#define FLS_COR_EXP_FFOR_FFOR_EXP_HPP

#include "fls/cor/exp/exp.hpp"      //
#include "fls/cor/exp/rpn.hpp"      //
#include "fls/cor/prm/prm_type.hpp" //
#include <cstddef>                  // for byte
#include <stdint.h>                 // for uint8_t

namespace fastlanes {
class ffor_exp { // NOLINT
public:
	template <typename T>
	class Exp : public TExp<T> {
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
		S_PATCH_REC = 5,
	};

	class Cfg {
	public:
		inline static constexpr n_t    VERSION   = 1;    //
		inline static constexpr double EXC_RATIO = 0.05; //
	};

	/* base_vec | bit_vec | data_vec */
	inline constexpr static RPN NO_PATCH_CMPR = {1, //
	                                             3,
	                                             3,
	                                             true,
	                                             {prm_t::TRS, prm_t::ANALYZE, prm_t::FFOR},
	                                             {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                             {false},
	                                             12};
	/* base_vec | bit_vec | data_vec */
	inline constexpr static RPN NO_PATCH_DECMPR = {3, //
	                                               1,
	                                               1,
	                                               true,
	                                               {prm_t::FFOR},
	                                               {fls_t::FLS_SMT},
	                                               {false},
	                                               12};
	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN LL_PATCH_CMPR = {1,
	                                             5,
	                                             4,
	                                             true,
	                                             {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::LL_PATCH, prm_t::FFOR},
	                                             {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                             {false},
	                                             20};

	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN LL_PATCH_DECMPR = {5,
	                                               1,
	                                               2,
	                                               true,
	                                               {prm_t::LL_PATCH, prm_t::FFOR}, //
	                                               {fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                               {false},
	                                               20};

	/* exc_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN S_PATCH_CMPR = {1,
	                                            5,
	                                            4,
	                                            true,
	                                            {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::S_PATCH, prm_t::FFOR}, //
	                                            {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                            {false},
	                                            20};

	/* exc_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN S_PATCH_REC_CMPR = {1,
	                                                5,
	                                                4,
	                                                true,
	                                                {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::S_PATCH, prm_t::FFOR}, //
	                                                {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                                {true},
	                                                20};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN S_PATCH_DECMPR = {5, //
	                                              1,
	                                              2,
	                                              true,
	                                              {prm_t::S_PATCH, prm_t::FFOR}, //
	                                              {fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                              {false},
	                                              20};

	/* exc_vec | exc_c_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN B_PATCH_CMPR = {1,
	                                            5,
	                                            4,
	                                            true,
	                                            {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::B_PATCH, prm_t::FFOR}, //
	                                            {fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                            {false},
	                                            20};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN B_PATCH_DECMPR = {5,
	                                              1,
	                                              2,
	                                              true,
	                                              {prm_t::B_PATCH, prm_t::FFOR}, //
	                                              {fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                              {false},
	                                              20};
};
} // namespace fastlanes
#endif // FLS_COR_EXP_FFOR_FFOR_EXP_HPP
