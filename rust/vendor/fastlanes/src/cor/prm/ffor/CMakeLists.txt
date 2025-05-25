add_library(fls_ffor_prm
            OBJECT
            ffor_decompress.cpp
            ffor_compress.cpp
            ffor_analyze.cpp)

if(ENABLE_IWYU)
	set_target_properties(fls_ffor_prm PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()
set_target_properties(fls_ffor_prm PROPERTIES CXX_CLANG_TIDY "")

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_ffor_prm>
    PARENT_SCOPE)