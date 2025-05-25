#ifndef ALP_ENCODER_HPP
#define ALP_ENCODER_HPP

#include "alp/common.hpp"
#include "alp/config.hpp"
#include "alp/state.hpp"
#include <list>
#include <map>
#include <vector>

#ifdef __AVX2__

#include <immintrin.h>

#endif

/*
 * ALP Encoding
 */
namespace alp {

template <typename PT, bool is_null = false>
struct encoder {
	using UT = typename inner_t<PT>::ut;
	using ST = typename inner_t<PT>::st;
	/*
	 * Check for special values which are impossible for ALP to encode
	 * because they cannot be cast to int64 without an undefined behaviour
	 */
	//! Analyze FFOR to obtain bitwidth and frame-of-reference value
	static void analyze_ffor(const ST* input_vector, bw_t& bit_width, ST* base_for);
	/*
	 * Function to sort the best combinations from each vector sampled from the rowgroup
	 * First criteria is number of times it appears
	 * Second criteria is bigger exponent
	 * Third criteria is bigger factor
	 */
	static bool compare_best_combinations(const std::pair<std::pair<int, int>, int>& t1,
	                                      const std::pair<std::pair<int, int>, int>& t2);
	/*
	 * Find the best combinations of factor-exponent from each vector sampled from a rowgroup
	 * This function is called once per rowgroup
	 * This operates over ALP first level samples
	 */
	static void find_top_k_combinations(const PT* smp_arr, state<PT>& stt);
	/*
	 * Find the best combination of factor-exponent for a vector from within the best k combinations
	 * This is ALP second level sampling
	 */
	static void
	find_best_exponent_factor_from_combinations(const std::vector<std::pair<uint8_t, uint8_t>>& top_combinations,
	                                            uint8_t                                         top_k,
	                                            const PT*                                       input_vector,
	                                            uint8_t&                                        factor,
	                                            uint8_t&                                        exponent);

	static void encode_simdized(const PT*      data_p,
	                            PT*            exceptions,
	                            exp_p_t*       exceptions_positions,
	                            ST*            encoded_integers,
	                            state<PT>&     st,
	                            const uint8_t* null_map);

	static void encode(const PT*      input_vector,
	                   PT*            exceptions,
	                   uint16_t*      exceptions_positions,
	                   ST*            encoded_integers,
	                   state<PT>&     stt,
	                   const uint8_t* null_map);

	static void init(const PT* rowgroup_data_p, uint64_t rowgroup_size, PT* sample_arr, state<PT>& stt);
};

} // namespace alp

#endif
