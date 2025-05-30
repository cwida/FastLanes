#ifndef FLS_IO_EXTERNAL_MEMORY_HPP
#define FLS_IO_EXTERNAL_MEMORY_HPP

#include "fls/common/common.hpp"
#include "fls/std/span.hpp"

namespace fastlanes {
class Buf;

class ExternalMemory {

public:
	template <typename T>
	ExternalMemory(T* pointer, sz_t n_bytes);

public:
	[[nodiscard]] span<std::byte> GetSpan() const;
	void                          Ingest(const Buf& buf);

private:
	span<std::byte> m_data_span;

public:
	static void Write(std::byte*& des_p, std::byte* src_p, n_t bsz);
	static void Copy(std::byte* des_p, std::byte* src_p, n_t bsz);
	static void Copy(void* des_p, void* src_p, n_t bsz);
};

} // namespace fastlanes

#endif // FLS_IO_EXTERNAL_MEMORY_HPP
