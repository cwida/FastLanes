#ifndef FLS_READER_HORIZONTAL_COLUMN_HPP
#define FLS_READER_HORIZONTAL_COLUMN_HPP

#include "fls/std/span.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/

class HorizontalColumn {
public:
	explicit HorizontalColumn(span<std::byte> ptr);

public:
	span<std::byte> ptr;
};

} // namespace fastlanes
#endif // FLS_READER_HORIZONTAL_COLUMN_HPP