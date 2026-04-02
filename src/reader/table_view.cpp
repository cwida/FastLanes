// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/reader/table_view.cpp
// ────────────────────────────────────────────────────────
#include "fls/reader/table_view.hpp"
#include "fls/reader/rowgroup_view.hpp"

namespace fastlanes {

TableView::~TableView()                               = default;
TableView::TableView(TableView&&) noexcept            = default;
TableView& TableView::operator=(TableView&&) noexcept = default;

} // namespace fastlanes
