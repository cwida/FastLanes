## ────────────────────────────────────────────────
## Generated-bindings library
## ────────────────────────────────────────────────
set(GALP_GENERATED_BINDINGS_SOURCES
        generated-bindings/alp-double-decompress_column-bindings.cu
        generated-bindings/alp-double-query_column-bindings.cu
        generated-bindings/alp-double-query_multi_column-bindings.cu
        generated-bindings/alp-float-decompress_column-bindings.cu
        generated-bindings/alp-float-query_column-bindings.cu
        generated-bindings/alp-float-query_multi_column-bindings.cu
        generated-bindings/alpextended-double-decompress_column-bindings.cu
        generated-bindings/alpextended-double-query_column-bindings.cu
        generated-bindings/alpextended-double-query_multi_column-bindings.cu
        generated-bindings/alpextended-float-decompress_column-bindings.cu
        generated-bindings/alpextended-float-query_column-bindings.cu
        generated-bindings/alpextended-float-query_multi_column-bindings.cu
        generated-bindings/bp-uint32_t-decompress_column-bindings.cu
        generated-bindings/bp-uint32_t-query_column-bindings.cu
        generated-bindings/bp-uint64_t-decompress_column-bindings.cu
        generated-bindings/bp-uint64_t-query_column-bindings.cu
        generated-bindings/ffor-uint32_t-compute_column-bindings.cu
        generated-bindings/ffor-uint32_t-decompress_column-bindings.cu
        generated-bindings/ffor-uint32_t-query_column-bindings.cu
        generated-bindings/ffor-uint32_t-query_multi_column-bindings.cu
        generated-bindings/ffor-uint64_t-compute_column-bindings.cu
        generated-bindings/ffor-uint64_t-decompress_column-bindings.cu
        generated-bindings/ffor-uint64_t-query_column-bindings.cu
        generated-bindings/ffor-uint64_t-query_multi_column-bindings.cu
)
add_library(generated-bindings STATIC ${GALP_GENERATED_BINDINGS_SOURCES})
target_compile_options(generated-bindings PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-expt-relaxed-constexpr>)
target_include_directories(generated-bindings PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CUDAToolkit_INCLUDE_DIRS})
target_link_libraries(generated-bindings PUBLIC CUDA::cudart nvcomp::nvcomp Thrust::Thrust galp_core)
apply_warnings(generated-bindings)
set_target_properties(generated-bindings PROPERTIES CUDA_SEPARABLE_COMPILATION ON)


add_executable(compressors-benchmarks compressors-benchmarks.cu nvcomp/benchmark-compressors.cu nvcomp/nvcomp-compressors.cu)
apply_warnings(compressors-benchmarks)
target_link_libraries(compressors-benchmarks PRIVATE galp_core)

add_executable(micro-benchmarks micro-benchmarks.cu nvcomp/benchmark-compressors.cu nvcomp/nvcomp-compressors.cu)
apply_warnings(micro-benchmarks)
target_link_libraries(micro-benchmarks PRIVATE galp_core generated-bindings)
