qt_add_executable(
        local_link_data_lib_unit_tests
        mocks/network_api_mock.h mocks/network_api_mock.cpp
        mocks/udp_socket_adapter_mock.h mocks/udp_socket_adapter_mock.cpp
        network_api_test.cpp
)

target_link_libraries(
        local_link_data_lib_unit_tests
        PRIVATE local_link_data_lib
        PRIVATE Qt::Test
        PRIVATE GTest::gtest_main
        PRIVATE GTest::gmock_main
)

gtest_discover_tests(local_link_data_lib_unit_tests)