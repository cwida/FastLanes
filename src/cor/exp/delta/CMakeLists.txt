add_library(fls_delta_exp
            OBJECT
            delta_exp.cpp)

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_delta_exp>
    PARENT_SCOPE)

if(ENABLE_IWYU)
	set_property(TARGET fls_delta_exp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()