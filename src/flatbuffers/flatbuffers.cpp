#include "fls/flatbuffers/flatbuffers.hpp"
#include "fls/connection.hpp"
#include "fls/footer/table_descriptor.hpp"
#include "fls/io/io.hpp"
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace fastlanes {

n_t WriteBuffer(io& io, const void* buf_ptr, std::size_t buf_size) {

	IO::append(io, static_cast<const char*>(buf_ptr), buf_size);

	return static_cast<n_t>(buf_size);
}

n_t FlatBuffers::Write(io& io, const TableDescriptorT& table_descriptor) {
	// build the FlatBuffer in memory
	flatbuffers::FlatBufferBuilder builder(1024);
	const auto                     tbl_off = TableDescriptor::Pack(builder, &table_descriptor);
	builder.Finish(tbl_off);

	// write it out (will auto-create directories as needed)
	return WriteBuffer(io, builder.GetBufferPointer(), builder.GetSize());
}

} // namespace fastlanes
