add_subdirectory(b_patch)
add_subdirectory(ll_patch)
add_subdirectory(s_patch)

add_library(patch_prm
            OBJECT
            patch.cpp)

target_compile_definitions(patch_prm PRIVATE IS_SCALAR)
target_compile_options(patch_prm PRIVATE "")
if(ENABLE_IWYU)
	set_target_properties(patch_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(patch_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:patch_prm>
    PARENT_SCOPE)
