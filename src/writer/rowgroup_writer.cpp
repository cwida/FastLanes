#include "fls/writer/rowgroup_writer.hpp"
#include "fls/encoder/encoder.hpp"
#include "fls/wizard/wizard.hpp"
#include "fls/writer/column_write_view.hpp"
#include "fls/writer/writer.hpp"

namespace fastlanes {

static void fill_in(col_pt& col, const n_t how_many_to_fill) {
	visit(overloaded {
	          [&](const up<FLSStrColumn>& string_col) {
		          const auto last_value_length = string_col->length_arr.back();

		          for (n_t val_idx {0}; val_idx < how_many_to_fill; val_idx++) {
			          const auto size = string_col->byte_arr.size();
			          for (n_t byte_index {last_value_length}; byte_index > 0; byte_index--) {
				          string_col->byte_arr.push_back(string_col->byte_arr[size - byte_index]);
				          string_col->fsst_byte_arr.push_back(string_col->byte_arr[size - byte_index]);
			          }
			          string_col->length_arr.push_back(last_value_length);
			          string_col->fsst_length_arr.push_back(last_value_length);
		          }
	          },
	          [&]<typename PT>(up<TypedCol<PT>>& typed_col) {
		          PT last_element = typed_col->data.back();
		          for (n_t val_idx {0}; val_idx < how_many_to_fill; val_idx++) {
			          typed_col->data.push_back(last_element);
		          }
	          },
	          [&](up<Struct>& struct_col) {},
	          [&](auto& arg) { FLS_UNREACHABLE_WITH_TYPE(arg) },
	      },
	      col);
}

RowGroupWriter::RowGroupWriter(FileWriter& file_writer)
    : file_writer(file_writer) {

	const auto row_group_descriptor = make_unique<RowgroupDescriptorT>();

	std::vector<std::unique_ptr<ColumnDescriptorT>> cds;
	cds.reserve(file_writer.options.schema.size());
	for (const auto& cd : file_writer.options.schema) {
		cds.push_back(make_unique<ColumnDescriptorT>(*cd));
	}
	row_group_descriptor->m_column_descriptors = std::move(cds);
	// TODO: We don't use the max capacity, managed by the writer
	owned_rowgroup  = make_unique<Rowgroup>(*row_group_descriptor, 0);
	active_rowgroup = owned_rowgroup.get();
	n_tuples_per_column.resize(file_writer.options.schema.size());
}

RowGroupWriter::RowGroupWriter(FileWriter& file_writer, Rowgroup& rowgroup)
    : file_writer(file_writer)
    , active_rowgroup(&rowgroup) {

	n_tuples_per_column.resize(rowgroup.ColCount());
	for (auto& column: n_tuples_per_column) {
		column = rowgroup.RowCount();
	}
}

RowGroupWriter::~RowGroupWriter() {
}

void RowGroupWriter::WriteColumn(const ColumnWriteView& view, const idx_t col_idx) {
	WriteVector(view, col_idx);
}

void RowGroupWriter::Finalize() {
	auto& rg = GetRowGroup();

	// Fill in the values up to the used vector size.
	for (n_t col_idx {0}; col_idx < rg.internal_rowgroup.size(); col_idx++) {
		auto&     col_pt   = rg.internal_rowgroup[col_idx];
		const n_t leftover = n_tuples_per_column[col_idx] % file_writer.options.vector_size;
		if (leftover == 0) {
			continue;
		}

		const auto to_fill = file_writer.options.vector_size - leftover;
		fill_in(col_pt, to_fill);
	}

	rg.n_tup = n_tuples_per_column[0];
	rg.Init();
	rg.Cast();
	rg.Finalize();
	rg.GetStatistics();
	descriptor             = make_rowgroup_descriptor(rg);
	descriptor->m_n_vec    = rg.VecCount();
	descriptor->m_n_tuples = rg.RowCount();

	const auto wizard = make_unique<Wizard<FileWriter>>(file_writer);
	wizard->SpellRowGroup(rg.internal_rowgroup, *descriptor);

	Encoder::encode_rowgroup(buf, rg.internal_rowgroup, *descriptor);
}

void RowGroupWriter::Flush() {
	file_writer.FlushRowGroup(buf, std::move(descriptor));
	// TODO (optional): After flushing we create a new row_group so that we can keep reusing the same row_group
};

void RowGroupWriter::WriteVector(const ColumnWriteView& view, const idx_t col_idx) {
	auto& col_variant = GetRowGroup().internal_rowgroup[col_idx];

	ColumnWriteViewVisitor v {};
	view.Accept(col_variant, v);

	n_tuples_per_column[col_idx] += view.Size();
}

Rowgroup& RowGroupWriter::GetRowGroup() const {
	return *active_rowgroup;
}

} // namespace fastlanes