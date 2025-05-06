#ifndef DATA_ISSUES_HPP
#define DATA_ISSUES_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using issues_dataset_t = std::array<std::pair<string_view, string_view>, 2>;

class issues {
public:
	static constexpr string_view issues_cwida_alp_37_kv_cache_original {FASTLANES_DATA_DIR
	                                                                    "/issues/cwida/alp/37/kv_cache_original"};
	static constexpr string_view issues_cwida_alp_37_diff_data {FASTLANES_DATA_DIR "/issues/cwida/alp/37/diff_data"};

	static constexpr issues_dataset_t dataset = {{
	    {"issues_cwida_alp_37_kv_cache_original", issues_cwida_alp_37_kv_cache_original},
	    {"issues_cwida_alp_37_diff_data", issues_cwida_alp_37_diff_data},

	}};
};
} // namespace fastlanes

#endif // DATA_ISSUES_HPP
