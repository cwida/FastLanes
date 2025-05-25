<p align="center">
  <img src="assets/logo.svg" alt="FastLanes Logo" width="180" />
</p>

# FastLanes: A Next-Generation Columnar File Format

FastLanes is like Parquet with **40% better compression** and **40× faster decoding**, making it the ideal choice for
high-throughput analytics workloads.

---

## Getting Started

### Python

```python
import pyfastlanes

# Connect to FastLanes
conn = pyfastlanes.connect()

# Convert a CSV directory to FastLanes format
conn.inline_footer().read_csv("path/to/csv_dir").to_fls("data.fls")

# Read back and write to CSV
reader = conn.read_fls("data.fls")
reader.to_csv("decoded.csv")
````

### C++

Add FastLanes as a dependency via CMake:

```cmake
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929  # release-1.11.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
```

Example usage:

```cpp
#include "fastlanes.hpp"

int main() {
    fastlanes::Connection conn;
    conn.read_csv("data/csv_dir").to_fls("data.fls");

    auto reader = fastlanes::Connection().read_fls("data.fls");
    reader->to_csv("decoded.csv");
    return EXIT_SUCCESS;
}
```

### Coming Soon

* **CUDA** support for FastLanes CUDA reader
* **Rust** bindings for seamless integration in Rust projects

---

## Publications

* **Azim Afroozeh & Peter Boncz**, “The FastLanes Compression Layout: Decoding > 100 Billion Integers per Second with
  Scalar Code,” *PVLDB*, 16(9): 2132–2144, May 2023

    * [Read the paper](https://www.vldb.org/pvldb/vol16/p2132-afroozeh.pdf)
    * [Source code](publications/data_parallelized_encodings)

* **Azim Afroozeh, Lotte Felius & Peter Boncz**, “Accelerating GPU Data Processing Using FastLanes Compression,” *DaMoN
  ’24*, Proceedings of the 20th International Workshop on Data Management on New Hardware, Santiago, Chile, June 2024

    * [Read the paper](https://doi.org/10.1145/3662010.3663450)
    * [Source code](https://github.com/cwida/FastLanesGPU)

---

## How to Cite

If you use FastLanes in your research or projects, please cite:

```bibtex
@article{afroozeh2023fastlanes,
    author = {Afroozeh, Azim and Boncz, Peter},
    title = {The FastLanes Compression Layout: Decoding > 100 Billion Integers per Second with Scalar Code},
    journal = {Proceedings of the VLDB Endowment},
    volume = {16},
    number = {9},
    pages = {2132--2144},
    month = may,
    year = {2023},
    publisher = {VLDB Endowment}
}

@inproceedings{afroozeh2024accelerating,
    author = {Afroozeh, Azim and Felius, Lotte and Boncz, Peter},
    title = {Accelerating GPU Data Processing Using FastLanes Compression},
    booktitle = {DaMoN ’24: Proceedings of the 20th International Workshop on Data Management on New Hardware},
    pages = {1--11},
    month = jun,
    year = {2024},
    organization = {ACM},
    doi = {10.1145/3662010.3663450}
}
```

---

## License

This project is released under the [MIT License](LICENSE).

---

## Join Our Community

Come discuss FastLanes, share feedback, and help shape the future of data formats on Discord:
[![Join Our Discord](https://img.shields.io/discord/1282716959099588651?label=Join%20Our%20Discord\&logo=discord\&color=7289da)](https://discord.gg/SpTHkCQ7uh)

