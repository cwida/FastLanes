#ifndef FLS_COR_EXP_RLE_RLE_EXP_HPP
#define FLS_COR_EXP_RLE_RLE_EXP_HPP

#include "fls/cor/exp/exp.hpp"      //
#include "fls/cor/exp/rpn.hpp"      //
#include "fls/cor/prm/prm_type.hpp" //
#include <cstddef>                  // for byte
#include <stdint.h>                 // for uint8_t

namespace fastlanes {
class rle_exp { // NOLINT
public:
	template <typename T>
	class Exp : public fastlanes::TExp<T> {
	public:
		~Exp() override = default;                 //
		explicit Exp(ExpT exp_t, uint8_t variant); //
	public:
		const RPN* cmpr_rpn() override;   //
		const RPN* decmpr_rpn() override; //
		n_t        arw_c() override;      //
	};

	enum class var_t : uint8_t { // NOLINT.
		UNCOMPRESSED        = 1,
		DELTA_NO_PATCH      = 2,
		UNCOMPRESSED_REC    = 3,
		DELTA_NO_PATCH_REC  = 4, // rec on rle-values
		DELTA_NO_PATCH_REC2 = 5, // rec on rle-values and rsum-bases
	};

	class Cfg {
	public:
		inline static constexpr n_t VERSION = 1; //
	};

	inline constexpr static RPN UNCOMPRESSED_CMPR = {2, //
	                                                 2,
	                                                 3,
	                                                 true,
	                                                 {prm_t::MEM_CPY, prm_t::TRS, prm_t::MEM_CPY}, //
	                                                 {fls_t::FLS_SMT, fls_t::FLS16_T, fls_t::FLS16_T},
	                                                 {},
	                                                 8};

	inline constexpr static RPN UNCOMPRESSED_DECMPR = {2, //
	                                                   2,
	                                                   2,
	                                                   true,
	                                                   {prm_t::MEM_CPY, prm_t::MEM_CPY}, //
	                                                   {fls_t::FLS_SMT, fls_t::FLS16_T},
	                                                   {},
	                                                   8};

	/* data -> rle_bases | base | bit | bitpacked_data */
	inline constexpr static RPN DELTA_NO_PATCH_CMPR = {
	    2, //
	    5,
	    5,
	    true,
	    {prm_t::MEM_CPY, prm_t::TRS, prm_t::RSUM, prm_t::ANALYZE, prm_t::FFOR}, //
	    {fls_t::FLS_SMT, fls_t::FLS16_T, fls_t::FLS16_T, fls_t::FLS16_T, fls_t::FLS16_T},
	    {},
	    20};
	/* rle_bases | base | bit | bitpacked_data -> data
	 * -> +1 helper at des side. */
	inline constexpr static RPN DELTA_NO_PATCH_DECMPR = {5, //
	                                                     3,
	                                                     3,
	                                                     true,
	                                                     {prm_t::MEM_CPY, prm_t::RSUM, prm_t::FFOR},
	                                                     {fls_t::FLS_SMT, fls_t::FLS16_T, fls_t::FLS16_T},
	                                                     {},
	                                                     20};

	inline constexpr static RPN UNCOMPRESSED_REC_CMPR = {2, //
	                                                     2,
	                                                     3,
	                                                     true,
	                                                     {prm_t::MEM_CPY, prm_t::TRS, prm_t::MEM_CPY}, //
	                                                     {fls_t::FLS_SMT, fls_t::FLS16_T, fls_t::FLS16_T},
	                                                     {true},
	                                                     8};

	/* data -> rle_bases | base | bit | bitpacked_data */
	inline constexpr static RPN DELTA_NO_PATCH_CMPR_REC = {
	    2, //
	    5,
	    5,
	    true,
	    {prm_t::MEM_CPY, prm_t::TRS, prm_t::RSUM, prm_t::ANALYZE, prm_t::FFOR}, //
	    {fls_t::FLS_SMT, fls_t::FLS16_T, fls_t::FLS16_T, fls_t::FLS16_T, fls_t::FLS16_T},
	    {
	        true,
	    },
	    20};

	/* data -> rle_bases | base | bit | bitpacked_data */
	inline constexpr static RPN DELTA_NO_PATCH_CMPR_REC2 = {
	    2, //
	    5,
	    5,
	    true,
	    {prm_t::MEM_CPY, prm_t::TRS, prm_t::RSUM, prm_t::ANALYZE, prm_t::FFOR}, //
	    {fls_t::FLS_SMT, fls_t::FLS16_T, fls_t::FLS16_T, fls_t::FLS16_T, fls_t::FLS16_T},
	    {
	        true,
	        true,
	    },
	    20};
};
} // namespace fastlanes
#endif // FLS_COR_EXP_RLE_RLE_EXP_HPP
