add_library(fls_dict_exp
            OBJECT
            dict_exp.cpp)

set(FASTLANES_OBJECT_FILES
    ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_dict_exp>
    PARENT_SCOPE)

if(ENABLE_IWYU)
	set_property(TARGET fls_dict_exp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif()