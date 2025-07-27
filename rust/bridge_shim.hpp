// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// rust/bridge_shim.hpp
// ────────────────────────────────────────────────────────
// bridge_shim.hpp
#pragma once
#include <rust/cxx.h>
#include <memory>
#include <filesystem>

#include "fls/connection.hpp"
#include "fls/reader/table_reader.hpp"          // <-- you forgot this!

using Connection  = fastlanes::Connection;       // alias BEFORE first use
using TableReader = fastlanes::TableReader;      // alias BEFORE first use

// -----------------------------------------------------------------------------
// factory + version
rust::String                get_version();
std::unique_ptr<Connection> connect();

// -----------------------------------------------------------------------------
// helpers that operate on Connection
inline Connection& inline_footer(Connection& c)               { return c.inline_footer(); }
inline Connection& read_csv     (Connection& c, rust::Str dir){ return c.read_csv(std::filesystem::path{std::string(dir)}); }
inline Connection& to_fls       (Connection& c, rust::Str out){ return c.to_fls  (std::filesystem::path{std::string(out)}); }

// -----------------------------------------------------------------------------
// NEW helpers that operate on TableReader
inline std::unique_ptr<TableReader>
read_fls(Connection& c, rust::Str p)
{
    return c.read_fls(std::filesystem::path{std::string(p)});
}

inline TableReader&
to_csv(TableReader& r, rust::Str p)
{
    r.to_csv(std::string(p));          // choose the std::string overload
    return r;
}
