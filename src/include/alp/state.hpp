#ifndef ALP_STATE_HPP
#define ALP_STATE_HPP

#include <unordered_map>
#include <vector>

namespace alp {

enum class Scheme : uint8_t {
	INVALID,
	ALP_RD,
	ALP,
};

template <typename PT>
struct state {
	using UT = typename inner_t<PT>::ut;
	using ST = typename inner_t<PT>::st;

	Scheme   scheme {Scheme::INVALID};
	uint16_t n_exceptions {0};
	uint64_t sampled_values_n {0};

	// ALP
	uint8_t                                  k_combinations {5};
	std::vector<std::pair<uint8_t, uint8_t>> best_k_combinations;
	uint8_t                                  exp {};
	uint8_t                                  fac {};
	bw_t                                     bit_width {};
	ST                                       for_base {};

	// ALP RD
	bw_t                                   right_bit_width {0};
	bw_t                                   left_bit_width {0};
	UT                                     right_for_base {0}; // Always 0
	uint16_t                               left_for_base {0};  // Always 0
	uint16_t                               left_parts_dict[config::MAX_RD_DICTIONARY_SIZE] {};
	uint8_t                                actual_dictionary_size {};
	uint32_t                               actual_dictionary_size_bytes {};
	std::unordered_map<uint16_t, uint16_t> left_parts_dict_map;
};
} // namespace alp

#endif // ALP_STATE_HPP
