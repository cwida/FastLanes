use std::path::PathBuf;
use fastlanes::{connect, inline_footer, read_csv, to_fls};

fn main() -> anyhow::Result<()> {
    // 1) CARGO_MANIFEST_DIR == ".../fastlanes_copy/rust"
    let manifest_dir = PathBuf::from(env!("CARGO_MANIFEST_DIR"));

    // 2) repo_root == ".../fastlanes_copy"
    let repo_root = manifest_dir
        .parent()
        .expect("rust/Cargo.toml must live one level down from repo root");

    // 3) repo_root_dir_name == "fastlanes_copy"
    let repo_root_dir_name = repo_root
        .file_name()
        .and_then(|os| os.to_str())
        .expect("repo root folder must be valid UTF-8");
    assert_eq!(repo_root_dir_name, "fastlanes_copy");

    // 4) build your real paths off of `repo_root`
    let csv_path = repo_root.join("data/generated/issues/issue_000");
    let fls_path = repo_root.join("data/fls/written_by_rust.fls");

    // 5) now call into C++
    let mut conn = connect();
    let mut pin  = conn.pin_mut();

    inline_footer(pin.as_mut());
    read_csv    (pin.as_mut(), csv_path.to_str().unwrap());
    to_fls      (pin.as_mut(), fls_path.to_str().unwrap());

    println!("ok — finished (repo root was “{}”)", repo_root_dir_name);
    Ok(())
}
