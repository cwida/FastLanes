#include "fls/io/external_memory.hpp"
#include "fls/cor/lyt/buf.hpp"
#include <cstring>
#include <stdexcept>

namespace fastlanes {

template <typename T>
ExternalMemory::ExternalMemory(T* pointer, sz_t n_bytes) {
	m_data_span = span<std::byte>(reinterpret_cast<std::byte*>(pointer), n_bytes);
}

template ExternalMemory::ExternalMemory(void* pointer, sz_t n_bytes);
template ExternalMemory::ExternalMemory(i64_pt* pointer, sz_t n_bytes);
template ExternalMemory::ExternalMemory(u64_pt* pointer, sz_t n_bytes);

std::span<std::byte> ExternalMemory::GetSpan() const {
	return m_data_span;
}

void ExternalMemory::Ingest(const Buf& buf) {
	if (buf.Size() > m_data_span.size()) {
		throw std::runtime_error("Memory::Ingest: Buffer too small");
	}

	m_data_span = span<std::byte>(m_data_span.data(), buf.Size());
	std::memcpy(m_data_span.data(), buf.data(), buf.Size()); //
}

void ExternalMemory::Write(std::byte*& des_p, std::byte* src_p, n_t bsz) {

	/**/
	FLS_ASSERT_NOT_NULL_POINTER(des_p)
	FLS_ASSERT_NOT_NULL_POINTER(src_p)
	FLS_ASSERT_CORRECT_SZ(bsz)

	std::memcpy(des_p, src_p, bsz);

	des_p = des_p + bsz;
}

void ExternalMemory::Copy(std::byte* des_p, std::byte* src_p, n_t bsz) {

	/**/
	FLS_ASSERT_NOT_NULL_POINTER(des_p)
	FLS_ASSERT_NOT_NULL_POINTER(src_p)
	FLS_ASSERT_CORRECT_SZ(bsz)

	std::memcpy(des_p, src_p, bsz);
}

void ExternalMemory::Copy(void* des_p, void* src_p, n_t bsz) {
	/**/
	FLS_ASSERT_NOT_NULL_POINTER(des_p)
	FLS_ASSERT_NOT_NULL_POINTER(src_p)
	FLS_ASSERT_CORRECT_SZ(bsz)

	std::memcpy(des_p, src_p, bsz);
}

} // namespace fastlanes