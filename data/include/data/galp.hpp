// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// data/include/data/galp.hpp
// ────────────────────────────────────────────────────────
#ifndef DATA_GALP_HPP
#define DATA_GALP_HPP

#include <array>
#include <string_view>

namespace fastlanes {

using galp_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 12>;

class galp {
public:
	// FLOAT precision
	static constexpr std::string_view float_galp_one_vector {FLS_CMAKE_SOURCE_DIR
	                                                         "/data/generated/galp/float/galp/one_vector"};
	static constexpr std::string_view float_galp_single_column {FLS_CMAKE_SOURCE_DIR
	                                                            "/data/generated/galp/float/galp/single_column"};

	static constexpr std::string_view float_constant_one_vector {FLS_CMAKE_SOURCE_DIR
	                                                             "/data/generated/galp/float/constant/one_vector"};
	static constexpr std::string_view float_constant_single_column {
	    FLS_CMAKE_SOURCE_DIR "/data/generated/galp/float/constant/single_column"};

	static constexpr std::string_view float_positive_inf_one_vector {
	    FLS_CMAKE_SOURCE_DIR "/data/generated/galp/float/positive_inf/one_vector"};
	static constexpr std::string_view float_positive_inf_single_column {
	    FLS_CMAKE_SOURCE_DIR "/data/generated/galp/float/positive_inf/single_column"};

	// DOUBLE precision
	static constexpr std::string_view double_galp_one_vector {FLS_CMAKE_SOURCE_DIR
	                                                          "/data/generated/galp/double/galp/one_vector"};
	static constexpr std::string_view double_galp_single_column {FLS_CMAKE_SOURCE_DIR
	                                                             "/data/generated/galp/double/galp/single_column"};

	static constexpr std::string_view double_constant_one_vector {FLS_CMAKE_SOURCE_DIR
	                                                              "/data/generated/galp/double/constant/one_vector"};
	static constexpr std::string_view double_constant_single_column {
	    FLS_CMAKE_SOURCE_DIR "/data/generated/galp/double/constant/single_column"};

	static constexpr std::string_view double_positive_inf_one_vector {
	    FLS_CMAKE_SOURCE_DIR "/data/generated/galp/double/positive_inf/one_vector"};
	static constexpr std::string_view double_positive_inf_single_column {
	    FLS_CMAKE_SOURCE_DIR "/data/generated/galp/double/positive_inf/single_column"};

	static constexpr galp_dataset_t dataset {
	    {// Float entries
	     {"float_galp_one_vector", float_galp_one_vector},
	     {"float_galp_single_column", float_galp_single_column},
	     {"float_constant_one_vector", float_constant_one_vector},
	     {"float_constant_single_column", float_constant_single_column},
	     {"float_positive_inf_one_vector", float_positive_inf_one_vector},
	     {"float_positive_inf_single_column", float_positive_inf_single_column},
	     // Double entries
	     {"double_galp_one_vector", double_galp_one_vector},
	     {"double_galp_single_column", double_galp_single_column},
	     {"double_constant_one_vector", double_constant_one_vector},
	     {"double_constant_single_column", double_constant_single_column},
	     {"double_positive_inf_one_vector", double_positive_inf_one_vector},
	     {"double_positive_inf_single_column", double_positive_inf_single_column}}};
};

} // namespace fastlanes

#endif // DATA_GALP_HPP
