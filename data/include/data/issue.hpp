#ifndef DATA_ISSUE_HPP
#define DATA_ISSUE_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using issue_dataset_t = std::array<std::pair<string_view, string_view>, 2>;

class issue {
public:
	static constexpr string_view ISSUE_000 {FLS_CMAKE_SOURCE_DIR "/data/generated/issues/issue_000/"};
	static constexpr string_view ISSUE_001 {FLS_CMAKE_SOURCE_DIR "/data/generated/issues/issue_001/"};

	static constexpr issue_dataset_t dataset = {{
	    {"ISSUE_000", ISSUE_000},
	    {"ISSUE_001", ISSUE_001},
	}};
};

} // namespace fastlanes

#endif // DATA_ISSUE_HPP
