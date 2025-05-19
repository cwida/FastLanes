// bridge_shim.hpp
#pragma once
#include <rust/cxx.h>
#include <memory>
#include <filesystem>
#include "fls/connection.hpp"

using Connection = fastlanes::Connection;

// factory + version
rust::String get_version();
std::unique_ptr<Connection> connect();

// previously-added helpers
inline Connection& inline_footer(Connection& c)               { return c.inline_footer(); }
inline Connection& read_csv     (Connection& c, rust::Str dir){ return c.read_csv(std::filesystem::path(std::string(dir))); }
inline Connection& to_fls       (Connection& c, rust::Str out){ return c.to_fls  (std::filesystem::path(std::string(out))); }
