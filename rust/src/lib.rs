// lib.rs

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("bridge_shim.hpp");
        type Connection;

        fn connect() -> UniquePtr<Connection>;
        fn get_version() -> String;

        // free functions again – one explicit lifetime ties
        // the input & output pins together
        fn inline_footer<'a>(c: Pin<&'a mut Connection>) -> Pin<&'a mut Connection>;
        fn read_csv<'a>   (c: Pin<&'a mut Connection>, dir: &'a str)
                           -> Pin<&'a mut Connection>;
        fn to_fls<'a>     (c: Pin<&'a mut Connection>, out: &'a str)
                           -> Pin<&'a mut Connection>;
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

pub use ffi::{inline_footer, read_csv, to_fls};   // add this near the bottom
