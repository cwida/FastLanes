#ifndef FLS_COR_EXP_DICT_DICT_EXP_HPP
#define FLS_COR_EXP_DICT_DICT_EXP_HPP

#include "fls/common/common.hpp"
#include "fls/cor/exp/exp.hpp" //
#include "fls/cor/exp/rpn.hpp"
#include "fls/cor/prm/prm_type.hpp"
#include <cstddef>  // for byte
#include <stdint.h> // for uint8_t

namespace fastlanes {
class dict_exp { // NOLINT
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
		UNCOMPRESSED      = 1,
		FFOR_NO_PATCH     = 2,
		FFOR_LL_PATCH     = 3,
		FFOR_S_PATCH      = 4,
		FFOR_B_PATCH      = 5,
		FFOR_S_PATCH_REC  = 6,
		DELTA_NO_PATCH    = 7,
		DELTA_LL_PATCH    = 8,
		DELTA_S_PATCH     = 9,
		DELTA_B_PATCH     = 10,
		DELTA_B_PATCH_REC = 11,
	};

	/* uncompressed. */
	inline constexpr static RPN UNCOMPRESSED_CMPR = {
	    1, 1, 2, true, {prm_t::TRS, prm_t::MEM_CPY}, {fls_t::FLS32_T, fls_t::FLS32_T}, {false}, 4};

	inline constexpr static RPN UNCOMPRESSED_DECMPR = {1, 1, 1, true, {prm_t::MEM_CPY}, {fls_t::FLS32_T}, {false}, 4};

	/* base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_NO_PATCH_CMPR = {1,
	                                                  3,
	                                                  3,
	                                                  true,
	                                                  {prm_t::TRS, prm_t::ANALYZE, prm_t::FFOR},
	                                                  {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                  {false},
	                                                  12};
	/* base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_NO_PATCH_DECMPR = {3, 1, 1, true, {prm_t::FFOR}, {fls_t::FLS32_T}, {false}, 12};

	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_LL_PATCH_CMPR = {1,
	                                                  5,
	                                                  4,
	                                                  true,
	                                                  {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::LL_PATCH, prm_t::FFOR},
	                                                  {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                  {false},
	                                                  20};

	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_LL_PATCH_DECMPR = {
	    5, 1, 2, true, {prm_t::LL_PATCH, prm_t::FFOR}, {fls_t::FLS32_T, fls_t::FLS32_T}, {false}, 20};

	/* exc_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_S_PATCH_CMPR = {1,
	                                                 5,
	                                                 4,
	                                                 true,
	                                                 {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::S_PATCH, prm_t::FFOR},
	                                                 {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                 {false},
	                                                 20};

	/* exc_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_S_PATCH_REC_CMPR = {
	    1,
	    5,
	    4,
	    true,
	    {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::S_PATCH, prm_t::FFOR}, //
	    {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	    {true},
	    20};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_S_PATCH_DECMPR = {
	    5, 1, 2, true, {prm_t::S_PATCH, prm_t::FFOR}, {fls_t::FLS32_T, fls_t::FLS32_T}, {false}, 20};

	/* exc_vec | exc_c_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_B_PATCH_CMPR = {1,
	                                                 5,
	                                                 4,
	                                                 true,
	                                                 {prm_t::TRS, prm_t::PA_ANALYZE, prm_t::B_PATCH, prm_t::FFOR},
	                                                 {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                 {false},
	                                                 20};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN FFOR_B_PATCH_DECMPR = {
	    5, 1, 2, true, {prm_t::B_PATCH, prm_t::FFOR}, {fls_t::FLS32_T, fls_t::FLS32_T}, {false}, 20};

	/* data -> delta_bases | base | bit | bitpacked_data */
	inline constexpr static RPN DELTA_NO_PATCH_CMPR = {1, //
	                                                   4,
	                                                   4,
	                                                   true,
	                                                   {prm_t::TRS, prm_t::RSUM, prm_t::ANALYZE, prm_t::FFOR}, //
	                                                   {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                   {},
	                                                   16};
	/* delta_bases | base | bit | bitpacked_data -> data
	 * -> +1 helper at des side. */
	inline constexpr static RPN DELTA_NO_PATCH_DECMPR = {4, //
	                                                     2,
	                                                     2,
	                                                     true,
	                                                     {prm_t::RSUM, prm_t::FFOR},
	                                                     {fls_t::FLS32_T, fls_t::FLS32_T},
	                                                     {},
	                                                     16};
	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN DELTA_LL_PATCH_CMPR = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::LL_PATCH, prm_t::FFOR},
	    {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	    {},
	    24};

	/* exc_vec | first_exc_pos | base_vec | bit_vec | data_vec */
	inline constexpr static RPN DELTA_LL_PATCH_DECMPR = {6,
	                                                     2,
	                                                     3,
	                                                     true,
	                                                     {prm_t::RSUM, prm_t::LL_PATCH, prm_t::FFOR},
	                                                     {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                     {},
	                                                     24};

	/* exc_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN DELTA_S_PATCH_CMPR = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::S_PATCH, prm_t::FFOR},
	    {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	    {},
	    24};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN DELTA_S_PATCH_DECMPR = {6, //
	                                                    2,
	                                                    3,
	                                                    true,
	                                                    {prm_t::RSUM, prm_t::S_PATCH, prm_t::FFOR},
	                                                    {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                    {},
	                                                    24};

	/* exc_vec | exc_c_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN DELTA_B_PATCH_CMPR = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::B_PATCH, prm_t::FFOR},
	    {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	    {},
	    24};

	/* exc_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN DELTA_B_PATCH_DECMPR = {6,
	                                                    2,
	                                                    3,
	                                                    true,
	                                                    {prm_t::RSUM, prm_t::B_PATCH, prm_t::FFOR},
	                                                    {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	                                                    {},
	                                                    20};

	/* exc_vec | exc_c_vec | sel_vec | base_vec | bit_vec | data_vec */
	inline constexpr static RPN DELTA_B_PATCH_REC_CMPR = {
	    1,
	    6,
	    5,
	    true,
	    {prm_t::TRS, prm_t::RSUM, prm_t::PA_ANALYZE, prm_t::B_PATCH, prm_t::FFOR},
	    {fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T, fls_t::FLS32_T},
	    {false, true},
	    24};
};
class DictFrqExp : public dict_exp {};
class DictValExp : public dict_exp {};

} // namespace fastlanes
#endif // FLS_COR_EXP_DICT_DICT_EXP_HPP
