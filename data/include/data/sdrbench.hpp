// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// data/include/data/sdrbench.hpp
// ────────────────────────────────────────────────────────
#ifndef DATA_SDRBENCH_HPP
#define DATA_SDRBENCH_HPP

#include <array>
#include <string>

namespace fastlanes {
using sdrbnech_dataset_t = std::array<std::pair<std::string_view, std::string_view>, 1>;

class sdrbnech {
public:
	static constexpr std::string_view hurricane_isabel {FASTLANES_DATA_DIR "/sdrbench/Hurricane_ISABEL"};

	static constexpr sdrbnech_dataset_t dataset = {{
	    {"hurricane_isabel", hurricane_isabel},
	}};
};
} // namespace fastlanes

#endif // DATA_SDRBENCH_HPP
