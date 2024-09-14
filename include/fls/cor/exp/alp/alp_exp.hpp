#ifndef FLS_COR_EXP_ALP_ALP_EXP_HPP
#define FLS_COR_EXP_ALP_ALP_EXP_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp.hpp" //
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/prm/prm_type.hpp"
#include <cstddef>  // for byte
#include <stdint.h> // for uint8_t

namespace fastlanes {
class alp_exp { // NOLINT
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
		ALP = 1,
	};

	/* alp. */
	inline constexpr static RPN ALP_CMPR = {1,
	                                        6,
	                                        2,
	                                        true,
	                                        {prm_t::TRS, prm_t::ALP}, //
	                                        {fls_t::FLS64_T, fls_t::FLS_DBT},
	                                        {false},
	                                        4};

	inline constexpr static RPN ALP_DCMPR = {6,
	                                         1,
	                                         1,
	                                         true,
	                                         {prm_t::ALP}, //
	                                         {fls_t::FLS_DBT},
	                                         {false},
	                                         4};
};
} // namespace fastlanes
#endif // FLS_COR_EXP_ALP_ALP_EXP_HPP
