add_library(fls_fsst12_exp
            OBJECT
            fsst12_exp.cpp)

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_fsst12_exp>
    PARENT_SCOPE)

if(ENABLE_IWYU)
	set_property(TARGET fls_fsst12_exp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()