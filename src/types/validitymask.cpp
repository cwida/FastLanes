#include "fls/types/validitymask.hpp"
#include "fls/common/assert.hpp"
#include <bit>     // std::popcount (C++20)
#include <cstring> // std::memset / memcpy

namespace fastlanes {

// ───────────────────────────────────────── internal helpers
constexpr uint64_t ValidityMask::bit_mask(n_t bit) noexcept {
	return uint64_t {1u} << bit;
}

void ValidityMask::assert_idx(n_t idx) noexcept {
	FLS_ASSERT_CORRECT_VEC_INDEX(idx);
}

// ───────────────────────────────────────── ctor
ValidityMask::ValidityMask() noexcept {
	clear(); // zero-initialise (redundant but explicit)
}

// ───────────────────────────────────────── single‑bit ops
void ValidityMask::set(n_t idx) noexcept {
	assert_idx(idx);
	m_data[idx >> WORD_SHIFT] |= bit_mask(idx & WORD_MASK);
}

void ValidityMask::reset(n_t idx) noexcept {
	assert_idx(idx);
	m_data[idx >> WORD_SHIFT] &= ~bit_mask(idx & WORD_MASK);
}

void ValidityMask::flip(n_t idx) noexcept {
	assert_idx(idx);
	m_data[idx >> WORD_SHIFT] ^= bit_mask(idx & WORD_MASK);
}

bool ValidityMask::test(n_t idx) const noexcept {
	assert_idx(idx);
	return (m_data[idx >> WORD_SHIFT] >> (idx & WORD_MASK)) & 1u;
}

// ───────────────────────────────────────── bulk ops
void ValidityMask::clear() noexcept {
	std::memset(m_data, 0, sizeof(m_data));
}

void ValidityMask::fill() noexcept {
	std::memset(m_data, 0xFF, sizeof(m_data));
}

n_t ValidityMask::count() const noexcept {
	n_t total = 0;
	for (uint64_t w : m_data) {
		total += static_cast<n_t>(std::popcount(w));
	}
	return total;
}

bool ValidityMask::any() const noexcept {
	for (uint64_t w : m_data) {
		if (w != 0)
			return true;
	}
	return false;
}

bool ValidityMask::none() const noexcept {
	return !any();
}

bool ValidityMask::all() const noexcept {
	for (uint64_t w : m_data) {
		if (w != ~uint64_t(0))
			return false;
	}
	return true;
}

// ───────────────────────────────────────── bitwise ops
void ValidityMask::bit_or(const ValidityMask& other) noexcept {
	for (n_t i = 0; i < WORD_COUNT; ++i) {
		m_data[i] |= other.m_data[i];
	}
}

void ValidityMask::bit_and(const ValidityMask& other) noexcept {
	for (n_t i = 0; i < WORD_COUNT; ++i) {
		m_data[i] &= other.m_data[i];
	}
}

void ValidityMask::bit_xor(const ValidityMask& other) noexcept {
	for (n_t i = 0; i < WORD_COUNT; ++i) {
		m_data[i] ^= other.m_data[i];
	}
}

// ───────────────────────────────────────── copy
void ValidityMask::copy_from(const ValidityMask& other) noexcept {
	std::memcpy(m_data, other.m_data, sizeof(m_data));
}

// ───────────────────────────────────────── ingest dense byte-vector
void ValidityMask::encode(const uint8_t* bytes) noexcept {
	for (n_t word = 0; word < WORD_COUNT; ++word) {
		uint64_t       w     = 0;
		const uint8_t* block = bytes + word * WORD_BITS; // 64 bytes per word
		for (n_t bit = 0; bit < WORD_BITS; ++bit) {
			if (block[bit])
				w |= (uint64_t {1} << bit);
		}
		m_data[word] = w;
	}
}

// ───────────────────────────────────────── static decode helper
void ValidityMask::decode(const uint64_t* words, uint8_t* bytes) noexcept {
	FLS_ASSERT_NOT_NULL_POINTER(words);
	FLS_ASSERT_NOT_NULL_POINTER(bytes);

	for (n_t word = 0; word < WORD_COUNT; ++word) {
		uint64_t w     = words[word];
		uint8_t* block = bytes + word * WORD_BITS; // 64 bytes per word
		for (n_t bit = 0; bit < WORD_BITS; ++bit)
			block[bit] = static_cast<uint8_t>((w >> bit) & 1u); // 0 or **1**
	}
}

// ───────────────────────────────────────── non-static delegating overload
void ValidityMask::decode(uint8_t* bytes) const noexcept {
	// Re-use the static helper on our own storage
	decode(m_data, bytes);
}

uint64_t* ValidityMask::data() noexcept {
	return m_data;
}
const uint64_t* ValidityMask::data() const noexcept {
	return m_data;
}

} // namespace fastlanes
