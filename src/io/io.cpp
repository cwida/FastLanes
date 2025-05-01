#include "fls/io/io.hpp"
#include "fls/cor/lyt/buf.hpp"

namespace fastlanes {

void IO::flush(io& io, const Buf& buf) {
	// write the buffer
	visit(overloaded {
	          [&](up<File>& file) { file->Write(buf); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);
}

void IO::append(io& io, const Buf& buf) {
	// write the buffer
	visit(overloaded {
	          [&](up<File>& file) { file->Append(buf); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);
}

void IO::append(io& io, const char* pointer, n_t size) {
	// write the buffer
	visit(overloaded {
	          [&](up<File>& file) { file->Append(pointer, size); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);
}

void IO::read(const io& io, Buf& buf) {
	visit(overloaded {
	          [&](const up<File>& file) { file->Read(buf); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);
}
void IO::range_read(const io& io, Buf& buf, const n_t offset, const n_t size) {
	visit(overloaded {
	          [&](const up<File>& file) { file->ReadRange(buf, offset, size); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);
}

n_t IO::get_size(const io& io) {
	n_t size = 0;
	visit(overloaded {
	          [&](const up<ExternalMemory>& external_memory) { size = external_memory->GetSpan().size(); },
	          [&](const up<File>& file) { size = file->Size(); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);

	return size;
}

template <typename PT>
span<PT> IO::read(const io& io) {
	span<PT> span_result;
	visit(overloaded {
	          [&](const up<ExternalMemory>& memory) {
		          auto memory_span = memory->GetSpan();
		          span_result = span<PT> {reinterpret_cast<PT*>(memory_span.data()), memory_span.size() / sizeof(PT)};
	          },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);
	return span_result;

	// FLS_UNREACHABLE()
}

template span<i64_pt>    IO::read(const io& io);
template span<dbl_pt>    IO::read(const io& io);
template span<std::byte> IO::read(const io& io);

} // namespace fastlanes