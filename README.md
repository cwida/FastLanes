# <div align="center"> The FastLanes Compression Layout: </div>
## <div align="center"> Decoding >100 Billion Integers per Second with Scalar Code  </div>

## FastLanes:
FastLanes is a project initiated at CWI, intended as a foundation for next-generation big data formats.
In this first paper on FastLanes, we focus on significantly improving data decoding performance
over the state-of-the art.
in a follow-up we will discuss improvements in compression ratio, as well.
It introduces a new layout for compressed columnar data, that increases the opportunities for data-parallel decoding,
improving performance by factors.
It does so in a way that works across the heterogeneous and evolving Instruction Set Architectures (ISAs) landscape,
is future-proof, and minimizes technical debt by relying on scalar-only code.

## How to Build:
### Requirements: 
1) __Clang++__
2) __CMake__ 3.20 or higher


### Run:

```shell
    mkdir build ; cd build
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../fls_toolchain/example.cmake ..
    make
```


## How to Run:

The Fastlanes primitives are implemented for the following architectures and ISA extensions:

| Architecture | ISA     |
|--------------|---------|
| arm64v8      | NEON    |
| arm64v8      | SVE     |
| wasm         | SIMD128 |
| x86_64       | SSE     |
| x86_64       | AVX2    |
| x86_64       | AVX512F |

## 3.1 Micro-benchmarks

---
### Bit-Unpacking

Find the source file for each implementation at:

| Implementation | Source File                                                                                              |
|----------------|----------------------------------------------------------------------------------------------------------|
| Scalar         | `fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_unpack_src.cpp`                      |
| Scalar_T64     | `fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_unpack_src.cpp`               |
| SIMD           | `fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_unpack_src.cpp` |
| Auto-Vectorized| `fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_unpack_src.cpp`                      |


Test each implementation by running: 

| Implementation | Command                                                                                                 |
|----------------|---------------------------------------------------------------------------------------------------------|
| Scalar         | `./fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_unpack_test`                      |
| Scalar_T64     | `./fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_unpack_test`               |
| SIMD           | `./fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_unpack_test` |
| Auto-Vectorized| `./fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_unpack_test`                      |


Benchmark each implementation by running:


| Implementation | Command                                                                                                  |
|----------------|----------------------------------------------------------------------------------------------------------|
| Scalar         | `./fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_unpack_bench`                      |
| Scalar_T64     | `./fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_unpack_bench`               |
| SIMD           | `./fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_unpack_bench` |
| Auto-Vectorized| `./fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_unpack_bench`                      |


---
### Delta Coding

Find the source file for each implementation at:

| Implementation | Source File                                                                                            |
|----------------|--------------------------------------------------------------------------------------------------------|
| Scalar         | `fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_rsum_src.cpp`                      |
| Scalar_T64     | `fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_rsum_src.cpp`               |
| SIMD           | `fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_rsum_src.cpp` |
| Auto-Vectorized| `fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_rsum_src.cpp`                      |


Test each implementation by running:

| Implementation | Command                                                                                               |
|----------------|-------------------------------------------------------------------------------------------------------|
| Scalar         | `./fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_rsum_test`                      |
| Scalar_T64     | `./fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_rsum_test`               |
| SIMD           | `./fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_rsum_test` |
| Auto-Vectorized| `./fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_rsum_test`                      |


Benchmark each implementation by running:


| Implementation | Command                                                                                                |
|----------------|--------------------------------------------------------------------------------------------------------|
| Scalar         | `./fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_rsum_bench`                      |
| Scalar_T64     | `./fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_rsum_bench`               |
| SIMD           | `./fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_rsum_bench` |
| Auto-Vectorized| `./fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_rsum_bench`                      |



---
### FUSED FOR+Bitpack

Find the source file for each implementation at:

| Implementation | Source File                                                                                            |
|----------------|--------------------------------------------------------------------------------------------------------|
| Scalar         | `fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_ffor_src.cpp`                      |
| Scalar_T64     | `fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_ffor_src.cpp`               |
| SIMD           | `fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_ffor_src.cpp` |
| Auto-Vectorized| `fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_ffor_src.cpp`                      |


Test each implementation by running:

| Implementation | Command                                                                                               |
|----------------|-------------------------------------------------------------------------------------------------------|
| Scalar         | `./fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_ffor_test`                      |
| Scalar_T64     | `./fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_ffor_test`               |
| SIMD           | `./fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_ffor_test` |
| Auto-Vectorized| `./fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_ffor_test`                      |


Benchmark each implementation by running:


| Implementation | Command                                                                                                |
|----------------|--------------------------------------------------------------------------------------------------------|
| Scalar         | `./fls_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_ffor_bench`                      |
| Scalar_T64     | `./fls_generated/fallback/unit64_nav_uf1/fallback_unit64_scalar_nav_1024_uf1_ffor_bench`               |
| SIMD           | `./fls_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_ffor_bench` |
| Auto-Vectorized| `./fls_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_ffor_bench`                      |


