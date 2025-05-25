#include "fls/reader/segment.hpp"
#include "fls/cor/lyt/buf.hpp"
#include "fls/footer/segment_descriptor.hpp"
#include "fls/std/vector.hpp"
#include <stdexcept>

namespace fastlanes {

/*--------------------------------------------------------------------------------------------------------------------*\
 * EntryPointView
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
EntryPointView<PT>::EntryPointView(span<PT> this_span)
    : entrypoint_span(this_span) {
}

template <typename PT>
n_t EntryPointView<PT>::size() const {
	return entrypoint_span.size();
}

template <typename PT>
PT& EntryPointView<PT>::operator[](const n_t index) {
	return entrypoint_span[index];
}

template <typename PT>
const PT& EntryPointView<PT>::operator[](const n_t index) const {
	return entrypoint_span[index];
}

template class EntryPointView<u32_pt>;
template class EntryPointView<u16_pt>;
template class EntryPointView<u08_pt>;

n_t get_offset(const entry_point_view_t& entry_point_view, n_t vex_idx) {
	return std::visit(overloaded {//
	                              [](const std::monostate&) -> n_t { FLS_UNREACHABLE() },
	                              [vex_idx]<typename PT>(const EntryPointView<PT>& entry_point_view) -> n_t {
		                              if (vex_idx == 0) {
			                              return 0;
		                              }
		                              return entry_point_view.entrypoint_span[vex_idx - 1];
	                              }},
	                  entry_point_view);
}

n_t get_size(const entry_point_view_t& entry_point_view) {
	return std::visit(overloaded {//
	                              [](const std::monostate&) -> n_t { FLS_UNREACHABLE() },
	                              []<typename PT>(const EntryPointView<PT>& entry_point_view) -> n_t {
		                              return entry_point_view.entrypoint_span.size();
	                              }},
	                  entry_point_view);
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * SegmentView
\*--------------------------------------------------------------------------------------------------------------------*/
SegmentView::SegmentView(entry_point_view_t entry_point_view, span<std::byte> data_span)
    : entry_point_view(entry_point_view)
    , data_span(data_span)
    , data(nullptr)
    , vec_idx(INVALID_N) {
}

void SegmentView::PointTo(const n_t a_vec_idx) {
	data    = data_span.data() + get_offset(entry_point_view, a_vec_idx);
	vec_idx = a_vec_idx;
}

n_t SegmentView::Size() const {
	FLS_ASSERT_L(vec_idx, get_size(entry_point_view))

	if (vec_idx == 0) {
		return get_offset(entry_point_view, 0);
	}

	return get_offset(entry_point_view, vec_idx) - get_offset(entry_point_view, vec_idx - 1);

	FLS_UNREACHABLE()
}

/*--------------------------------------------------------------------------------------------------------------------*\
 * Segment
\*--------------------------------------------------------------------------------------------------------------------*/
Segment::Segment()
    : persistent(true)
    , is_block_based(false) {
	buf = make_unique<Buf>();
	//
}

void Segment::Flush(const void* data_p, const n_t size) {
	FLS_ASSERT_NOT_NULL_POINTER(data_p)
	FLS_ASSERT_NOT_NULL_POINTER(buf.get())

	if (!persistent) {
		return;
	}

	buf->Append(data_p, size);
	flush_entrypoint(size);
}

void Segment::MakeTemporary() {
	FLS_ASSERT_TRUE(persistent)

	persistent = false;
}

EntryPointType detect_smallest_entry_point_type(const Segment& segment) {
	const auto entry_points = segment.entry_points;

	if (entry_points.empty()) {
		throw std::invalid_argument("entry_points vector is empty");
	}

	const uint32_t value = entry_points.back();

	if (value <= static_cast<uint32_t>(std::numeric_limits<uint8_t>::max())) {
		return EntryPointType::UINT8;
	}
	if (value <= static_cast<uint32_t>(std::numeric_limits<uint16_t>::max())) {
		return EntryPointType::UINT16;
	}

	return EntryPointType::UINT32;
}

template <typename T>
void cast_entry_points(uint8_t* helper_buffer, const std::vector<entry_point_t>& entry_points) {
	auto* typed_entry_point = reinterpret_cast<T*>(helper_buffer);
	for (size_t entry_point_idx = 0; entry_point_idx < entry_points.size(); entry_point_idx++) {
		typed_entry_point[entry_point_idx] = static_cast<T>(entry_points[entry_point_idx]);
	}
}

void cast(const std::vector<entry_point_t>& entry_points, EntryPointType entry_point_t, uint8_t* helper_buffer) {
	switch (entry_point_t) {
	case EntryPointType::UINT8:
		cast_entry_points<uint8_t>(helper_buffer, entry_points);
		break;
	case EntryPointType::UINT16:
		cast_entry_points<uint16_t>(helper_buffer, entry_points);
		break;
	case EntryPointType::UINT32:
		cast_entry_points<uint32_t>(helper_buffer, entry_points);
		break;
	default:
		FLS_UNREACHABLE();
	}
}

up<SegmentDescriptorT> Segment::Dump(Buf& external_buf, n_t& current_offset, uint8_t* helper_buffer) const {
	FLS_ASSERT_NOT_NULL_POINTER(entry_points.data())

	SegmentDescriptorT segment_descriptor;

	segment_descriptor.entry_point_t = detect_smallest_entry_point_type(*this);
	cast(entry_points, segment_descriptor.entry_point_t, helper_buffer);

	segment_descriptor.entrypoint_offset = current_offset;
	// first offsets;
	segment_descriptor.entrypoint_size =
	    entry_points.size() * sizeof_entry_point_type(segment_descriptor.entry_point_t);

	external_buf.Append(helper_buffer, segment_descriptor.entrypoint_size);

	current_offset += segment_descriptor.entrypoint_size;

	// next data
	segment_descriptor.data_offset = current_offset;
	segment_descriptor.data_size   = buf->Size();
	external_buf.Append(buf->data(), segment_descriptor.data_size);
	current_offset += segment_descriptor.data_size;

	return make_unique<SegmentDescriptorT>(segment_descriptor);
}

void Segment::MakeBlockBased() {
	is_block_based = true;
}

bool Segment::IsBlockBased() {
	return is_block_based;
}

void Segment::flush_entrypoint(n_t size) {
	FLS_ASSERT_LE(size, std::numeric_limits<entry_point_t>::max())
	auto downcasted_size = static_cast<entry_point_t>(size);
	//
	if (entry_points.empty()) {
		entry_points.push_back(downcasted_size);
		return;
	}

	//
	const auto prev_offset = entry_points.back();
	const auto curr_offset = prev_offset + downcasted_size;
	entry_points.push_back(curr_offset);
}

template <typename PT>
PT* Segment::GetFixedSizeArray(const n_t length) {
	const auto size = length * sizeof(PT);
	flush_entrypoint(size);

	return buf->GetFixedSizeArray<PT>(size);
}

template i64_pt* Segment::GetFixedSizeArray<i64_pt>(n_t length);
template i32_pt* Segment::GetFixedSizeArray<i32_pt>(n_t length);
template i16_pt* Segment::GetFixedSizeArray<i16_pt>(n_t length);
template i08_pt* Segment::GetFixedSizeArray<i08_pt>(n_t length);
template dbl_pt* Segment::GetFixedSizeArray<dbl_pt>(n_t length);
template flt_pt* Segment::GetFixedSizeArray<flt_pt>(n_t length);

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_segment_view
\*--------------------------------------------------------------------------------------------------------------------*/
SegmentView make_segment_view(span<std::byte> column_span, const SegmentDescriptorT& segment_descriptor) {
	auto segment_span = column_span.subspan(segment_descriptor.entrypoint_offset, segment_descriptor.entrypoint_size);

	switch (segment_descriptor.entry_point_t) {
	case EntryPointType::UINT8: {
		const auto entry_point_span =
		    std::span<uint8_t>(reinterpret_cast<uint8_t*>(segment_span.data()), segment_span.size() / sizeof(uint8_t));

		auto entry_point_view = EntryPointView<uint8_t>(entry_point_span);

		const auto data_span = column_span.subspan(segment_descriptor.data_offset, segment_descriptor.data_size);
		return SegmentView {entry_point_view, data_span};
	}
	case EntryPointType::UINT16: {
		const auto entry_point_span = std::span<uint16_t>(reinterpret_cast<uint16_t*>(segment_span.data()),
		                                                  segment_span.size() / sizeof(uint16_t));

		auto entry_point_view = EntryPointView<uint16_t>(entry_point_span);

		const auto data_span = column_span.subspan(segment_descriptor.data_offset, segment_descriptor.data_size);
		return SegmentView {entry_point_view, data_span};
	}
	case EntryPointType::UINT32: {
		const auto entry_point_span = std::span<uint32_t>(reinterpret_cast<uint32_t*>(segment_span.data()),
		                                                  segment_span.size() / sizeof(uint32_t));

		auto entry_point_view = EntryPointView<uint32_t>(entry_point_span);

		const auto data_span = column_span.subspan(segment_descriptor.data_offset, segment_descriptor.data_size);
		return SegmentView {entry_point_view, data_span};
	}
	case EntryPointType::UINT64:
	default:
		FLS_UNREACHABLE()
	}
}

} // namespace fastlanes