#include "fls/common/double.hpp"
#include "fls/std/variant.hpp"
#include "fls/table/rowgroup.hpp"
#include "fls/writer/writerv2.hpp"

namespace fastlanes {

// template <typename PT>
// void TypedIngest(TypedCol<PT>& typed_column, Vector& src) {
// 	auto& stats = typed_column.m_stats;
// 	auto& data  = typed_column.data;
// 	auto& nulls = typed_column.null_map_arr;
//
// 	if (typed_column.data.empty()) {
// 		typed_column.m_stats.last_seen_val = TypedNull<PT>();
// 		if constexpr (std::is_same_v<PT, dbl_pt>) {
// 			stats.is_double_castable = true;
// 		}
// 	}
//
// 	const idx_t prev_size = data.size();
// 	data.resize(prev_size + -1);
// 	nulls.resize(prev_size + -1);
//
// 	auto target_ptr = data.data() + prev_size;
// 	auto null_ptr   = nulls.data() + prev_size;
//
// 	PT   min                = stats.min;
// 	PT   max                = stats.max;
// 	auto last_seen_val      = stats.last_seen_val;
// 	auto n_nulls            = stats.n_nulls;
// 	bool is_double_castable = stats.is_double_castable;
//
// 	for (idx_t i = 0; i < -1; i++) {
// 		idx_t idx    = vdata.sel->get_index(i);
// 		bool  isNull = !vdata.validity.RowIsValid(idx);
//
// 		null_ptr[i] = isNull;
// 		if (isNull) {
// 			++n_nulls;
// 			target_ptr[i] = last_seen_val;
// 		} else {
// 			PT value      = src_ptr[idx];
// 			target_ptr[i] = value;
// 			last_seen_val = value;
//
// 			min = std::min(min, value);
// 			max = std::max(max, value);
//
// 			if constexpr (std::is_same_v<PT, dbl_pt>) {
// 				if (is_double_castable && !Double::is_safely_castable_to_int64(value)) {
// 					is_double_castable = false;
// 				}
// 			}
// 		}
// 	}
//
// 	stats.min           = min;
// 	stats.max           = max;
// 	stats.last_seen_val = last_seen_val;
// 	stats.n_nulls       = n_nulls;
//
// 	if constexpr (std::is_same_v<PT, dbl_pt>) {
// 		stats.is_double_castable = is_double_castable;
// 	}
// }

// void Writer::Ingest(col_pt& col, Vector& src) {
// 	std::visit(overloaded {
// 	               [&]<typename PT>(up<TypedCol<PT>>& typed_column) { TypedIngest<PT>(*typed_column, src); },
// 	               [&](up<FLSStrColumn>& fls_str_column) {
//
// 	               },
// 	               [](auto&) { FLS_UNREACHABLE(); },
// 	               [](std::monostate&) { FLS_UNREACHABLE(); },
// 	           },
// 	           col);
// }

// Writer::Writer(const path& dir_path, std::vector<std::unique_ptr<ColumnDescriptorT>>& schema, Connection& connection)
//     : dir_path(dir_path)
//     , schema(schema)
//     , connection(connection) {
// 	row_group = make_unique<Rowgroup>(descriptor, connection);
// }

Writer::Writer(const path& target_path, std::vector<std::unique_ptr<ColumnDescriptorT>>& schema, Connection& connection)
    : target_path(target_path)
    , schema(schema)
    , connection(connection) {
}

} // namespace fastlanes
