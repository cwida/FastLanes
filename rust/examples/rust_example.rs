use fls_rs::{connect, inline_footer, read_csv, read_fls, to_csv, to_fls};
use std::path::PathBuf;

fn main() -> anyhow::Result<()> {
    // 0) Print the library version:
    let version: String = fls_rs::get_version();
    println!("fastlanes C++ bridge version: {}", version);

    // 1) CARGO_MANIFEST_DIR == ".../fastlanes/rust"
    let manifest_dir = PathBuf::from(env!("CARGO_MANIFEST_DIR"));

    // 2) repo_root == ".../fastlanes"
    let repo_root = manifest_dir
        .parent()
        .expect("rust/Cargo.toml must live one level down from repo root");

    // 4) build your real paths off of `repo_root`
    let csv_path = repo_root.join("data/issues/issue_000");
    let fls_path = repo_root.join("data/fls/written_by_rust.fls");
    let decoded_csv_path = repo_root.join("data/fls/decoded_by_fastlanes_rs.csv");

    // 5) now call into C++
    let mut conn = connect();
    let mut pin = conn.pin_mut();

    inline_footer(pin.as_mut());
    read_csv(pin.as_mut(), csv_path.to_str().unwrap());
    to_fls(pin.as_mut(), fls_path.to_str().unwrap());

    // NEW ----------------------------------------------------
    let mut rdr = read_fls(pin.as_mut(), fls_path.to_str().unwrap());
    to_csv(rdr.pin_mut(), decoded_csv_path.to_str().unwrap());
    //---------------------------------------------------------

    println!("✓ everything finished");
    Ok(())
}
