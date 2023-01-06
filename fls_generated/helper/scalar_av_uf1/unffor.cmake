add_library(helper_scalar_av_1024_uf1_unffor OBJECT
            helper_scalar_av_1024_uf1_unffor_src.cpp)
target_compile_definitions(helper_scalar_av_1024_uf1_unffor PRIVATE IS_SCALAR)
set(FLAG -O3)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(helper_scalar_av_1024_uf1_unffor PUBLIC ${FLAG})
cmake_print_properties(TARGETS helper_scalar_av_1024_uf1_unffor
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:helper_scalar_av_1024_uf1_unffor>)
get_target_property(TARGET_NAME helper_scalar_av_1024_uf1_unffor NAME)
get_target_property(TARGET_COMPILE_OPTIONS helper_scalar_av_1024_uf1_unffor COMPILE_OPTIONS)
