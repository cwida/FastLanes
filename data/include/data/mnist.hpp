#ifndef DATA_MNIST_HPP
#define DATA_MNIST_HPP

#include <array>
#include <string>

namespace fastlanes {
using mnist_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 14>;

class mnist {
public:
	static constexpr std::string_view EMNIST_LEFT {FLS_CMAKE_SOURCE_DIR "/data/mnist/emnist/csv/zigzag/all_split/zigzag_left_20"};
	static constexpr std::string_view EMNIST_MID_BAD {FLS_CMAKE_SOURCE_DIR "/data/mnist/emnist/csv/zigzag/all_split/zigzag_mid_24_bad"};
	static constexpr std::string_view EMNIST_MID_MIX_RUN {FLS_CMAKE_SOURCE_DIR "/data/mnist/emnist/csv/zigzag/all_split/zigzag_mid_24_mix_run"};
	static constexpr std::string_view EMNIST_MID_NONZERO {FLS_CMAKE_SOURCE_DIR "/data/mnist/emnist/csv/zigzag/all_split/zigzag_mid_24_nonzero"};
	static constexpr std::string_view EMNIST_RIGHT_MIX_RUN {FLS_CMAKE_SOURCE_DIR "/data/mnist/emnist/csv/zigzag/all_split/zigzag_right_20_mix_run"};
	static constexpr std::string_view EMNIST_RIGHT_NONZERO {FLS_CMAKE_SOURCE_DIR "/data/mnist/emnist/csv/zigzag/all_split/zigzag_right_20_nonzero"};
	static constexpr std::string_view EMNIST_ORIGINAL {FLS_CMAKE_SOURCE_DIR "/data/mnist/emnist/csv/zigzag/zigzag_split/original"};
	
	
	static constexpr std::string_view FASHION_MNIST_LEFT {FLS_CMAKE_SOURCE_DIR "/data/mnist/fashion-mnist/csv/zigzag/all_split/zigzag_left_21"};
	static constexpr std::string_view FASHION_MNIST_MID_BAD {FLS_CMAKE_SOURCE_DIR "/data/mnist/fashion-mnist/csv/zigzag/all_split/zigzag_mid_24_bad"};
	static constexpr std::string_view FASHION_MNIST_MID_MIX_RUN {FLS_CMAKE_SOURCE_DIR "/data/mnist/fashion-mnist/csv/zigzag/all_split/zigzag_mid_24_mix_run"};
	static constexpr std::string_view FASHION_MNIST_MID_NONZERO {FLS_CMAKE_SOURCE_DIR "/data/mnist/fashion-mnist/csv/zigzag/all_split/zigzag_mid_24_nonzero"};
	static constexpr std::string_view FASHION_MNIST_RIGHT_MIX_RUN {FLS_CMAKE_SOURCE_DIR "/data/mnist/fashion-mnist/csv/zigzag/all_split/zigzag_right_19_mix_run"};
	static constexpr std::string_view FASHION_MNIST_RIGHT_NONZERO {FLS_CMAKE_SOURCE_DIR "/data/mnist/fashion-mnist/csv/zigzag/all_split/zigzag_right_19_nonzero"};
	static constexpr std::string_view FASHION_MNIST_ORIGINAL {FLS_CMAKE_SOURCE_DIR "/data/mnist/fashion-mnist/csv/zigzag/zigzag_split/original"};

	static constexpr mnist_dataset_t dataset = {{
	    {"EMNIST_LEFT", EMNIST_LEFT},
	    {"EMNIST_MID_BAD", EMNIST_MID_BAD},
	    {"EMNIST_MID_MIX_RUN", EMNIST_MID_MIX_RUN},
	    {"EMNIST_MID_NONZERO", EMNIST_MID_NONZERO},
	    {"EMNIST_RIGHT_MIX_RUN", EMNIST_RIGHT_MIX_RUN},
	    {"EMNIST_RIGHT_NONZERO", EMNIST_RIGHT_NONZERO},
	    {"EMNIST_ORIGINAL", EMNIST_ORIGINAL},

	    {"FASHION_MNIST_LEFT", FASHION_MNIST_LEFT},
	    {"FASHION_MNIST_MID_BAD", FASHION_MNIST_MID_BAD},
	    {"FASHION_MNIST_MID_MIX_RUN", FASHION_MNIST_MID_MIX_RUN},
	    {"FASHION_MNIST_MID_NONZERO", FASHION_MNIST_MID_NONZERO},
	    {"FASHION_MNIST_RIGHT_MIX_RUN", FASHION_MNIST_RIGHT_MIX_RUN},
	    {"FASHION_MNIST_RIGHT_NONZERO", FASHION_MNIST_RIGHT_NONZERO},
	    {"FASHION_MNIST_ORIGINAL", FASHION_MNIST_ORIGINAL}
	}};
};
} // namespace fastlanes

#endif // DATA_MNIST_HPP
