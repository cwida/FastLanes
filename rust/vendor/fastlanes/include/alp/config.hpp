#ifndef ALP_CONFIG_HPP
#define ALP_CONFIG_HPP

#include <cstdint>

#ifndef ALP_N_VECTORS_PER_ROWGROUP
#define ALP_N_VECTORS_PER_ROWGROUP 100UL // Default value
#endif

#ifndef ALP_IS_ADAPTIVE_MODE_ENABLED
#define ALP_IS_ADAPTIVE_MODE_ENABLED true // Default value
#endif
/*
 * ALP Configs
 */
namespace alp {

class config {
public:
	/// ALP Vector size (We recommend against changing this; it should be constant)
	static constexpr uint64_t VECTOR_SIZE = 1024;
	/// number of vectors per rowgroup
	static constexpr uint64_t N_VECTORS_PER_ROWGROUP = ALP_N_VECTORS_PER_ROWGROUP;
	/// Rowgroup size
	static constexpr uint64_t ROWGROUP_SIZE = N_VECTORS_PER_ROWGROUP * VECTOR_SIZE;
	/// Vectors from the rowgroup from which to take samples; this will be used to then calculate the jumps
	static constexpr uint64_t ROWGROUP_VECTOR_SAMPLES = 8;
	/// We calculate how many equidistant vector we must jump within a rowgroup
	static constexpr uint64_t ROWGROUP_SAMPLES_JUMP = (ROWGROUP_SIZE / ROWGROUP_VECTOR_SAMPLES) / VECTOR_SIZE;
	/// Values to sample per vector
	static constexpr uint64_t SAMPLES_PER_VECTOR = 32;
	/// Maximum number of combinations obtained from row group sampling
	static constexpr uint64_t MAX_K_COMBINATIONS       = 5;
	static constexpr uint64_t CUTTING_LIMIT            = 16;
	static constexpr uint64_t MAX_RD_DICT_BIT_WIDTH    = 3;
	static constexpr uint64_t MAX_RD_DICTIONARY_SIZE   = (1 << MAX_RD_DICT_BIT_WIDTH);
	static constexpr bool     IS_ADAPTIVE_MODE_ENABLED = ALP_IS_ADAPTIVE_MODE_ENABLED;
};

// Default template, not defined intentionally
template <typename T>
struct inner_t;

// Specialization for float -> uint32_t
template <>
struct inner_t<float> {
	using ut = uint32_t;
	using st = int32_t;
};

// Specialization for double -> uint64_t
template <>
struct inner_t<double> {
	using ut = uint64_t;
	using st = int64_t;
};

} // namespace alp

#endif