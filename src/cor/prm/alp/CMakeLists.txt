add_library(fls_alp_prm
        OBJECT
        alp_decompress.cpp
        alp_compress.cpp)

if (ENABLE_IWYU)
    set_target_properties(fls_alp_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
set_target_properties(fls_alp_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_alp_prm>
        PARENT_SCOPE)