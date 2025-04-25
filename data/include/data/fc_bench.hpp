#ifndef DATA_FC_BENCH_HPP
#define DATA_FC_BENCH_HPP

#include "fls/std/string.hpp"
#include <array>

namespace fastlanes {
using fc_bench_dataset_t = std::array<std::pair<string_view, string_view>, 1>;

class fc_bench {
public:
	static constexpr string_view fc_bench_sample {FASTLANES_DATA_DIR "/fc_bench"};

	static constexpr fc_bench_dataset_t dataset = {{
	    {"fc_bench", fc_bench_sample},
	}};
};
} // namespace fastlanes

#endif // DATA_FC_BENCH_HPP
