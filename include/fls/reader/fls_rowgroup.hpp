#ifndef FLS_READER_FLS_ROWGROUP_HPP
#define FLS_READER_FLS_ROWGROUP_HPP

#include "fls/reader/horizontal_column.hpp"
#include "fls/std/span.hpp"
#include "fls/std/vector.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class Footer;
/*--------------------------------------------------------------------------------------------------------------------*/

class FLSRowgroup {
public:
	explicit FLSRowgroup(span<std::byte> ptr, const Footer& footer);

public:
	vector<HorizontalColumn> columns;
};

} // namespace fastlanes

#endif // FLS_READER_FLS_ROWGROUP_HPP
