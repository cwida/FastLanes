#ifndef FLS_WRITER_ROWGROUP_HPP
#define FLS_WRITER_ROWGROUP_HPP

#include "fls/common/alias.hpp"
#include "fls/cor/lyt/buf.hpp"

namespace fastlanes {

class FileWriter;
class Rowgroup;
struct RowgroupDescriptorT;
struct ColumnWriteView;

// TODO: Currently single use, should we make it multiple use?
class RowGroupWriter {
public:
	explicit RowGroupWriter(FileWriter& file_writer);

	RowGroupWriter(FileWriter& file_writer, Rowgroup& rowgroup);

	~RowGroupWriter();

	void WriteColumn(const ColumnWriteView& view, idx_t col_idx);

	void Finalize();

	void Flush();

private:
	void                    WriteVector(const ColumnWriteView& view, idx_t col_idx);
	[[nodiscard]] Rowgroup& GetRowGroup() const;

private:
	Buf                     buf; // TODO[memory pool]
	FileWriter&             file_writer;
	up<Rowgroup>            owned_rowgroup;
	Rowgroup*               active_rowgroup;
	up<RowgroupDescriptorT> descriptor;
	std::vector<n_t>        n_tuples_per_column;
};

} // namespace fastlanes

#endif // FLS_WRITER_ROWGROUP_HPP