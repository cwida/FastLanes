#ifndef DATA_ISSUES_HPP
#define DATA_ISSUES_HPP

#include <array>
#include <string>

namespace fastlanes {
using issues_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 3>;

class issues {
public:
	static constexpr std::string_view issues_cwida_alp_37_kv_cache_original {FASTLANES_DATA_DIR
	                                                                         "/issues/cwida/alp/37/kv_cache_original"};
	static constexpr std::string_view issues_cwida_alp_37_diff_data {FASTLANES_DATA_DIR
	                                                                 "/issues/cwida/alp/37/diff_data"};
	static constexpr std::string_view ISSUE_000 {FLS_CMAKE_SOURCE_DIR "/data/issues/issue_000/"};
	//
	static constexpr issues_dataset_t dataset = {{
	    {"issues_cwida_alp_37_kv_cache_original", issues_cwida_alp_37_kv_cache_original},
	    {"issues_cwida_alp_37_diff_data", issues_cwida_alp_37_diff_data},
	    {"ISSUE_000", ISSUE_000},
	}};
};
} // namespace fastlanes

#endif // DATA_ISSUES_HPP
