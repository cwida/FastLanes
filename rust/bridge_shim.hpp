#pragma once
#include <rust/cxx.h>
#include <memory>
#include "fls/connection.hpp"  // this header puts `fastlanes::Connection` in scope

// **Bring the real class into the global namespace:**
using Connection = fastlanes::Connection;

// Expose exactly the Rust–C++ signatures you want:
rust::String get_version();
std::unique_ptr<Connection> connect();
