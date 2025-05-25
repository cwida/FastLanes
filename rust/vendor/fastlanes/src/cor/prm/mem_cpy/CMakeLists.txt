add_library(fls_mem_cpy_exp
            OBJECT
            mem_cpy_decompress.cpp
            mem_cpy_compress.cpp)

target_compile_definitions(fls_mem_cpy_exp PRIVATE IS_SCALAR)
target_compile_options(fls_mem_cpy_exp PRIVATE "")
if(ENABLE_IWYU)
    set_target_properties(fls_mem_cpy_exp PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(fls_mem_cpy_exp PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_mem_cpy_exp>
    PARENT_SCOPE)