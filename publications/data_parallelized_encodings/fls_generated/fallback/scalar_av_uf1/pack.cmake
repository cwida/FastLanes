add_library(fallback_scalar_av_1024_uf1_pack OBJECT
            fallback_scalar_av_1024_uf1_pack_src.cpp)
target_compile_definitions(fallback_scalar_av_1024_uf1_pack PRIVATE IS_SCALAR)
set(FLAG -fno-builtin -O3)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
   message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(fallback_scalar_av_1024_uf1_pack PUBLIC ${FLAG})
cmake_print_properties(TARGETS fallback_scalar_av_1024_uf1_pack
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST(APPEND FLS_GENERATED_OBJECT_FILES
     $<TARGET_OBJECTS:fallback_scalar_av_1024_uf1_pack>)
get_target_property(TARGET_NAME fallback_scalar_av_1024_uf1_pack NAME)
get_target_property(TARGET_COMPILE_OPTIONS fallback_scalar_av_1024_uf1_pack COMPILE_OPTIONS)
