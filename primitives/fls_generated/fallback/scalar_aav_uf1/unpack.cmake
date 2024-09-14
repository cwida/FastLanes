add_library(fallback_scalar_aav_1024_uf1_unpack OBJECT
        fallback_scalar_aav_1024_uf1_unpack_src.cpp)
target_compile_definitions(fallback_scalar_aav_1024_uf1_unpack PRIVATE IS_SCALAR)

LIST(APPEND FLS_GENERATED_OBJECT_FILES
        $<TARGET_OBJECTS:fallback_scalar_aav_1024_uf1_unpack>)
#------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING)
    #    add_executable(fallback_scalar_aav_1024_uf1_unpack_test fallback_scalar_aav_1024_uf1_unpack_test.cpp)
    #    target_link_libraries(fallback_scalar_aav_1024_uf1_unpack_test PRIVATE fallback_scalar_aav_1024_uf1_unpack)
    #    target_link_libraries(fallback_scalar_aav_1024_uf1_unpack_test PRIVATE fallback_scalar_aav_1024_uf1_pack fallback_scalar_aav_1024_uf1_ffor)
    #    target_link_libraries(fallback_scalar_aav_1024_uf1_unpack_test PRIVATE gtest_main)
    #    target_include_directories(fallback_scalar_aav_1024_uf1_unpack_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    #    gtest_discover_tests(fallback_scalar_aav_1024_uf1_unpack_test)
endif ()
