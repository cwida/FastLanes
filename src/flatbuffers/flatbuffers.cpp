#include "fls/flatbuffers/flatbuffers.hpp"
#include "fls/footer/table_descriptor.hpp"
#include <fls/connection.hpp>
#include <fls/printer/az_printer.hpp>

namespace fastlanes {

constexpr string_view FOOTER_NAME = "table_descriptor.fbb";

void FlatBuffers::Write(const path& dir_path, TableDescriptorT& data) {
	// Construct the output path, e.g. "<dir_path>/footer.bin"
	const auto file_path = dir_path / FOOTER_NAME;

	// Reserve a bit of headroom to avoid reallocations
	flatbuffers::FlatBufferBuilder builder(1024);

	// Pack your in‐memory TableDescriptorT into the FlatBuffer
	auto table_off = fastlanes::TableDescriptor::Pack(builder, &data);

	// Write the root offset and seal the buffer
	builder.Finish(table_off);

	// Open the file for binary output
	std::ofstream out {file_path, std::ios::binary};
	if (!out) {
		az_printer::cyan_cout << "Failed to open for writing: " << file_path << "\n";
		return;
	}

	// Dump the buffer to disk
	out.write(reinterpret_cast<const char*>(builder.GetBufferPointer()),
	          static_cast<std::streamsize>(builder.GetSize()));
	out.close();

	az_printer::cyan_cout << "FlatBuffer written to " << file_path << "\n";
}

n_t FlatBuffers::Write(const Connection& connection, const path& dir_path, TableDescriptorT& table_descriptor) {
	if (connection.is_footer_inlined()) {

		flatbuffers::FlatBufferBuilder builder(1024);
		auto                           table_off = fastlanes::TableDescriptor::Pack(builder, &table_descriptor);
		builder.Finish(table_off);

		// Append raw bytes to <dir_path>/FASTLANES_FILE_NAME
		const path    fls_path = dir_path / FASTLANES_FILE_NAME;
		std::ofstream out {fls_path, std::ios::binary | std::ios::app};
		if (!out) {
			az_printer::cyan_cout << "Failed to open for appending: " << fls_path << "\n";
			return 0;
		}
		auto buf_ptr = reinterpret_cast<const char*>(builder.GetBufferPointer());
		auto buf_sz  = static_cast<std::streamsize>(builder.GetSize());
		out.write(buf_ptr, buf_sz);
		out.close();

		return static_cast<n_t>(buf_sz);
	}

	// --- Non-inlined: write a standalone FlatBuffer footer.bin ---
	FlatBuffers::Write(dir_path, table_descriptor);

	// Measure the written footer
	const path      footer_path = dir_path / FOOTER_NAME;
	std::error_code ec;
	auto            size = std::filesystem::file_size(footer_path, ec);
	if (ec) {
		az_printer::cyan_cout << "Failed to stat " << footer_path << ": " << ec.message() << "\n";
		return 0;
	}
	return static_cast<n_t>(size);
}

} // namespace fastlanes