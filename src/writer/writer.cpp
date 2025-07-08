#include "fls/writer/writer.hpp"
#include "fls/file/file_footer.hpp"
#include "fls/file/file_header.hpp"
#include "fls/flatbuffers/flatbuffers.hpp"
#include "fls/footer/table_descriptor_generated.h"
#include "fls/info.hpp"
#include "fls/writer/rowgroup_writer.hpp"

namespace fastlanes {

FileWriter::FileWriter(WriterOptions&& opts)
    : options(std::move(opts)) {

    };

void FileWriter::Open() {
	table_descriptor = make_unique<TableDescriptorT>();
	n_row_groups     = 0;
	cur_file_offset  = 0;

	io_target = make_unique<File>(options.file_path);
	io_footer = make_unique<File>(options.file_path.parent_path() / FOOTER_NAME);

	FileHeader::Write(io_target, options.inlined_footer);
	cur_file_offset = sizeof(FileHeader);
};

void FileWriter::Close() {
	table_descriptor->m_table_binary_size = cur_file_offset;

	WriteFooter();
};

up<RowGroupWriter> FileWriter::CreateRowGroupWriter() {
	return make_unique<RowGroupWriter>(*this);
}

void FileWriter::WriteFooter() {
	if (options.inlined_footer) {
		const n_t        table_descriptor_size = FlatBuffers::Write(io_target, *table_descriptor);
		const FileFooter file_footer {
		    table_descriptor->m_table_binary_size, table_descriptor_size, Info::get_magic_bytes()};

		FileFooter::Write(io_target, file_footer);
	} else {
		const n_t        table_descriptor_size = FlatBuffers::Write(io_footer, *table_descriptor);
		const FileFooter file_footer {
		    table_descriptor->m_table_binary_size, table_descriptor_size, Info::get_magic_bytes()};

		FileFooter::Write(io_footer, file_footer);
	}
}

void FileWriter::FlushRowGroup(const Buf& buf, up<RowgroupDescriptorT>&& descriptor) {
	std::lock_guard<std::mutex> glock(flush_lock);

	IO::append(io_target, buf);

	descriptor->m_offset = cur_file_offset;
	cur_file_offset += descriptor->m_size;
	n_row_groups++;

	table_descriptor->m_rowgroup_descriptors.push_back(std::move(descriptor));
}

} // namespace fastlanes
