#ifndef DATA_ISSUE_HPP
#define DATA_ISSUE_HPP

#include "fls/std/string.hpp"

namespace fastlanes {

class Issue {
public:
	static constexpr string_view ISSUE76 {FASTLANES_DATA_DIR "/issue/tables/issue_76/"};
};
} // namespace fastlanes

#endif // DATA_ISSUE_HPP
