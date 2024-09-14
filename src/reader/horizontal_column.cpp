#include "fls/reader/horizontal_column.hpp"

namespace fastlanes {

HorizontalColumn::HorizontalColumn(span<std::byte> ptr)
    : ptr(ptr) {}
} // namespace fastlanes