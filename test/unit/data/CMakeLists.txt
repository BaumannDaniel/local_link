qt_add_executable(
        local_link_data_lib_unit_tests
        network/network_api_test.cpp
        test_util/network_api_mock.h test_util/network_api_mock.cpp
        test_util/tcp_server_adapter_mock.h test_util/tcp_server_adapter_mock.cpp
        test_util/tcp_socket_adapter_mock.h test_util/tcp_socket_adapter_mock.cpp
        test_util/udp_socket_adapter_mock.h test_util/udp_socket_adapter_mock.cpp
)

target_link_libraries(
        local_link_data_lib_unit_tests
        PRIVATE local_link_data_lib
        PRIVATE Qt::Test
        PRIVATE GTest::gtest_main
        PRIVATE GTest::gmock_main
)

gtest_discover_tests(local_link_data_lib_unit_tests)