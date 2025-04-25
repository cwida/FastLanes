#ifndef DATA_FANNIE_MAE_HPP
#define DATA_FANNIE_MAE_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using fannie_mae_dataset_t = std::array<std::pair<string_view, string_view>, 1>;

class fannie_mae {
public:
	static constexpr string_view table_2024Q3 {FASTLANES_DATA_DIR "/fannie_mae/2024Q3"};

	static constexpr fannie_mae_dataset_t dataset = {{
	    {"table_2024Q3", table_2024Q3},
	}};
};
} // namespace fastlanes

#endif // DATA_FANNIE_MAE_HPP
