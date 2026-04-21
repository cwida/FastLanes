# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What is FastLanes

FastLanes is a C++20 columnar compression storage format — "Like Parquet, but with 40% better compression and 40× faster decoding." Zero external dependencies, SIMD-friendly without explicit SIMD instructions. Bindings exist for Python (`python/`), Rust (`rust/`), C (`src/c_api/`), and CUDA (`cuda/`).

## Build Commands

FastLanes uses CMake 3.22+ with Ninja. On Linux/macOS it requires Clang >= 13. On Windows it uses MSVC (set up via `vcvarsall.bat`).

### Configure and build (Release with tests)
```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DFLS_BUILD_TESTING=ON
cmake --build build --parallel
```

### Run all tests
```bash
cd build && ctest -j4 --output-on-failure --timeout 300 -E QuickFuzz
```

### Run a single test by filter
```bash
build/test/src/dataset_tests/dataset_tests.exe --gtest_filter=FastLanesReaderTester.issue_000
```

### Run a single test target
```bash
cmake --build build --target unit_test && ctest -R unit_test --output-on-failure
```

### Key CMake options
| Option | Default | Purpose |
|--------|---------|---------|
| `FLS_BUILD_TESTING` | OFF | Build tests (fetches GoogleTest v1.15.2) |
| `FLS_BUILD_SHARED_LIBS` | OFF | Build as shared library (DLL) instead of static |
| `FLS_BUILD_BENCHMARKING` | OFF | Build benchmarks |
| `FLS_BUILD_PYTHON` | OFF | Build Python bindings |
| `FLS_BUILD_CUDA` | OFF | Build CUDA reader |
| `FLS_ENABLE_CLANG_TIDY` | OFF | Enable clang-tidy on all targets |

### Windows-specific (MSVC)

Invoke builds via a `.bat` that calls `vcvarsall.bat` first. Example pattern:
```bat
call "C:\Program Files\Microsoft Visual Studio\...\vcvarsall.bat" arm64
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DFLS_BUILD_TESTING=ON
cmake --build build --parallel
```

Test data can be cached across builds by setting `FASTLANES_DATA_DIR` environment variable to an existing data directory (e.g., `build_release/_deps/data-src`).

### Format code
The project uses `.clang-format` (LLVM base, tabs, 120-column limit). Run clang-format on changed files before committing.

## Architecture

### Public API

The main entry point is `fastlanes::Connection` (in `src/include/fls/connection.hpp`):
```cpp
auto conn = fastlanes::connect();
conn->read_csv("input/");       // ingest CSV
conn->to_fls("output/");        // write FastLanes format
auto reader = conn->read_fls("data.fls");  // read back
auto table = reader->materialize();
```

`TableReader` provides rowgroup-level random access. `RowgroupReader` decompresses individual rowgroups. The reader stack: `TableReader` → `RowgroupReader` → `RowgroupView` → `ColumnView` → `SegmentView`.

### Library structure

All source is under `src/`. Each subdirectory builds an OBJECT library that gets linked into the single `FastLanes` library target. Key components:

- **`cor/`** — Core: architecture detection, CPU features, layout (`Buf`), compression/decompression engines
- **`expression/`** — Expression-based encoding: physical expressions, operators (RLE, FSST, ALP, dict, delta, etc.), interpreter
- **`encoder/`** — High-level encoding pipeline, materializer (decompression)
- **`wizard/`** — Schema discovery: analyzes data and selects optimal encoding per column
- **`reader/`** — File reading: segments, column views, rowgroup views, table reader
- **`table/`** — In-memory table representation: `Rowgroup`, `Table`, `Vector`, typed columns
- **`footer/`** — FlatBuffers-generated metadata descriptors (table, rowgroup, column, segment)
- **`alp/`** — ALP (Adaptive Lossless Floating-Point) compression codec
- **`primitive/`** — Low-level primitives: bitpacking, patching, FSST string compression

### DLL / Shared library support (Windows)

The `FLS_API` macro in `src/include/fls/api/api.hpp` controls symbol visibility:
- `FLS_STATIC` defined → `FLS_API` is empty (static build)
- `FLS_BUILD_DLL` defined → `FLS_API` is `__declspec(dllexport)` (building the DLL)
- Neither defined → `FLS_API` is `__declspec(dllimport)` (consuming the DLL)

When `FLS_BUILD_SHARED_LIBS=ON`, `FLS_BUILD_DLL` is set directory-scoped via `add_compile_definitions` in `src/CMakeLists.txt` so all object libraries under `src/` get it. Test targets (under `test/`) don't get it, so `FLS_API` correctly resolves to `dllimport` for them.

Any public function or class that test code (or external consumers) calls across the DLL boundary must be marked `FLS_API`. For template functions, the explicit instantiations in the .cpp must also carry `FLS_API`.

Note: `WINDOWS_EXPORT_ALL_SYMBOLS` does NOT work for this project — the symbol count exceeds the 65535 .def file limit.

**MSVC dllexport gotchas:** MSVC eagerly instantiates all special member functions for `__declspec(dllexport)` classes. This causes two problems:

1. **Non-copyable members** (e.g., `vector<unique_ptr<T>>`): MSVC tries to generate copy ctor/assign and fails. Fix: explicitly `= delete` copy operations on the class.

2. **Incomplete types in unique_ptr**: MSVC tries to generate the destructor inline, which needs the complete type. Fix: either include the complete type's header, or declare the destructor in the header and define it `= default` in the .cpp where the type is complete.

### Type aliases

Defined in `src/include/fls/common/alias.hpp`:
- `n_t` = `uint64_t` (counts), `idx_t` = `uint32_t` (indices), `bw_t` = `uint8_t` (bit width)
- `up<T>` = `unique_ptr<T>`, `sp<T>` = `shared_ptr<T>`

### Test structure

Tests live in `test/src/` with six suites: `dataset_tests`, `expression_tests`, `fls_reader_tests`, `primitive_tests`, `quick_fuzz_tests`, `unit_tests`. All use GoogleTest. On MSVC, a `msvc_heap_guard` object library handles SEH guard-page exceptions that would otherwise cause spurious test failures.

## Code Style

- `.clang-tidy` is strict: `WarningsAsErrors: '*'` — all warnings are errors
- Types: `CamelCase`. Functions: `aNy_CasE`. Members: `lower_case` (private: `m_` prefix). Constants: `UPPER_CASE`. Typedefs: `lower_case` with `_t` suffix
- Tabs for indentation, 120-column limit
- PRs target `dev` branch
