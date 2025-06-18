#ifndef FLS_WRITER_WRITER_HPP
#define FLS_WRITER_WRITER_HPP

#include "fls/common/alias.hpp"
#include "fls/common/double.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Table;
struct RowgroupDescriptorT;
class Connection;
/*--------------------------------------------------------------------------------------------------------------------*/
// struct ColumnBatchBase {
// 	virtual ~ColumnBatchBase()                      = default;
// 	virtual idx_t N() const                         = 0;
// 	virtual void  Apply(class Writer& writer) const = 0;
// };
//
// template <typename GetFn, typename ValidFn>
// struct ColumnBatchImpl : ColumnBatchBase {
// 	size_t  col;
// 	idx_t   count;
// 	GetFn   get;
// 	ValidFn is_valid;
//
// 	ColumnBatchImpl(size_t c, idx_t N, GetFn g, ValidFn v)
// 	    : col(c)
// 	    , count(N)
// 	    , get(std::move(g))
// 	    , is_valid(std::move(v)) {
// 	}
//
// 	idx_t N() const override {
// 		return count;
// 	}
//
// 	void Apply(Writer& writer) const override;
// };
//
// template <typename GetFn, typename ValidFn>
// struct ColumnBatch {
// 	size_t  col;
// 	idx_t   N;
// 	GetFn   get;
// 	ValidFn is_valid;
// };
// template <typename GetFn, typename ValidFn>
// ColumnBatch(size_t, idx_t, GetFn, ValidFn) -> ColumnBatch<GetFn, ValidFn>;
// /*--------------------------------------------------------------------------------------------------------------------*\
//  * Writer
// \*--------------------------------------------------------------------------------------------------------------------*/
// class Writer {
// public:
// 	explicit Writer(const path&                                      dir_path,
// 	                std::vector<std::unique_ptr<ColumnDescriptorT>>& schema,
// 	                Connection&                                      connection);
//
//
// 	template <typename GetFn, typename ValidFn>
// 	void WriteColumn(const ColumnBatch<GetFn, ValidFn>& batch) {
// 		Ingest(row_group->internal_rowgroup[batch.col], batch);
// 	}
//
// 	void WriteBatch(const std::vector<std::unique_ptr<ColumnBatchBase>>& batches) {
// 		FLS_ASSERT_FALSE(batches.empty());
// 		for (auto& b : batches) {
// 			FLS_ASSERT_EQUALITY(b->N(), batches[0]->N());
// 			b->Apply(*this);
// 		}
// 	}
//
// private:
// 	template <typename PT>
// 	PT TypedNull() {
// 		static constexpr i08_pt I08_NULL   = 0;
// 		static constexpr i16_pt I16_NULL   = 0;
// 		static constexpr i32_pt I32_NULL   = 0;
// 		static constexpr i64_pt I64_NULL   = 0;
// 		static constexpr u08_pt U08_NULL   = 0;
// 		static constexpr u16_pt U16_NULL   = 0;
// 		static constexpr u32_pt U32_NULL   = 0;
// 		static constexpr u64_pt U64_NULL   = 0;
// 		static constexpr bol_pt BOOL_NULL  = false;
// 		static constexpr flt_pt FLOAT_NULL = 0.0;
// 		static constexpr dbl_pt DBL_NULL   = 0.0;
// 		static constexpr char   STR_NULL[] = "NULL";
//
// 		if constexpr (std::is_same_v<PT, i08_pt>) {
// 			return I08_NULL;
// 		} else if constexpr (std::is_same_v<PT, i16_pt>) {
// 			return I16_NULL;
// 		} else if constexpr (std::is_same_v<PT, i32_pt>) {
// 			return I32_NULL;
// 		} else if constexpr (std::is_same_v<PT, i64_pt>) {
// 			return I64_NULL;
// 		} else if constexpr (std::is_same_v<PT, u08_pt>) {
// 			return U08_NULL;
// 		} else if constexpr (std::is_same_v<PT, u16_pt>) {
// 			return U16_NULL;
// 		} else if constexpr (std::is_same_v<PT, u32_pt>) {
// 			return U32_NULL;
// 		} else if constexpr (std::is_same_v<PT, u64_pt>) {
// 			return U64_NULL;
// 		} else if constexpr (std::is_same_v<PT, str_pt>) {
// 			return STR_NULL;
// 		} else if constexpr (std::is_same_v<PT, bol_pt>) {
// 			return BOOL_NULL;
// 		} else if constexpr (std::is_same_v<PT, flt_pt>) {
// 			return FLOAT_NULL;
// 		} else if constexpr (std::is_same_v<PT, dbl_pt>) {
// 			return DBL_NULL;
// 		}
//
// 		FLS_UNREACHABLE();
// 	}
//
// 	template <typename PT, typename GetFn, typename ValidFn>
// 	void TypedIngest(TypedCol<PT>& typed_column, const ColumnBatch<GetFn, ValidFn>& batch) {
// 		auto& stats = typed_column.m_stats;
// 		auto& data  = typed_column.data;
// 		auto& nulls = typed_column.null_map_arr;
//
// 		if (typed_column.data.empty()) {
// 			typed_column.m_stats.last_seen_val = TypedNull<PT>();
// 			if constexpr (std::is_same_v<PT, dbl_pt>) {
// 				stats.is_double_castable = true;
// 			}
// 		}
//
// 		const idx_t prev_size = data.size();
// 		data.resize(prev_size + -1);
// 		nulls.resize(prev_size + -1);
//
// 		auto target_ptr = data.data() + prev_size;
// 		auto null_ptr   = nulls.data() + prev_size;
//
// 		PT   min                = stats.min;
// 		PT   max                = stats.max;
// 		auto last_seen_val      = stats.last_seen_val;
// 		auto n_nulls            = stats.n_nulls;
// 		bool is_double_castable = stats.is_double_castable;
//
// 		for (idx_t i = 0; i < -1; i++) {
// 			bool isNull = !batch.is_valid(i);
// 			null_ptr[i] = isNull;
//
// 			if (isNull) {
// 				++n_nulls;
// 				target_ptr[i] = last_seen_val;
// 			} else {
// 				PT value = batch.get(i);
//
// 				target_ptr[i] = value;
// 				last_seen_val = value;
//
// 				min = std::min(min, value);
// 				max = std::max(max, value);
//
// 				if constexpr (std::is_same_v<PT, dbl_pt>) {
// 					if (is_double_castable && !Double::is_safely_castable_to_int64(value)) {
// 						is_double_castable = false;
// 					}
// 				}
// 			}
// 		}
//
// 		stats.min           = min;
// 		stats.max           = max;
// 		stats.last_seen_val = last_seen_val;
// 		stats.n_nulls       = n_nulls;
//
// 		if constexpr (std::is_same_v<PT, dbl_pt>) {
// 			stats.is_double_castable = is_double_castable;
// 		}
// 	}
//
// 	template <typename GetFn, typename ValidFn>
// 	void Ingest(col_pt& col, const ColumnBatch<GetFn, ValidFn>& batch) {
// 		std::visit(overloaded {
// 		               [&]<typename PT>(up<TypedCol<PT>>& typed_column) { TypedIngest<PT>(*typed_column, batch); },
// 		               [&](up<FLSStrColumn>& fls_str_column) {
//
// 		               },
// 		               [](auto&) { FLS_UNREACHABLE(); },
// 		               [](std::monostate&) { FLS_UNREACHABLE(); },
// 		           },
// 		           col);
// 	}
//
// private:
// 	const path&                                      dir_path;
// 	std::vector<std::unique_ptr<ColumnDescriptorT>>& schema;
// 	//! TODO: Support multiple, by making these FIFO queues.
// 	RowgroupDescriptorT descriptor;
// 	up<Rowgroup>        row_group;
//
// 	Connection& connection;
// };
//
// template <typename GetFn, typename ValidFn>
// void ColumnBatchImpl<GetFn, ValidFn>::Apply(Writer& writer) const {
// 	writer.WriteColumn(ColumnBatch<GetFn, ValidFn> {col, count, get, is_valid});
// }

} // namespace fastlanes

#endif // FLS_WRITER_WRITER_HPP
