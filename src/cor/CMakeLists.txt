add_subdirectory(eng)
add_subdirectory(exp)
add_subdirectory(lyt)
add_subdirectory(prm)


add_library(fls_cor
        OBJECT
        #        compression_plan_history.cpp
        cpu.cpp
        exp_pool.cpp
        mtd.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_cor>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_cor PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
