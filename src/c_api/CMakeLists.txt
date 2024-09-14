add_library(fls_c_api
        OBJECT
        c_api_connector.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_c_api>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_c_api PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()