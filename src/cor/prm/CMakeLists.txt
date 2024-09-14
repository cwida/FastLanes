add_subdirectory(alp)
add_subdirectory(b_ffor)
add_subdirectory(bitpack)
add_subdirectory(factor)
add_subdirectory(ffor)
add_subdirectory(fsst)
add_subdirectory(fsst12)
add_subdirectory(mem_cpy)
add_subdirectory(mem_trs)
add_subdirectory(patch)
add_subdirectory(rle)
add_subdirectory(rsum)
add_subdirectory(trs)

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

