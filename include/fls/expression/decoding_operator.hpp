#ifndef FLS_EXPRESSION_DECODING_OPERATOR_HPP
#define FLS_EXPRESSION_DECODING_OPERATOR_HPP

#include "fls/reader/segment.hpp"
#include "fls/table/chunk.hpp"

namespace fastlanes {
class ColumnView;
struct InterpreterState;
class RowgroupReader;
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_unffor_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_unffor_opr {
public:
	explicit dec_unffor_opr(const ColumnView& column_view, InterpreterState& state);

public:
	void      PointTo(n_t vec_idx);
	void      Unffor(n_t vec_idx);
	const PT* Data();

public:
	SegmentView bitpacked_segment_view;
	SegmentView bw_segment_view;
	SegmentView base_segment_view;
	alignas(64) PT unffored_data[CFG::VEC_SZ];
};
/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_uncompressed_opr
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
struct dec_uncompressed_opr {
public:
	explicit dec_uncompressed_opr(const ColumnView& column_view, n_t segment_idx);

public:
	void PointTo(n_t vec_n);
	PT*  Data();

public:
	SegmentView data_segment;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * dec_uncompressed_opr
\*--------------------------------------------------------------------------------------------------------------------*/
struct dec_fls_str_uncompressed_opr {
	explicit dec_fls_str_uncompressed_opr(const ColumnView& column_view, const RPNT& rpn);

public:
	void       PointTo(n_t vec_idx);
	std::byte* Data() const;
	len_t*     Length() const;
	n_t*       ByteArrSize();

public:
	SegmentView byte_arr_segment;
	SegmentView length_segment;
};

template <typename PT>
struct dec_constant_opr {
public:
	explicit dec_constant_opr(const ColumnView& column_view);
	PT value;
};

struct dec_constant_str_opr {
public:
	explicit dec_constant_str_opr(const ColumnView& column_view);
	vector<uint8_t> bytes;
};

struct dec_struct_opr {
	dec_struct_opr(const ColumnDescriptorT& column_descriptor,
	               const ColumnView&        column_view,
	               InterpreterState&        state,
	               RowgroupReader&          reader);

	vector<sp<class PhysicalExpr>> internal_exprs;
};

} // namespace fastlanes

#endif // FLS_EXPRESSION_DECODING_OPERATOR_HPP