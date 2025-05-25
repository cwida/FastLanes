#include "fls/expression/physical_expression.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/expression/alp_expression.hpp"
#include "fls/expression/analyze_operator.hpp"
#include "fls/expression/cross_rle_operator.hpp"
#include "fls/expression/decoding_operator.hpp"
#include "fls/expression/dict_expression.hpp"
#include "fls/expression/encoding_operator.hpp"
#include "fls/expression/frequency_operator.hpp"
#include "fls/expression/fsst12_dict_operator.hpp"
#include "fls/expression/fsst12_expression.hpp"
#include "fls/expression/fsst_dict_operator.hpp"
#include "fls/expression/fsst_expression.hpp"
#include "fls/expression/null_operator.hpp"
#include "fls/expression/rle_expression.hpp"
#include "fls/expression/rsum_operator.hpp"
#include "fls/expression/scan_operator.hpp"
#include "fls/expression/slpatch_operator.hpp"
#include "fls/expression/transpose_operator.hpp"
#include "fls/reader/segment.hpp"

namespace fastlanes {

struct point_to_visitor {
	explicit point_to_visitor(const n_t vec_n)
	    : vec_idx(vec_n) {};

	//
	void operator()(const sp<PhysicalExpr>& opr) {
	}

	// encoding
	template <typename PT>
	void operator()(const sp<enc_uncompressed_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<enc_fls_str_uncompressed_op>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<enc_struct_opr>& opr) {
		for (const auto& child_opr : opr->internal_exprs) {
			child_opr->PointTo(vec_idx);
		}
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_dict_map_opr<KEY_PT, INDEX_PT>>& opr) {
		opr->PointTo(vec_idx);
	}

	template <typename PT>
	void operator()(const sp<enc_ffor_opr<PT>>& opr) {
	}

	template <typename PT>
	void operator()(const sp<enc_scan_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}

	// decoding
	template <typename PT>
	void operator()(const sp<dec_uncompressed_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	template <typename PT>
	void operator()(const sp<dec_unffor_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}

	template <typename PT>
	void operator()(const sp<enc_alp_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}

	template <typename PT>
	void operator()(const sp<dec_constant_opr<PT>>& opr) {
	}
	void operator()(const sp<dec_constant_str_opr>& opr) {
	}

	void operator()(const sp<dec_struct_opr>& opr) {
		for (const auto& child_opr : opr->internal_exprs) {
			child_opr->PointTo(vec_idx);
		}
	}
	void operator()(const sp<dec_fls_str_uncompressed_opr>& opr) {
		opr->PointTo(vec_idx);
	}

	template <typename PT>
	void operator()(const sp<enc_alp_rd_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}

	template <typename PT>
	void operator()(const sp<dec_alp_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}

	template <typename PT>
	void operator()(const sp<dec_alp_rd_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}

	// DICT
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<dec_dict_opr<KEY_PT, INDEX_PT>>& opr) {
	}
	template <typename KEY_PT>
	void operator()(const sp<enc_dict_opr<KEY_PT>>& opr) {
	}

	// FSST
	void operator()(const sp<dec_fsst_opr>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<enc_fsst_opr>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<dec_fsst12_opr>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<enc_fsst12_opr>& opr) {
		opr->PointTo(vec_idx);
	}
	// DICT FSST
	void operator()(const sp<enc_fsst_dict_opr>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<enc_fsst12_dict_opr>& opr) {
		opr->PointTo(vec_idx);
	}

	template <typename INDEX_PT>
	void operator()(const sp<dec_fsst_dict_opr<INDEX_PT>>& opr) {
	}
	template <typename INDEX_PT>
	void operator()(const sp<dec_fsst12_dict_opr<INDEX_PT>>& opr) {
	}
	// RLE
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<dec_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	// TRANSPOSE
	template <typename PT>
	void operator()(const sp<enc_transpose_opr<PT>>& opr) {
	}

	// RSUM
	template <typename PT>
	void operator()(const sp<enc_rsum_opr<PT>>& opr) {
	}
	template <typename PT>
	void operator()(const sp<dec_rsum_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	//
	template <typename PT>
	void operator()(const sp<dec_scan_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	//
	template <typename PT, bool USE_PATCHING>
	void operator()(const sp<enc_analyze_opr<PT, USE_PATCHING>>& opr) {
		opr->PointTo(vec_idx);
	}
	//
	template <typename PT>
	void operator()(const sp<dec_transpose_opr<PT>>& opr) {
	}
	// SLPATCH
	template <typename PT>
	void operator()(const sp<enc_slpatch_opr<PT>>& opr) {
	}
	// SLPATCH
	template <typename PT>
	void operator()(const sp<dec_slpatch_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	template <typename PT>
	void operator()(const sp<enc_null_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	template <typename PT>
	void operator()(const sp<dec_null_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	template <typename PT>
	void operator()(const sp<dec_frequency_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	template <typename PT>
	void operator()(const sp<enc_frequency_opr<PT>>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<dec_frequency_str_opr>& opr) {
		opr->PointTo(vec_idx);
	}
	void operator()(const sp<enc_frequency_str_opr>& opr) {
		opr->PointTo(vec_idx);
	}
	//
	template <typename PT>
	void operator()(const sp<enc_cross_rle_opr<PT>>& opr) {
	}
	template <typename PT>
	void operator()(const sp<dec_cross_rle_opr<PT>>& opr) {
	}
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg)
	}

	const n_t vec_idx;
};

PhysicalExpr::~PhysicalExpr() = default;

PhysicalExpr::PhysicalExpr()
    : n_active_operators(0) {
}

void PhysicalExpr::PointTo(n_t vec_idx) const {
	for (const auto& opr : operators) {
		visit(point_to_visitor {vec_idx}, opr);
	}
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Flush
\*--------------------------------------------------------------------------------------------------------------------*/
struct flush_segments_visitor {
	explicit flush_segments_visitor(vector<up<Segment>>& a_segments,
	                                Buf&                 buf,
	                                ColumnDescriptorT&   column_descriptor,
	                                uint8_t*             helper_buffer)
	    : segments(a_segments)
	    , buf(buf)
	    , column_descriptor(column_descriptor)
	    , helper_buffer(helper_buffer) {};

	template <typename PT>
	void operator()(const sp<enc_uncompressed_opr<PT>>& opr) {
		segments.push_back(std::move(opr->segment));
	}

	template <typename PT>
	void operator()(const sp<enc_scan_opr<PT>>& opr) {
	}

	void operator()(const sp<enc_fls_str_uncompressed_op>& opr) {
		segments.push_back(std::move(opr->data_segment));
		segments.push_back(std::move(opr->length_segment));
	}

	template <typename PT>
	void operator()(const sp<enc_ffor_opr<PT>>& opr) {
		segments.push_back(std::move(opr->bitpacked_segment));
		segments.push_back(std::move(opr->bitwidth_segment));
		segments.push_back(std::move(opr->base_segment));
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_dict_map_opr<KEY_PT, INDEX_PT>>& opr) {
	}

	// DICT
	template <typename KEY_PT>
	void operator()(const sp<enc_dict_opr<KEY_PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_alp_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_alp_rd_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<dec_uncompressed_opr<PT>>& opr) {
		FLS_UNREACHABLE()
	}

	void operator()(const sp<enc_struct_opr>& opr) {
		for (n_t expr_idx {0}; expr_idx < opr->internal_exprs.size(); expr_idx++) {
			FLS_ASSERT_E(opr->internal_exprs.size(), column_descriptor.children.size())
			opr->internal_exprs[expr_idx]->Finalize();
			opr->internal_exprs[expr_idx]->Flush(buf, *column_descriptor.children[expr_idx], helper_buffer);
		}
	}

	void operator()(const sp<enc_fsst_opr>& opr) {
		opr->MoveSegments(segments);
	}
	void operator()(const sp<enc_fsst12_opr>& opr) {
		opr->MoveSegments(segments);
	}
	// FSST DICT
	void operator()(const sp<enc_fsst_dict_opr>& opr) {
		opr->MoveSegments(segments);
	}
	void operator()(const sp<enc_fsst12_dict_opr>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_transpose_opr<PT>>& opr) {
	}

	template <typename PT>
	void operator()(const sp<enc_rsum_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_null_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	// SLPATCH
	template <typename PT>
	void operator()(const sp<enc_slpatch_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_frequency_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	void operator()(const sp<enc_frequency_str_opr>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_cross_rle_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg)
	}

	template <typename PT, bool USE_PATCHING>
	void operator()(const sp<enc_analyze_opr<PT, USE_PATCHING>>& opr) {
	}

	vector<up<Segment>>& segments;
	Buf&                 buf;
	ColumnDescriptorT&   column_descriptor;
	uint8_t*             helper_buffer;
};
void PhysicalExpr::Flush(Buf& buf, ColumnDescriptorT& column_descriptor, uint8_t* helper_buffer) const {

	column_descriptor.column_offset = buf.Size();

	vector<up<Segment>> segments;
	for (const auto& op : operators) {
		visit(flush_segments_visitor {segments, buf, column_descriptor, helper_buffer}, op);
	}

	n_t current_offset = column_descriptor.column_offset;

	for (const auto& segment : segments) {
		if (!segment->persistent) {
			continue;
		}

		auto segment_descriptor = segment->Dump(buf, current_offset, helper_buffer);

		column_descriptor.segment_descriptors.push_back(std::move(segment_descriptor));
	}

	column_descriptor.total_size = buf.Size() - column_descriptor.column_offset;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Size
\*--------------------------------------------------------------------------------------------------------------------*/
struct extract_segments_visitor {
	explicit extract_segments_visitor(vector<up<Segment>>& a_segments)
	    : segments(a_segments) {};

	template <typename PT>
	void operator()(const sp<enc_scan_opr<PT>>& opr) {
	}

	template <typename PT>
	void operator()(const sp<enc_uncompressed_opr<PT>>& opr) {
		segments.push_back(std::move(opr->segment));
	}

	void operator()(const sp<enc_fls_str_uncompressed_op>& opr) {
		segments.push_back(std::move(opr->data_segment));
		segments.push_back(std::move(opr->length_segment));
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_dict_map_opr<KEY_PT, INDEX_PT>>& opr) {
	}

	template <typename KEY_PT>
	void operator()(const sp<enc_dict_opr<KEY_PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_ffor_opr<PT>>& opr) {
		segments.push_back(std::move(opr->bitpacked_segment));
		segments.push_back(std::move(opr->bitwidth_segment));
		segments.push_back(std::move(opr->base_segment));
	}

	template <typename PT>
	void operator()(const sp<enc_alp_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<enc_alp_rd_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}

	template <typename PT>
	void operator()(const sp<dec_uncompressed_opr<PT>>& opr) {
		FLS_UNREACHABLE()
	}

	void operator()(const sp<enc_fsst_opr>& opr) {
		opr->MoveSegments(segments);
	}
	void operator()(const sp<enc_fsst12_opr>& opr) {
		opr->MoveSegments(segments);
	}

	void operator()(const sp<enc_struct_opr>& opr) {
		for (const auto& op : opr->internal_exprs) {
			for (const auto& child_operator : op->operators) {
				visit(extract_segments_visitor {segments}, child_operator);
			}
		}
	}

	// DICT
	void operator()(const sp<enc_fsst_dict_opr>& opr) {
		opr->MoveSegments(segments);
	}
	void operator()(const sp<enc_fsst12_dict_opr>& opr) {
		opr->MoveSegments(segments);
	}

	// RLE
	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
		opr->MoveSegments(segments);
	}
	// TRANSPOSE
	template <typename PT>
	void operator()(const sp<enc_transpose_opr<PT>>& opr) {
	}
	// RSUM
	template <typename PT>
	void operator()(const sp<enc_rsum_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}
	// TRANSPOSE
	template <typename PT, bool USE_PATCHING>
	void operator()(const sp<enc_analyze_opr<PT, USE_PATCHING>>& opr) {
	}
	// SLPATCH
	template <typename PT>
	void operator()(const sp<enc_slpatch_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}
	// FREQUENCY
	template <typename PT>
	void operator()(const sp<enc_frequency_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}
	void operator()(const sp<enc_frequency_str_opr>& opr) {
		opr->MoveSegments(segments);
	}
	// CROSS_RLE
	template <typename PT>
	void operator()(const sp<enc_cross_rle_opr<PT>>& opr) {
		opr->MoveSegments(segments);
	}
	//
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg)
	}

public:
	vector<up<Segment>>& segments;
};

n_t ScaleDownTheSize(n_t segment_size, n_t sample_size, n_t n_vecs) {
	return (segment_size / n_vecs) * sample_size;
}

n_t PhysicalExpr::Size(n_t sample_size, n_t n_vecs) const {
	vector<up<Segment>> segments;
	for (const auto& op : operators) {
		visit(extract_segments_visitor {segments}, op);
	}

	n_t ttl_size {0};
	for (const auto& segment : segments) {
		if (!segment->persistent) {
			continue;
		}

		const auto segment_size = segment->buf->Size() + segment->entry_points.size() * sizeof(entry_point_t);
		n_t        scaled_down_size;
		if (segment->IsBlockBased()) {
			scaled_down_size = ScaleDownTheSize(segment_size, sample_size, n_vecs);
		} else {
			scaled_down_size = segment_size;
		}
		ttl_size += scaled_down_size;
	}

	return ttl_size;
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Finalize
\*--------------------------------------------------------------------------------------------------------------------*/
struct finalize_operators_visitor {
	finalize_operators_visitor() = default;

	template <typename KEY_PT>
	void operator()(const sp<enc_dict_opr<KEY_PT>>& opr) {
		opr->Finalize(); //
	}
	template <typename PT>
	void operator()(const sp<enc_alp_rd_opr<PT>>& opr) {
		opr->Finalize();
	}
	void operator()(const sp<enc_fsst_opr>& opr) {
		opr->Finalize();
	}
	void operator()(const sp<enc_fsst12_opr>& opr) {
		opr->Finalize();
	}

	template <typename PT>
	void operator()(const sp<enc_scan_opr<PT>>& opr) {
	}

	template <typename PT>
	void operator()(const sp<enc_uncompressed_opr<PT>>& opr) {
	}

	void operator()(const sp<enc_fls_str_uncompressed_op>& opr) {
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_dict_map_opr<KEY_PT, INDEX_PT>>& opr) {
	}

	template <typename PT>
	void operator()(const sp<enc_ffor_opr<PT>>& opr) {
	}

	template <typename PT>
	void operator()(const sp<enc_alp_opr<PT>>& opr) {
	}

	template <typename PT>
	void operator()(const sp<dec_uncompressed_opr<PT>>& opr) {
	}

	void operator()(const sp<enc_struct_opr>& opr) {
	}

	// DICT FSST
	void operator()(const sp<enc_fsst_dict_opr>& opr) {
		opr->Finalize();
	}
	void operator()(const sp<enc_fsst12_dict_opr>& opr) {
		opr->Finalize();
	}

	template <typename KEY_PT, typename INDEX_PT>
	void operator()(const sp<enc_rle_map_opr<KEY_PT, INDEX_PT>>& opr) {
	}
	// TRANSPOSE
	template <typename PT>
	void operator()(const sp<enc_transpose_opr<PT>>& opr) {
	}
	// RSUM
	template <typename PT>
	void operator()(const sp<enc_rsum_opr<PT>>& opr) {
	}
	// ANALYZE
	template <typename PT, bool USE_PATCHING>
	void operator()(const sp<enc_analyze_opr<PT, USE_PATCHING>>& opr) {
	}
	// SLPATCH
	template <typename PT>
	void operator()(const sp<enc_slpatch_opr<PT>>& opr) {
	}
	//
	// SLPATCH
	template <typename PT>
	void operator()(const sp<enc_null_opr<PT>>& opr) {
	}
	//
	template <typename PT>
	void operator()(const sp<enc_frequency_opr<PT>>& opr) {
		opr->Finalize();
	}
	void operator()(const sp<enc_frequency_str_opr>& opr) {
		opr->Finalize();
	}
	//
	template <typename PT>
	void operator()(const sp<enc_cross_rle_opr<PT>>& opr) {
		opr->Finalize();
	}
	//
	void operator()(const auto& arg) {
		FLS_UNREACHABLE_WITH_TYPE(arg)
	}
};

void PhysicalExpr::Finalize() const {
	for (const auto& op : operators) {
		visit(finalize_operators_visitor {}, op);
	}
}
} // namespace fastlanes