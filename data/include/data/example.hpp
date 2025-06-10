#ifndef DATA_EXAMPLE_HPP
#define DATA_EXAMPLE_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using EXAMPLE_DATASET_dataset_t = std::array<std::pair<string_view, string_view>, 1>;

class EXAMPLE {
public:
	static constexpr string_view N1 {FLS_CMAKE_SOURCE_DIR "/data/example/"};
};
} // namespace fastlanes

#endif // DATA_EXAMPLE_HPP
