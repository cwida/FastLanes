#ifndef FLS_READER_EXTERNAL_READER_HPP
#define FLS_READER_EXTERNAL_READER_HPP

#include "fls/common/alias.hpp"
#include "fls/std/variant.hpp"

namespace fastlanes {
/*--------------------------------------------------------------------------------------------------------------------*/
class CsvReader;
/*--------------------------------------------------------------------------------------------------------------------*/

using external_reader = variant<std::monostate, up<CsvReader>>;

} // namespace fastlanes

#endif // FLS_READER_COLUMN_VIEW_HPP