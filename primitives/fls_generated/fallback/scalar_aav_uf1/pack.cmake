add_library(fallback_scalar_aav_1024_uf1_pack OBJECT
        fallback_scalar_aav_1024_uf1_pack_src.cpp)
target_compile_definitions(fallback_scalar_aav_1024_uf1_pack PRIVATE IS_SCALAR)

LIST(APPEND FLS_GENERATED_OBJECT_FILES
        $<TARGET_OBJECTS:fallback_scalar_aav_1024_uf1_pack>)
