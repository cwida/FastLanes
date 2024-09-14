add_subdirectory(dic)
add_subdirectory(page)

add_library(fls_lyt
        OBJECT
        buf.cpp
        #
        col.cpp
        vec.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_lyt>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_lyt PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
