// lib.rs

#[cxx::bridge]
pub mod ffi {
    unsafe extern "C++" {
        include!("bridge_shim.hpp");

        /// Opaque C++ Connection type
        type Connection;

        /// Factory function from your C++ shim
        fn connect() -> UniquePtr<Connection>;

        /// This returns a Rust String, not a C++ CxxString
        fn get_version() -> String;
    }
}

// re-export the C++ type at the crate root
pub use ffi::Connection;

// re-export UniquePtr so users don’t need to depend on cxx directly
pub use cxx::UniquePtr;

pub fn connect() -> UniquePtr<Connection> {
    ffi::connect()
}

pub fn get_version() -> String {
    ffi::get_version()
}
