#ifndef FLS_PRIMITIVE_ALP_SAMPLER_HPP
#define FLS_PRIMITIVE_ALP_SAMPLER_HPP

// NOLINTBEGIN

#include "fls/primitive/alp/config.hpp"
#include "fls/primitive/alp/cutter.hpp"
#include <algorithm>
#include <map>

namespace alp { namespace sampler {

using param = std::pair<uint64_t, std::pair<int, int>>;

inline bool compare(const param& t1, const param& t2) {
	return (t1.first < t2.first) ||
	       (t1.first == t2.first && (t2.second.first < t1.second.first)) || // We prefer bigger exponents
	       ((t1.first == t2.first && t2.second.first == t1.second.first) &&
	        (t2.second.second < t1.second.second)); // We prefer bigger factors
}

namespace rowgroup {

inline void
sample(const double* in_vector, size_t cur_offset, size_t in_vector_len, double* out_vector_sample, state& stt) {
	size_t   left_on_vector = in_vector_len - cur_offset;
	size_t   sampled_size   = std::min(RG_C, left_on_vector);
	double   step_size      = sampled_size / (double)STEP_N;
	uint32_t c {0};

	for (size_t step_i = 0; step_i < STEP_N; step_i++) { // Vector
		auto rg_idx = std::lround(step_i * step_size);
		if (rg_idx > sampled_size - (SMP_R_C * RG_SMP_RUN_JMP)) { rg_idx = sampled_size - (SMP_R_C * RG_SMP_RUN_JMP); }
		for (size_t run_i = 0; run_i < SMP_R_C / RG_SMP_MICRO_RUN_SIZE; run_i++) {             // Segments per vector
			for (size_t micro_run_i = 0; micro_run_i < RG_SMP_MICRO_RUN_SIZE; micro_run_i++) { // Consecutive runs
				out_vector_sample[c++] = in_vector[cur_offset + rg_idx + (run_i * RG_SMP_RUN_JMP) + micro_run_i];
			}
		}
	}
}

/*
 * Function to sort the best combinations from each vector sampled from the rowgroup
 * First criteria is number of times it appears
 * Second criteria is bigger exponent
 * Third criteria is bigger factor
 */
inline bool compare_best_combinations(const std::pair<std::pair<int, int>, int>& t1,
                                      const std::pair<std::pair<int, int>, int>& t2) {
	return (t1.second > t2.second) || (t1.second == t2.second && (t2.first.first < t1.first.first)) ||
	       ((t1.second == t2.second && t2.first.first == t1.first.first) && (t2.first.second < t1.first.second));
}

/*
 * Find the best combinations for each vector in the rowgroup
 * Then, select the best (n_comb at most)
 */
inline void find_topn_combination(double* smp_arr, state& stt) {
	uint64_t                           SMP_V_C = SMP_C / SMP_R_C;
	uint64_t                           mvec_c  = SMP_R_C;
	std::map<std::pair<int, int>, int> global_combinations;
	int                                smp_offset {0};

	// For each vector in the rg sample
	size_t all_best_total_bits {(mvec_c * (64 + 16)) + (mvec_c * (64))};
	for (int smp_n = 0; smp_n < SMP_V_C; smp_n++) {
		uint8_t  found_factor {0};
		uint8_t  found_exponent {0};
		uint64_t best_total_bits {(mvec_c * (64 + 16)) + (mvec_c * (64))}; // worst scenario

		// We test all combinations (~170 combinations)
		for (int exp_ref = 18; exp_ref >= 0; exp_ref--) {
			for (int factor_idx = exp_ref; factor_idx >= 0; factor_idx--) {
				uint64_t exception_c {0};
				uint64_t matches_c {0};
				uint64_t bits_per_digit {0};
				uint64_t local_total_bits {0};
				int64_t  local_max_digits {std::numeric_limits<int64_t>().min()};
				int64_t  local_min_digits {std::numeric_limits<int64_t>().max()};

				for (size_t i = 0; i < mvec_c; ++i) {
					int64_t digits;
					double  dbl = smp_arr[smp_offset + i];
					double  orig;
					double  cd;

					cd     = dbl * alp::exp_arr[exp_ref] * alp::frac_arr[factor_idx];
					digits = alp::double_to_int64(cd);
					orig   = digits * alp::fact_arr[factor_idx] * alp::frac_arr[exp_ref];
					if (orig == dbl) {
						matches_c++;
						if (digits > local_max_digits) { local_max_digits = digits; }
						if (digits < local_min_digits) { local_min_digits = digits; }
						continue;
					}
					exception_c++;
				}
				// We skip combinations which yields to all exceptions
				if (matches_c < 2) { // We skip combinations which yields to less than 2 matches
					continue;
				}

				// Evaluate factor/exponent performance (we optimize for FOR)
				uint64_t delta = local_max_digits - local_min_digits;
				bits_per_digit = ceil(log2(delta + 1));
				local_total_bits += mvec_c * bits_per_digit;
				local_total_bits += exception_c * (64 + 16);

				if ((local_total_bits < best_total_bits) ||
				    (local_total_bits == best_total_bits && (found_exponent < exp_ref)) ||
				    // We prefer bigger exponents
				    ((local_total_bits == best_total_bits && found_exponent == exp_ref) &&
				     (found_factor < factor_idx)) // We prefer bigger factors
				) {
					best_total_bits = local_total_bits;
					found_exponent  = exp_ref;
					found_factor    = factor_idx;
					if (best_total_bits < all_best_total_bits) { all_best_total_bits = best_total_bits; }
				}
			}
		}

		std::pair<int, int> cmb = std::make_pair(found_exponent, found_factor);
		if (global_combinations.count(cmb)) {
			global_combinations[cmb] += 1;
		} else {
			global_combinations[cmb] = 1;
		}
		smp_offset += mvec_c;
	}

	if (all_best_total_bits >= MAGIC_LIMIT) {
		std::cout << "ALP CUTTER Detected!" << std::endl; //
		                                                  //		stt.scheme = ALP_CUTTER;
		                                                  //		return;
	}

	std::vector<std::pair<std::pair<int, int>, int>> comb_pairs;
	// Convert map pairs to vector for sort
	for (auto const& itr : global_combinations) {
		comb_pairs.emplace_back(itr.first, // Pair exp, fac
		                        itr.second // N of times it appeared
		);
	}
	// We sort combinations based on times they appeared
	std::sort(comb_pairs.begin(), comb_pairs.end(), compare_best_combinations);
	if (comb_pairs.size() < stt.rg_n_comb) { stt.rg_n_comb = comb_pairs.size(); }
	// Save best exp,fac pairs
	for (size_t i {0}; i < stt.rg_n_comb; i++) {
		stt.cmb_arr.push_back(comb_pairs[i].first);
	}
}

inline void make_dict(double* smp_arr, state& stt) {
	metadata best;
	best.l_bw = CUTTER_DICT_BW;
	best.r_bw = 64;
	for (size_t i {1}; i <= CUT_LIMIT; ++i) {
		stt.r_bw  = 64 - i;
		stt.l_bw  = i;
		auto next = skew(smp_arr, stt);

		//		std::cout << "next : " << next.to_string();
		if (next.get_size() <= best.get_size()) { best = next; }
	}

	/* Best: */
	stt.r_bw = best.r_bw;
	stt.l_bw = best.l_bw;
	get_dict(smp_arr, stt, best);

	std::cerr << "best : " << best.to_string();
}

inline void rowgroup_init(const double* col, size_t col_off, size_t tup_c, double* smp_arr, state& stt) {

	stt.scheme = ALP_PDE;

	/* Sample: */
	sample(col, col_off, tup_c, smp_arr, stt);

	//* HACKY : ALSO decide
	find_topn_combination(smp_arr, stt);
}

inline void cutter_init(double* col, size_t col_off, size_t tup_c, double* smp_arr, state& stt) {
	stt.r_base = 0;
	stt.r_bw   = 0;
	stt.l_base = 0;
	stt.l_bw   = 0;

	/* Sample: */
	sample(col, col_off, tup_c, smp_arr, stt);

	make_dict(smp_arr, stt);
}
} // namespace rowgroup
}} // namespace alp::sampler

// NOLINTEND

#endif
