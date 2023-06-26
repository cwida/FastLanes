#add_subdirectory(neon_intrinsic_uf8)
#add_subdirectory(neon_intrinsic_uf4)
#add_subdirectory(neon_intrinsic_uf2)
add_subdirectory(neon_intrinsic_uf1)
#add_subdirectory(neon_iu8lp_uf1) [todo]
#add_subdirectory(unit64_av_uf1)
#add_subdirectory(unit64_aav_uf1)
#add_subdirectory(scalar_av_uf1)
#add_subdirectory(scalar_aav_uf1)
add_subdirectory(sve_intrinsic_uf1)
#add_subdirectory(sse_to_neon_uf1) [todo]

add_library(generated_arm64v8
            OBJECT
            arm64v8.cpp)

SET(FLS_GENERATED_OBJECT_FILES
    ${FLS_GENERATED_OBJECT_FILES} $<TARGET_OBJECTS:generated_arm64v8> PARENT_SCOPE)