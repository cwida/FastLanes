#ifndef FLS_WRITER_WRITERv2_HPP
#define FLS_WRITER_WRITERv2_HPP

#include "fls/common/alias.hpp"
#include "fls/common/double.hpp"
#include "fls/connection.hpp"
#include "fls/std/filesystem.hpp"
#include "fls/table/rowgroup.hpp"

namespace fastlanes {
class Writer;

template <typename PT>
struct DataTypeTraits;

template <>
struct DataTypeTraits<u08_pt> {
	static constexpr DataType value = DataType::UINT8;
	using ColT                      = u08_col_t;
};
template <>
struct DataTypeTraits<u32_pt> {
	static constexpr DataType value = DataType::UINT32;
	using ColT                      = u32_col_t;
};
template <>
struct DataTypeTraits<dbl_pt> {
	static constexpr DataType value = DataType::DOUBLE;
	using ColT                      = dbl_col_t;
};
template <>
struct DataTypeTraits<flt_pt> {
	static constexpr DataType value = DataType::FLOAT;
	using ColT                      = flt_col_t;
};

struct ColumnBatchBase {
	virtual ~ColumnBatchBase()                = default;
	virtual idx_t count() const               = 0;
	virtual void  Write(Writer& writer) const = 0;
};

template <typename F, typename Arg, typename R>
concept CallableR = requires(F f, Arg a) {
	{ f(a) } -> std::same_as<R>;
};

template <typename PT, typename GetFn, typename ValidFn>
    requires CallableR<GetFn, idx_t, PT> && CallableR<ValidFn, idx_t, bool>
struct ColumnBatchImpl : ColumnBatchBase {
	size_t  col_idx;
	idx_t   N;
	GetFn   get;
	ValidFn is_valid;

	ColumnBatchImpl(size_t c, idx_t N, GetFn g, ValidFn v)
	    : col_idx(c)
	    , N(N)
	    , get(std::move(g))
	    , is_valid(std::move(v)) {
	}

	idx_t count() const override {
		return N;
	}
	void Write(Writer& writer) const override;
};

template <typename PT, typename GetFn, typename ValidFn>
    requires CallableR<GetFn, idx_t, PT> && CallableR<ValidFn, idx_t, bool>
struct ColumnBatch {
	size_t  col_idx;
	idx_t   N;
	GetFn   get;
	ValidFn is_valid;
};

class Writer {
public:
	explicit Writer(const path&                                      target_path,
	                std::vector<std::unique_ptr<ColumnDescriptorT>>& schema,
	                Connection&                                      connection);

	template <typename PT, typename GetFn, typename ValidFn>
	void WriteColumn(ColumnBatch<PT, GetFn, ValidFn> batch) {
		auto typed_column = init_logical_column<PT>();

		TypedIngest<PT>(*typed_column, batch);

		row_group->internal_rowgroup[batch.col_idx] =
		    col_pt {std::in_place_type<up<TypedCol<PT>>>, std::move(typed_column)};
	}

	void WriteBatch(const std::vector<std::unique_ptr<ColumnBatchBase>>& batches) {
		FLS_ASSERT_FALSE(batches.empty());
		for (auto& batch : batches) {
			FLS_ASSERT_EQUALITY(batch.count(), batches[0].count())
			batch->Write(*this);
		}
	}

private:
	template <typename PT>
	col_pt init_logical_column(size_t col_idx) {
		if constexpr (std::is_same_v<PT, List>) {
			auto list_col = std::make_unique<List>();
			list_col->child = init_logical_column<>();

			return col_pt{
				std::in_place_type<up<List>>,  // up<List> is unique_ptr<List>
				std::move(list_col)
			  };
		}
		else if constexpr (std::is_same_v<PT, Struct>) {
			auto struct_col = std::make_unique<Struct>();
			// fill struct_col->internal_rowgroup recursively...
			return col_pt{
				std::in_place_type<up<Struct>>,
				std::move(struct_col)
			  };
		}

		// 2) The “normal” leaf‐type case:
		using ColT = typename DataTypeTraits<PT>::ColT;    // e.g. u32_col_t
		using PtrT = up<ColT>;                             // unique_ptr<u32_col_t>

		// construct that alternative in place:
		return col_pt{
			std::in_place_type<PtrT>,
			std::make_unique<ColT>()
		  };
	}

	template <typename PT, typename GetFn, typename ValidFn>
	void TypedIngest(TypedCol<PT>& typed_column, const ColumnBatch<PT, GetFn, ValidFn>& batch) {
		auto& stats = typed_column.m_stats;
		auto& data  = typed_column.data;
		auto& nulls = typed_column.null_map_arr;

		if (typed_column.data.empty()) {
			// typed_column.m_stats.last_seen_val = TypedNull<PT>();
			if constexpr (std::is_same_v<PT, dbl_pt>) {
				stats.is_double_castable = true;
			}
		}

		const idx_t prev_size = data.size();
		data.resize(prev_size + batch.N);
		nulls.resize(prev_size + batch.N);

		auto target_ptr = data.data() + prev_size;
		auto null_ptr   = nulls.data() + prev_size;

		PT   min                = stats.min;
		PT   max                = stats.max;
		auto last_seen_val      = stats.last_seen_val;
		auto n_nulls            = stats.n_nulls;
		bool is_double_castable = stats.is_double_castable;

		for (idx_t i = 0; i < batch.N; i++) {
			bool isNull = !batch.is_valid(i);
			null_ptr[i] = isNull;

			if (isNull) {
				++n_nulls;
				target_ptr[i] = last_seen_val;
			} else {
				PT value = batch.get(i);

				target_ptr[i] = value;
				last_seen_val = value;

				min = std::min(min, value);
				max = std::max(max, value);

				if constexpr (std::is_same_v<PT, dbl_pt>) {
					if (is_double_castable && !Double::is_safely_castable_to_int64(value)) {
						is_double_castable = false;
					}
				}
			}
		}

		stats.min           = min;
		stats.max           = max;
		stats.last_seen_val = last_seen_val;
		stats.n_nulls       = n_nulls;

		if constexpr (std::is_same_v<PT, dbl_pt>) {
			stats.is_double_castable = is_double_castable;
		}
	}

private:
	[[maybe_unused]] const path&                                      target_path;
	[[maybe_unused]] std::vector<std::unique_ptr<ColumnDescriptorT>>& schema;
	[[maybe_unused]] Connection&                                      connection;

	up<Rowgroup> row_group;
};

template <typename PT, typename GetFn, typename ValidFn>
    requires CallableR<GetFn, idx_t, PT> && CallableR<ValidFn, idx_t, bool>
void ColumnBatchImpl<PT, GetFn, ValidFn>::Write(Writer& writer) const {
	writer.WriteColumn(ColumnBatch<PT, GetFn, ValidFn> {col_idx, N, get, is_valid});
}

} // namespace fastlanes

#endif // FLS_WRITER_WRITERv2_HPP