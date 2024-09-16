#include "fls/io/io.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/encoder/exp_col_encoder.hpp"

namespace fastlanes {
void IO::flush(io& io, const ExpEncodedCol& expr_encoded_col) {
	// write the buffer
	visit(overloaded {
	          [&](up<ExternalMemory>& memory) { memory->Ingest(*expr_encoded_col.data_buf); },
	          [](auto&) { FLS_UNREACHABLE() },
	      },
	      io);
}

void IO::flush(io& io, const Buf& buf) {
	// write the buffer
	visit(overloaded {
	          [&](up<File>& file) { file->Write(buf); },
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

bsz_t IO::get_size(const io& io) {
	bsz_t size = 0;
	visit(overloaded {
	          [&](const up<ExternalMemory>& external_memory) { size = external_memory->GetSpan().size(); },
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