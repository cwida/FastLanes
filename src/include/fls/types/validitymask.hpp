#ifndef FLS_TYPES_VALIDITYMASK_HPP
#define FLS_TYPES_VALIDITYMASK_HPP

/**
 * @file src/include/fls/types/validitymask.hpp
 * @brief Fixed‑size bitmap interface (implementation moved to validitymask.cpp).
 */

#include "fls/cfg/cfg.hpp"
#include "fls/common/assert.hpp"

namespace fastlanes {
class ValidityMask {
public:
	// ───────────────────────────────────── configuration
	static constexpr n_t BIT_COUNT  = CFG::VEC_SZ;                  ///< Total bits (compile‑time configured).
	static constexpr n_t WORD_BITS  = CFG::ValidityMask::WORD_BITS; ///< Bits per storage word.
	static constexpr n_t WORD_COUNT = BIT_COUNT / WORD_BITS;        ///< Number of words.

	// Derived compile‑time helpers (no magic numbers).
	static constexpr n_t WORD_SHIFT = [] {
		n_t s = 0, v = WORD_BITS;
		while (v > 1) {
			v >>= 1;
			++s;
		}
		return s;
	}();
	static constexpr n_t WORD_MASK = WORD_BITS - 1;

	// ───────────────────────────────────── compile‑time checks
	static_assert((1u << WORD_SHIFT) == WORD_BITS, "WORD_SHIFT must satisfy 1<<WORD_SHIFT == WORD_BITS");
	static_assert(WORD_MASK == WORD_BITS - 1, "WORD_MASK must equal WORD_BITS‑1");
	static_assert(BIT_COUNT % WORD_BITS == 0, "BIT_COUNT must be divisible by WORD_BITS");

private:
	alignas(64) uint64_t m_data[WORD_COUNT] {}; ///< Zero‑initialised storage.

	[[nodiscard]] static constexpr uint64_t bit_mask(n_t bit) noexcept;
	static void                             assert_idx(n_t idx) noexcept;

public:
	// ───────────────────────────────────── ctor
	ValidityMask() noexcept;

	// ───────────────────────────────────── single‑bit ops
	void               set(n_t idx) noexcept;
	void               reset(n_t idx) noexcept;
	void               flip(n_t idx) noexcept;
	[[nodiscard]] bool test(n_t idx) const noexcept;

	// ───────────────────────────────────── bulk ops
	void               clear() noexcept;       ///< Sets all bits to 0.
	void               fill() noexcept;        ///< Sets all bits to 1.
	[[nodiscard]] n_t  count() const noexcept; ///< Population‑count.
	[[nodiscard]] bool any() const noexcept;   ///< True if any bit is 1.
	[[nodiscard]] bool none() const noexcept;  ///< True if all bits are 0.
	[[nodiscard]] bool all() const noexcept;   ///< True if all bits are 1.

	void bit_or(const ValidityMask& other) noexcept;  ///< this |= other
	void bit_and(const ValidityMask& other) noexcept; ///< this &= other
	void bit_xor(const ValidityMask& other) noexcept; ///< this ^= other

	void copy_from(const ValidityMask& other) noexcept; ///< memcpy‑style copy.
};

// ───────────────────────────────────────── namespace‑level checks
static_assert((1ULL << ValidityMask::WORD_SHIFT) == ValidityMask::WORD_BITS, "WORD_SHIFT must match WORD_BITS");
static_assert(ValidityMask::WORD_MASK == ValidityMask::WORD_BITS - 1, "WORD_MASK must equal WORD_BITS‑1");
} // namespace fastlanes

#endif // FLS_TYPES_VALIDITYMASK_HPP
