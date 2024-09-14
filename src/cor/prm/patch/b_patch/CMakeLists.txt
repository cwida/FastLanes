add_library(fls_b_patch_prm
            OBJECT
            b_patch_decompress.cpp
            b_patch_compress.cpp)

target_compile_definitions(fls_b_patch_prm PRIVATE IS_SCALAR)
target_compile_options(fls_b_patch_prm PRIVATE "")
if (ENABLE_IWYU)
    set_target_properties(fls_b_patch_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
set_target_properties(fls_b_patch_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_b_patch_prm>
        PARENT_SCOPE)