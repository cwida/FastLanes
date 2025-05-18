#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("bridge_shim.hpp");

        // This returns a Rust String, not a C++ CxxString
        fn get_version() -> String;
    }
}

pub fn get_version() -> String {
    // just forward it – no conversions needed
    ffi::get_version()
}
