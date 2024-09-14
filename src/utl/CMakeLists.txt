add_subdirectory(cpu)

add_library(fls_utl
        OBJECT
        bit_util.cpp
        #[[]]
        env.cpp
        random.cpp
        util.cpp
)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_utl PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_utl>
        PARENT_SCOPE)
