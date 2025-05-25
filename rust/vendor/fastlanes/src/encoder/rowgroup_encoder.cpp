#include "fls/encoder/rowgroup_encoder.hpp"
#include "fls/connection.hpp"                            // for Connector
#include "fls/cor/exp/exp_pool.hpp"                      // for Expression
#include "fls/cor/exp/exp_type.hpp"                      // for ExpT
#include "fls/cor/exp/uncompressed/uncompressed_exp.hpp" // for uncompresse...
#include "fls/encoder/exp_col_encoder.hpp"               // for ExpColEncoder
#include "fls/footer/rowgroup_footer.hpp"                // for Schema
#include "fls/reader/segment.hpp"
#include "fls/std/variant.hpp" // for overloaded
#include <memory>              // for make_unique
#include <stdexcept>           // for runtime_error
#include <stdint.h>            // for uint8_t
#include <string>              // for basic_string
#include <variant>             // for visit, variant

namespace fastlanes {

// TODO [LQ_DEADLINE]
AllExpEncodedCol empty_col_result() {
	AllExpEncodedCol res {};
	res.exp_result_vec.emplace_back(
	    ExpEncodedCol {{static_cast<uint8_t>(uncompressed_exp::var_t::UNCOMPRESSED), ExpT::UNCOMPRESSED}, 0});
	return res;
}

AllExpEncodedCol RowgroupEncoder::encode_all(const col_pt& col, const ColumnDescriptor& column_descriptor) const {
	const auto type = column_descriptor.data_type;
	if (type == DataType::FALLBACK) {
		return {};
	}

	// TODO [LQ_DEADLINE]
	AllExpEncodedCol result = std::visit( //
	    overloaded {
	        [](const auto&) -> AllExpEncodedCol { throw std::runtime_error("NOT SUPPORTED"); },
	        [&](const up<TypedCol<dbl_pt>>& column) {
		        if (column->data.empty()) {
			        return empty_col_result();
		        } // TODO [LQ_DEADLINE]
		        return dbl_tester_up->Encode(column->data);
	        },
	        [&](const up<TypedCol<i64_pt>>& column) {
		        if (column->data.empty()) {
			        return empty_col_result();
		        } // TODO [LQ_DEADLINE]
		        return i64_tester_up->Encode(column->data);
	        },
	        [&](const up<TypedCol<str_pt>>& column) {
		        if (column->data.empty()) {
			        return empty_col_result();
		        } // TODO [LQ_DEADLINE]
		        return str_tester_up->Encode(column->data);
	        },
	        [&](const up<Struct>& struct_col) {
		        const auto res = encode(struct_col->internal_rowgroup, column_descriptor.children);
		        // Returning the first subcolumn of the struct
		        return *res.col_result_vec.begin();
	        },
	        [&](const up<List>& list_col) {
		        RowgroupEncodingResult res;
		        auto                   col_result = encode_all(
                    list_col->child, type == DataType::MAP ? column_descriptor : column_descriptor.children.front());
		        res.col_result_vec.push_back(col_result);
		        // TODO [TYPE]
		        const vector<i64_pt> offsets_i64 = {list_col->ofs_arr.begin(), list_col->ofs_arr.end()};
		        return i64_tester_up->Encode(offsets_i64);
	        },
	    },
	    col);

	result.col_idx = column_descriptor.idx;

	return result;
}

RowgroupEncoder::RowgroupEncoder(bool verify)
    : m_verify(verify) {
	i64_tester_up = std::make_unique<ExpColEncoder<i64_pt>>(m_verify);
	str_tester_up = std::make_unique<ExpColEncoder<str_pt>>(m_verify);
	dbl_tester_up = std::make_unique<ExpColEncoder<dbl_pt>>(m_verify);
}

void RowgroupEncoder::Encode(Connection& fls) const {
	//
	fls.m_encoding_result = make_unique<RowgroupEncodingResult>(encode(fls.rowgroup(), *fls.m_rowgroup_footer));
}

RowgroupEncodingResult RowgroupEncoder::encode(const rowgroup_pt&       table,
                                               const ColumnDescriptors& col_descriptions) const {
	RowgroupEncodingResult table_compression_res;

	for (const auto& col_description : col_descriptions) {
		auto col_compression_res = encode_all(table[col_description.idx], col_description);
		table_compression_res.col_result_vec.push_back(col_compression_res);
	}
	return table_compression_res;
}

RowgroupEncodingResult RowgroupEncoder::encode(const Rowgroup& rowgroup, const Footer& footer) const {

	return encode(rowgroup.internal_rowgroup, rowgroup.m_footer.m_column_descriptors);
}

} // namespace fastlanes