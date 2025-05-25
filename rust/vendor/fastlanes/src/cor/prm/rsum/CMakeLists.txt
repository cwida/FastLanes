add_library(fls_rsum_prm
            OBJECT
            rsum_decompress.cpp
            rsum_compress.cpp)

if(ENABLE_IWYU)
	set_target_properties(fls_rsum_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(fls_rsum_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_rsum_prm>
    PARENT_SCOPE)