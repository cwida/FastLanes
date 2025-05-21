// build.rs

fn main() {
    // 1) Where did cmake install FastLanes?
    let prefix =
        std::env::var("FASTLANES_INSTALL_PREFIX").unwrap_or_else(|_| "../build/install".into());
    let inc = format!("{}/include", &prefix);
    let lib = format!("{}/lib", &prefix);

    // 2) Generate the cxx bridge & compile our shim.cpp
    cxx_build::bridge("src/lib.rs") // <-- your #[cxx::bridge] mod
        .include(&inc) // <-- find <fls/info.hpp>
        .include(std::env::var("CARGO_MANIFEST_DIR").unwrap())
        // <-- find your own headers in ./src
        .file("bridge_shim.cpp") // <-- implement get_version() here
        .flag_if_supported("-std=c++20")
        .compile("fastlanes_version");

    // 3) Tell rustc where to find & link the FastLanes library
    println!("cargo:rustc-link-search=native={}", lib);
    println!("cargo:rustc-link-lib=static=FastLanes");
    println!("cargo:rustc-link-lib=static=ALP");
    println!("cargo:rustc-link-lib=static=primitives");
    println!("cargo:rustc-link-lib=c++"); // libc++
                                          // if you built a shared lib instead:
                                          // println!("cargo:rustc-link-lib=dylib=FastLanes");

    // 4) Re-run this build script if things change:
    println!("cargo:rerun-if-env-changed=FASTLANES_INSTALL_PREFIX");
    println!("cargo:rerun-if-changed=src/lib.rs");
    println!("cargo:rerun-if-changed=src/bridge_shim.cpp");
}
