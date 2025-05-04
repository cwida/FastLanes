#include "fls/wizard/sampling_layout.hpp"
#include "fls/common/assert.hpp"
#include <algorithm> // min

// ─────────────────────────────────────────────────────────────────────────────────────────────────────────────
// Run-time “sampling layout” mapping
// ─────────────────────────────────────────────────────────────────────────────────────────────────────────────
namespace fastlanes {

// -----------------------------------------------------------------------------
// Runtime “sampling” layout – matches the compile-time pattern for 32 & 64
// and works for every other N as well.
// -----------------------------------------------------------------------------
std::vector<n_t> sampling_layout_dynamic(n_t N) {
	FLS_ASSERT_G(N, 0);

	if (N == 0) {
		return {};
	}
	if (N == 1) {
		return {0};
	}
	if (N == 2) {
		return {0, 1};
	}

	std::vector<n_t> out;
	out.reserve(N);

	std::vector<bool> used(N, false);

	auto push = [&](n_t v) {
		if (!used[v]) {
			out.push_back(v);
			used[v] = true;
		}
	};

	// 1) fixed head -----------------------------------------------------------
	push(0);
	push(N - 1);

	// 2) symmetric pairs around the centre, skipping 1 and 2 ------------------
	for (n_t i = 0;; ++i) {
		bool added = false;
		n_t  left  = (N / 2) - i;     // floor(N/2) – i
		n_t  right = (N / 2) + 1 + i; // floor(N/2) + 1 + i

		if (left > 2 && left < N) {
			push(left);
			added = true;
		}
		if (right > 2 && right < N) {
			push(right);
			added = true;
		}

		if (!added)
			break; // both sides exhausted
	}

	// 3) tail: always {1, 2} in ascending order if present --------------------
	if (N > 1) {
		push(1);
	}
	if (N > 2) {
		push(2);
	}

	// 4) safety net (never hit in practice) -----------------------------------
	for (n_t v = 0; v < N; ++v) {
		push(v);
	}

	return out;
}

} // namespace fastlanes
