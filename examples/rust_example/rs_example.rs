// rs_example.rs

//! ```cargo
//! [dependencies]
//! anyhow = "1"
//! fls-rs = { path = "./rust" }  # Adjust the path to your fls_rs crate
//! ```

use fls_rs::{connect, inline_footer, read_csv, read_fls, to_csv, to_fls};
use std::path::PathBuf;

fn main() -> anyhow::Result<()> {
    let version: String = fls_rs::get_version();
    println!("fastlanes C++ bridge version: {}", version);

    // Get path to current crate (assumes this file lives in fastlanes root)
    let manifest_dir = PathBuf::from(env!("CARGO_MANIFEST_DIR"));
    let repo_root = manifest_dir
        .parent()
        .expect("rust/Cargo.toml must live one level down from repo root");

    let csv_path = repo_root.join("../data/generated/issues/issue_000");
    let fls_path = repo_root.join("written_by_rust.fls");
    let decoded_csv_path = repo_root.join("decoded_by_fastlanes_rs.csv");

    let mut conn = connect();
    let mut pin = conn.pin_mut();

    inline_footer(pin.as_mut());
    read_csv(pin.as_mut(), csv_path.to_str().unwrap());
    to_fls(pin.as_mut(), fls_path.to_str().unwrap());

    let mut rdr = read_fls(pin.as_mut(), fls_path.to_str().unwrap());
    to_csv(rdr.pin_mut(), decoded_csv_path.to_str().unwrap());

    println!("✓ everything finished");
    Ok(())
}
