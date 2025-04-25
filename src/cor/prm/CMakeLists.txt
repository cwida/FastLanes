add_subdirectory(fsst)
add_subdirectory(fsst12)

add_library(fls_all_prms
        OBJECT
        prm.cpp
        type.cpp)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_all_prms>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_all_prms PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

