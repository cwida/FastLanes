add_subdirectory(ffor)
add_subdirectory(predicate)
add_subdirectory(unffor)
add_subdirectory(untraspose)


add_library(fls_primitive
        OBJECT
        #
        primitive.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitive>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_primitive PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()