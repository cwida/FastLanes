add_library(fls_rle_prm
            OBJECT
            rle_decompress.cpp
            rle_compress.cpp)

if(ENABLE_IWYU)
	set_target_properties(fls_rle_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(fls_rle_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_rle_prm>
    PARENT_SCOPE)