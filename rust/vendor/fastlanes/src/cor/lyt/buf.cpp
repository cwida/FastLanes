#include "fls/cor/lyt/buf.hpp"
#include "fls/cfg/cfg.hpp"
#include "fls/io/external_memory.hpp"
#include <cstring>
#include <stdexcept>

namespace fastlanes {
static constexpr uint64_t BUF_SZ = 64ULL * 8 * 256 * 1024;

void Buf::init() {
	m_owned_p = new uint8_t[m_capacity];
	// by default, the owned buffer is the active one
	m_active_p = m_owned_p;
}

Buf::Buf()
    : m_capacity {BUF_SZ}
    , m_off {0}
    , m_owned_p(nullptr)
    , m_active_p(nullptr) {
	init();
}

Buf::Buf(const sz_t capacity)
    : m_capacity {capacity}
    , m_off {0}
    , m_owned_p(nullptr)
    , m_active_p(nullptr) {
	init();
}

void Buf::Rewind() {
	/**/
	this->Rewind(0);
}

void Buf::Rewind(const n_t a_off) {
	/**/
	FLS_ASSERT_CORRECT_OFFSET(a_off)

	m_off      = a_off;
	m_active_p = m_owned_p;
}

uint8_t* Buf::mutable_data() const {
	/**/
	return m_active_p;
}

template <typename PT>
PT* Buf::mutable_data() {
	/**/
	return reinterpret_cast<PT*>(m_active_p);
}

void Buf::UnsafeAppend(const void* data_p, const n_t sz) {
	/**/
	FLS_ASSERT_NOT_NULL_POINTER(data_p)
	FLS_ASSERT_CORRECT_SZ(sz)
	FLS_ASSERT_LE(m_off + sz, m_capacity)

	std::memcpy(m_active_p + m_off, data_p, sz);
	m_off += sz;
}

uint8_t* Buf::data() const {
	/**/
	return m_active_p;
}

template <typename PT>
PT* Buf::GetFixedSizeArray(const n_t size) {
	FLS_ASSERT_CORRECT_SZ(size)

	FLS_ASSERT_LE(m_off + size, m_capacity)
	m_off += size;

	return reinterpret_cast<PT*>(m_active_p);
}

template <typename PT>
void Buf::TypedAppend(const PT* data_p) {
	Append(data_p, sizeof(PT));
}

template <typename PT>
const PT* Buf::data() {
	/**/
	return reinterpret_cast<const PT*>(m_active_p);
}

void Buf::Append(const void* data_p, const n_t sz) {
	/**/
	FLS_ASSERT_NOT_NULL_POINTER(data_p)
	FLS_ASSERT_LE(m_off + sz, m_capacity)

	if (m_off + sz > m_capacity) {
		FLS_ABORT("NOT ENOUGH SPACE!")
	}

	std::memcpy(m_active_p + m_off, data_p, sz);
	m_off += sz;
}

n_t Buf::length() const {
	/**/
	return m_off;
}

void Buf::Reserve() { /**/
}

void Buf::Swap(const Buf& a_buf) {
	m_active_p = a_buf.m_active_p;
	m_off      = a_buf.m_off;
}

void Buf::UnsafeAdvance(const n_t byte_c) {
	/**/
	FLS_ASSERT_CORRECT_N(byte_c);

	m_off += byte_c;
}

void Buf::Advance(const n_t byte_c) {
	/**/
	FLS_ASSERT_CORRECT_N(byte_c)

	if (m_off + byte_c > m_capacity) {
		FLS_ABORT("NOT ENOUGH SPACE!")
	}

	m_off += byte_c;
}

Buf::~Buf() {
	/**/
	FLS_ASSERT_NOT_NULL_POINTER(m_owned_p)

	delete[] m_owned_p;
}

uint8_t* Buf::data_at(const n_t a_off) const {
	/**/
	FLS_ASSERT_CORRECT_OFFSET(a_off)

	return m_active_p + a_off;
}

uint8_t* Buf::end() const {
	/**/
	FLS_ASSERT_CORRECT_OFFSET(m_off)

	return m_active_p + m_off;
}

void Buf::Reset() {
	/**/
	m_active_p = m_owned_p;
	m_off      = 0;
}

void Buf::Swap(uint8_t* p) {
	/**/
	m_active_p = p;
	m_off      = 0;
}

void Buf::Resize(const sz_t new_sz) {
	/**/
	FLS_ASSERT_CORRECT_SZ(new_sz)

	if (m_owned_p != m_active_p) {
		throw std::runtime_error("Buffer is already swapped, swapped buffer can be resized.");
	}
	if (new_sz <= m_capacity) {
		return;
	}

	auto* tmp_p = new uint8_t[new_sz];
	ExternalMemory::Copy(tmp_p, m_owned_p, m_capacity);

	delete[] m_owned_p;
	m_owned_p = tmp_p;
}

sz_t Buf::Size() const {
	/**/
	return m_off;
}
span<std::byte> Buf::Span() const {
	const auto res = span<std::byte>(reinterpret_cast<std::byte*>(m_active_p), Size());
	return res;
}

sz_t Buf::Capacity() const {
	/**/
	return m_capacity;
}

void Buf::Clone(const Buf& a_buf) {
	ExternalMemory::Copy(m_owned_p, a_buf.m_active_p, a_buf.m_off);
	m_off      = a_buf.m_off;
	m_active_p = m_owned_p;
}

/*---------------------------------------------------------------------------------------------------------------------\
 * Specialization
\---------------------------------------------------------------------------------------------------------------------*/
template const ofs_t* Buf::data<ofs_t>();
template uint32_t*    Buf::mutable_data<uint32_t>();
template uint64_t*    Buf::mutable_data<uint64_t>();
template uint8_t*     Buf::mutable_data<uint8_t>();
template uint8_t**    Buf::mutable_data<uint8_t*>();

template i64_pt* Buf::GetFixedSizeArray<i64_pt>(n_t length);
template i32_pt* Buf::GetFixedSizeArray<i32_pt>(n_t length);
template i16_pt* Buf::GetFixedSizeArray<i16_pt>(n_t length);
template i08_pt* Buf::GetFixedSizeArray<i08_pt>(n_t length);
template dbl_pt* Buf::GetFixedSizeArray<dbl_pt>(n_t length);
template flt_pt* Buf::GetFixedSizeArray<flt_pt>(n_t length);

template void Buf::TypedAppend(const ofs_t* data_p);

} // namespace fastlanes
