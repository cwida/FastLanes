use cxx::UniquePtr;
use fastlanes::{get_version, connect, Connection};

fn main() {
    let version = get_version();
    let conn: UniquePtr<Connection> = connect();
    println!("FastLanes version: {version}");
}
