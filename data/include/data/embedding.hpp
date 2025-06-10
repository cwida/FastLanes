#ifndef DATA_EMBEDDING_HPP
#define DATA_EMBEDDING_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using EMBEDDING_DATASET_dataset_t = std::array<std::pair<string_view, string_view>, 1>;

class EMBEDDING {
public:
	static constexpr string_view N1 {FLS_CMAKE_SOURCE_DIR "/data/embedding/"};
};
} // namespace fastlanes

#endif // DATA_EMBEDDING_HPP
