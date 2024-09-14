add_library(fls_b_ffor_prm
            OBJECT
            b_ffor_decompress.cpp
            b_ffor_compress.cpp)

if(ENABLE_IWYU)
	set_target_properties(fls_b_ffor_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(fls_b_ffor_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_b_ffor_prm>
    PARENT_SCOPE)