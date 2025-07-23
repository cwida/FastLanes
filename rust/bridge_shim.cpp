// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// rust/bridge_shim.cpp
// ────────────────────────────────────────────────────────
#include "bridge_shim.hpp"
#include <fls/info.hpp>
#include <string>         // for std::string

rust::String get_version() {
    // fastlanes::Info::get_version() returns a std::string_view
    auto sv = fastlanes::Info::get_version();
    // make a real std::string out of it
    std::string s{ sv };
    // rust::String has a constructor from const std::string&
    return rust::String(s);
}

std::unique_ptr<Connection> connect() {
    return fastlanes::connect();
}
