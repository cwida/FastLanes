add_subdirectory(avx2_intrinsic_uf1)
add_subdirectory(avx512bw_intrinsic_uf1)
add_subdirectory(sse_intrinsic_uf1)

set(FLS_GENERATED_OBJECT_FILES
    ${FLS_GENERATED_OBJECT_FILES}
    PARENT_SCOPE)