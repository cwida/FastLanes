add_library(fls_ll_patch_prm
            OBJECT
            ll_patch_decompress.cpp
            ll_patch_compress.cpp)

target_compile_definitions(fls_ll_patch_prm PRIVATE IS_SCALAR)
target_compile_options(fls_ll_patch_prm PRIVATE "")

if(ENABLE_IWYU)
	set_target_properties(fls_ll_patch_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(fls_ll_patch_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_ll_patch_prm>
    PARENT_SCOPE)