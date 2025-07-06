#ifndef DATA_EMBEDDING_HPP
#define DATA_EMBEDDING_HPP

#include <array>
#include <string>

namespace fastlanes {
using EMBEDDING_DATASET_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 1>;

class EMBEDDING {
public:
	static constexpr std::string_view N1 {FLS_CMAKE_SOURCE_DIR "/data/embedding/"};
};
} // namespace fastlanes

#endif // DATA_EMBEDDING_HPP
