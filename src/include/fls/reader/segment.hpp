#ifndef FLS_READER_SEGMENT_HPP
#define FLS_READER_SEGMENT_HPP

#include "fls/common/common.hpp"
#include "fls/std/span.hpp"
#include "fls/std/variant.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Buf;
struct SegmentDescriptorT;
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*\
 * EntryPointView
\*--------------------------------------------------------------------------------------------------------------------*/
template <typename PT>
class EntryPointView {
public:
public:
	explicit EntryPointView(span<PT>);

public:
	n_t       size() const;
	PT&       operator[](n_t index);
	const PT& operator[](n_t index) const;

public:
	span<PT> entrypoint_span;
};

using entry_point_view_t =
    variant<std::monostate, EntryPointView<uint8_t>, EntryPointView<uint16_t>, EntryPointView<uint32_t>>;

n_t get_offset(const entry_point_view_t& entry_point_view, n_t vex_idx);

n_t get_size(const entry_point_view_t& entry_point_view);

/*--------------------------------------------------------------------------------------------------------------------*\
* SegmentView
\*--------------------------------------------------------------------------------------------------------------------*/
class SegmentView {
public:
	explicit SegmentView(entry_point_view_t entry_point_view, span<std::byte> data_span);

public:
	void              PointTo(n_t vec_idx);
	[[nodiscard]] n_t Size() const;

public:
	entry_point_view_t entry_point_view;
	span<std::byte>    data_span;
	std::byte*         data;
	n_t                vec_idx;
};

/*--------------------------------------------------------------------------------------------------------------------*\
 * make_segment_view
\*--------------------------------------------------------------------------------------------------------------------*/
SegmentView make_segment_view(span<std::byte> column_span, const SegmentDescriptorT& segment_descriptor);

/*--------------------------------------------------------------------------------------------------------------------*\
 * Segment
\*--------------------------------------------------------------------------------------------------------------------*/
class Segment {
public:
	explicit Segment();

public:
	void Flush(const void* pointer, n_t size);
	//
	template <typename PT>
	PT* GetFixedSizeArray(n_t length);
	//
	void MakeTemporary();
	//
	up<SegmentDescriptorT> Dump(Buf& external_buf, n_t& current_offset, uint8_t* entry_point_buffer) const;
	//
	void MakeBlockBased();
	//
	bool IsBlockBased();

private:
	void flush_entrypoint(n_t size);

public:
	bool                  persistent;
	up<Buf>               buf;
	vector<entry_point_t> entry_points;

private:
	bool is_block_based;
};

} // namespace fastlanes

#endif // FLS_READER_SEGMENT_HPP
