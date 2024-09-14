#ifndef DATA_CLICKBENCH_HPP
#define DATA_CLICKBENCH_HPP

#include "fls/std/string.hpp"

namespace fastlanes {

// clang-format off
class clickbench {
public:
	static constexpr string_view hits {FASTLANES_DATA_DIR "/clickbench/hits"}; //NOLINT
            
};
} // namespace fastlanes

#endif // DATA_CLICKBENCH_HPP
