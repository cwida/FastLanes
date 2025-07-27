// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/engine/verification.cuh
// ────────────────────────────────────────────────────────
#ifndef VERIFICATION_H
#define VERIFICATION_H

#include "flsgpu/flsgpu-api.cuh"
#include <cstdint>
#include <cstdio>
#include <type_traits>

namespace verification {

constexpr size_t LOG_N_MISTAKES = 5;

template <typename T>
struct Difference {
	size_t index;
	T      original;
	T      other;

	template <typename U, std::enable_if_t<std::is_integral<U>::value, bool> = true>
	void log() {
		fprintf(stderr,
		        "[%lu] correct: %lu, found: %lu\n",
		        static_cast<uint64_t>(index),
		        static_cast<uint64_t>(original),
		        static_cast<uint64_t>(other));
	}

	template <typename U, std::enable_if_t<std::is_floating_point<U>::value, bool> = true>
	void log() {
		using UINT_T = typename utils::same_width_uint<T>::type;

		UINT_T* original_c = reinterpret_cast<UINT_T*>(&original);
		UINT_T* other_c    = reinterpret_cast<UINT_T*>(&other);

		if (sizeof(U) == 8) {
			fprintf(stderr,
			        "[%lu] correct: %f (%016lX), found: %f (%016lX)\n",
			        index,
			        static_cast<double>(original),
			        static_cast<uint64_t>(*original_c),
			        static_cast<double>(other),
			        static_cast<uint64_t>(*other_c));
		} else {
			fprintf(stderr,
			        "[%lu] correct: %f (%08X), found: %f (%08X)\n",
			        index,
			        static_cast<double>(original),
			        static_cast<uint32_t>(*original_c),
			        static_cast<double>(other),
			        static_cast<uint32_t>(*other_c));
		}
	}
};

template <typename T>
struct ExecutionResult {
	bool                       success;
	std::vector<Difference<T>> differences;
};

template <typename T>
bool byte_compare(const T a, const T b) {
	using UINT_T      = typename utils::same_width_uint<T>::type;
	const UINT_T* a_c = reinterpret_cast<const UINT_T*>(&a);
	const UINT_T* b_c = reinterpret_cast<const UINT_T*>(&b);

	return (*a_c) == (*b_c);
}

template <typename T>
ExecutionResult<T> compare_data(const T* a, const T* b, const size_t size) {
	auto differences = std::vector<Difference<T>>();

	for (size_t i {0}; i < size; ++i) {
		if (!byte_compare(a[i], b[i])) {
			differences.push_back(Difference<T> {i, a[i], b[i]});

			if (differences.size() > LOG_N_MISTAKES) {
				break;
			}
		}
	}

	return ExecutionResult<T> {differences.size() == 0, differences};
}

template <typename T>
int32_t process_results(std::vector<ExecutionResult<T>> results, bool print_debug) {

	int32_t runs_failed = 0;
	for (size_t i {0}; i < results.size(); i++) {
		if (!results[i].success) {
			++runs_failed;

			if (print_debug) {
				fprintf(stderr, "\n Run %lu failed.\n", i);

				for (auto difference : results[i].differences) {
					difference.template log<T>();
				}
			}
		}
	}

	if (print_debug) {
		if (runs_failed == 0) {
			fprintf(stderr, "Compression successful.\n");
		} else {
			fprintf(stderr, "\n[%d/%ld] Runs failed.\n", runs_failed, results.size());
		}
	}

	return runs_failed;
}

} // namespace verification

#endif // VERIFICATION_H
