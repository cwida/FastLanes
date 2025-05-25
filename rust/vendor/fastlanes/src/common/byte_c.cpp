#include "fls/common/byte_c.hpp"
#include "fls/common/assert.hpp" // for FLS_ASSERT_CORRECT_SZ

namespace fastlanes {
void ByteCount::reset() {
	m_c = 0;
}

double operator/(const ByteCount& l, const ByteCount& r) {
	FLS_ASSERT_CORRECT_SZ(l.m_c)
	FLS_ASSERT_CORRECT_SZ(r.m_c)

	return static_cast<double>(l.m_c) / static_cast<double>(r.m_c);
}

n_t operator-(const ByteCount& l, const ByteCount& r) {
	FLS_ASSERT_CORRECT_SZ(l.m_c)
	FLS_ASSERT_CORRECT_SZ(r.m_c)

	return l.m_c - r.m_c;
}

ByteCount::ByteCount(n_t c) {
	FLS_ASSERT_CORRECT_SZ(c)

	m_c = c;
}
n_t ByteCount::Val() const {
	return m_c;
}

bool operator>=(const ByteCount& l, const ByteCount& r) {
	FLS_ASSERT_CORRECT_SZ(l.m_c)
	FLS_ASSERT_CORRECT_SZ(r.m_c)

	return static_cast<bool>(l.m_c >= r.m_c);
}

bool operator<(const ByteCount& l, const ByteCount& r) {
	FLS_ASSERT_CORRECT_SZ(l.m_c)
	FLS_ASSERT_CORRECT_SZ(r.m_c)

	return static_cast<bool>(l.m_c < r.m_c);
}

ByteCount operator+(const ByteCount& l, const ByteCount& r) {
	FLS_ASSERT_CORRECT_SZ(l.m_c)
	FLS_ASSERT_CORRECT_SZ(r.m_c)

	return byte_c {l.m_c + r.m_c};
}

bool operator>(const ByteCount& l, const ByteCount& r) {
	FLS_ASSERT_CORRECT_SZ(l.m_c)
	FLS_ASSERT_CORRECT_SZ(r.m_c)

	return static_cast<bool>(l.m_c > r.m_c);
}

void ByteCount::operator=(ByteCount&& r) noexcept {
	this->m_c = r.m_c;
}

ByteCount::ByteCount(ByteCount& byte_count) {
	this->m_c = byte_count.m_c;
}

ByteCount operator*(const ByteCount& l, const ByteCount& r) {
	FLS_ASSERT_CORRECT_SZ(l.m_c)
	FLS_ASSERT_CORRECT_SZ(r.m_c)

	return byte_c {l.m_c * r.m_c};
}
} // namespace fastlanes