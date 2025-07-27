set(GALP_CORE_SOURCES
        alp/alp-bindings.cu
        engine/enums.cu
)
add_library(galp_core STATIC ${GALP_CORE_SOURCES})
target_compile_options(galp_core PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-expt-relaxed-constexpr>)
target_include_directories(galp_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CUDAToolkit_INCLUDE_DIRS})
target_link_libraries(galp_core PUBLIC CUDA::cudart nvcomp::nvcomp Thrust::Thrust FastLanes::core)
apply_warnings(galp_core)
set_target_properties(galp_core PROPERTIES CUDA_SEPARABLE_COMPILATION ON)