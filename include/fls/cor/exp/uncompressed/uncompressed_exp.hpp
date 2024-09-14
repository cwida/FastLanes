#ifndef FLS_COR_EXP_UNCOMPRESSED_UNCOMPRESSED_EXP_HPP
#define FLS_COR_EXP_UNCOMPRESSED_UNCOMPRESSED_EXP_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp.hpp" //
#include "fls/cor/exp/exp_type.hpp"
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/prm/prm_type.hpp"
#include <cstddef>  // for byte
#include <stdint.h> // for uint8_t

namespace fastlanes {
class uncompressed_exp { // NOLINT
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
		UNCOMPRESSED = 1,
	};

	/* uncompressed. */
	inline constexpr static RPN UNCOMPRESSED_CMPR = {1,
	                                                 1,
	                                                 2,
	                                                 true,
	                                                 {prm_t::TRS, prm_t::MEM_CPY}, //
	                                                 {fls_t::FLS_SMT, fls_t::FLS_SMT},
	                                                 {false},
	                                                 4};

	inline constexpr static RPN UNCOMPRESSED_DCMPR = {1,
	                                                  1,
	                                                  1,
	                                                  true,
	                                                  {prm_t::MEM_CPY}, //
	                                                  {fls_t::FLS_SMT},
	                                                  {false},
	                                                  4};
};
} // namespace fastlanes
#endif // FLS_COR_EXP_UNCOMPRESSED_UNCOMPRESSED_EXP_HPP
