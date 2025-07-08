#ifndef FLS_WRITER_COLUMNVIEW_HPP
#define FLS_WRITER_COLUMNVIEW_HPP

#include "fls/common/double.hpp"
#include "fls/table/rowgroup.hpp"
#include "ingest.hpp"
#include <span>
#include <string>

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
struct ColumnWriteViewVisitor;
/*--------------------------------------------------------------------------------------------------------------------*/

struct ColumnWriteView {
	friend class RowGroupWriter;

public:
	virtual ~ColumnWriteView() = default;

private:
	virtual void   Accept(col_pt& col, ColumnWriteViewVisitor& v) const = 0;
	virtual size_t Size() const                                         = 0;
};

template <typename PT>
struct PrimitiveWriteView final : ColumnWriteView {
	friend struct ColumnWriteViewVisitor;

public:
	explicit PrimitiveWriteView(std::span<const PT> data)
	    : data(data) {
	}

private:
	void Accept(col_pt& col, ColumnWriteViewVisitor& v) const override;

	size_t Size() const override {
		return data.size();
	}

private:
	std::span<const PT> data;
};

struct StringWriteView final : ColumnWriteView {
	friend struct ColumnWriteViewVisitor;

public:
	explicit StringWriteView(std::span<const str_pt> data)
	    : data(data) {
	}

private:
	void Accept(col_pt& col, ColumnWriteViewVisitor& v) const override;

	size_t Size() const override {
		return data.size();
	}

private:
	std::span<const str_pt> data;
};

// TODO: Why make a function static in a visitor?
struct ColumnWriteViewVisitor {
	explicit ColumnWriteViewVisitor() {};

	template <typename PT>
	void Visit(col_pt& col, const PrimitiveWriteView<PT>& v) {
		if (auto ptr = std::get_if<up<TypedCol<PT>>>(&col)) {
			Ingest::TypedIngest<PT>(*ptr->get(), v.data);
		} else {
			FLS_ABORT("Column to ingest is incompatible with provided schema.");
		}
	}

	void Visit(col_pt& col, const StringWriteView& v) {
		if (auto ptr = std::get_if<up<FLSStrColumn>>(&col)) {
			Ingest::FLSStringIngest(*ptr->get(), v.data);
		} else {
			FLS_ABORT("Column to ingest is incompatible with provided schema.");
		}
	}
};

// Out of line declarations for the Accept function, here we know the ColumnViewVisitor type.
template <typename PT>
void PrimitiveWriteView<PT>::Accept(col_pt& col, ColumnWriteViewVisitor& v) const {
	v.Visit(col, *this);
}

inline void StringWriteView::Accept(col_pt& col, ColumnWriteViewVisitor& v) const {
	v.Visit(col, *this);
}

} // namespace fastlanes

#endif // FLS_WRITER_COLUMNVIEW_HPP