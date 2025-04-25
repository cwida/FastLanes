#ifndef DATA_SDRBENCH_HPP
#define DATA_SDRBENCH_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using sdrbnech_dataset_t = std::array<std::pair<string_view, string_view>, 1>;

class sdrbnech {
public:
	static constexpr string_view hurricane_isabel {FASTLANES_DATA_DIR "/sdrbench/Hurricane_ISABEL"};

	static constexpr sdrbnech_dataset_t dataset = {{
	    {"hurricane_isabel", hurricane_isabel},
	}};
};
} // namespace fastlanes

#endif // DATA_SDRBENCH_HPP
