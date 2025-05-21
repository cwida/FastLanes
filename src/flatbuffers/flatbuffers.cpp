#include "fls/flatbuffers/flatbuffers.hpp"
#include "fls/connection.hpp"
#include "fls/footer/table_descriptor.hpp"
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace fastlanes {

constexpr std::string_view FOOTER_NAME = "table_descriptor.fbb";

n_t WriteBuffer(const std::filesystem::path& file_path,
                const void*                  buf_ptr,
                std::size_t                  buf_size,
                std::ios_base::openmode      mode = std::ios::binary | std::ios::out) {
	std::ofstream out {file_path, mode};
	if (!out) {
		throw std::runtime_error("Failed to open for writing: " + file_path.string());
	}
	out.write(reinterpret_cast<const char*>(buf_ptr), static_cast<std::streamsize>(buf_size));
	if (!out) {
		throw std::runtime_error("Failed to write buffer to: " + file_path.string());
	}
	return static_cast<n_t>(buf_size);
}

n_t FlatBuffers::Write(const Connection&            conn,
                       const std::filesystem::path& file_path,
                       TableDescriptorT&            table_descriptor) {
	const auto inlined = conn.is_footer_inlined();

	const auto footer_path = inlined ? file_path : (file_path.parent_path() / FOOTER_NAME);
	const auto mode        = std::ios::binary | (inlined ? std::ios::app : std::ios::out);

	// build the FlatBuffer in memory
	flatbuffers::FlatBufferBuilder builder(1024);
	auto                           tbl_off = TableDescriptor::Pack(builder, &table_descriptor);
	builder.Finish(tbl_off);

	// write it out (will auto-create directories as needed)
	return WriteBuffer(footer_path, builder.GetBufferPointer(), builder.GetSize(), mode);
}

} // namespace fastlanes
