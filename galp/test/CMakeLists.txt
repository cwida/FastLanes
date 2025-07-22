add_executable(galp_tests
        thrust_memcpy_test.cu
        thrust_core_test.cu
        galp_test.cu
)


target_link_libraries(galp_tests PRIVATE
        galp_core
        GTest::gtest_main
        FastLanes::core
)

apply_warnings(galp_tests)

gtest_discover_tests(galp_tests
        DISCOVERY_TIMEOUT 60
)