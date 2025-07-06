#ifndef DATA_EXAMPLE_HPP
#define DATA_EXAMPLE_HPP

#include <array>
#include <string>

namespace fastlanes {
using EXAMPLE_DATASET_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 1>;

class EXAMPLE {
public:
	static constexpr std::string_view N1 {FLS_CMAKE_SOURCE_DIR "/data/example/"};
};
} // namespace fastlanes

#endif // DATA_EXAMPLE_HPP
