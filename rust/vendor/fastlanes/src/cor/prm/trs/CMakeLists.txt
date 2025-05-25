add_library(fls_trs_prm
            OBJECT
            trs_decompress.cpp
            trs_compress.cpp)

target_compile_definitions(fls_trs_prm PRIVATE IS_SCALAR)
target_compile_options(fls_trs_prm PRIVATE "")
if(ENABLE_IWYU)
    set_target_properties(fls_trs_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(fls_trs_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_trs_prm>
    PARENT_SCOPE)