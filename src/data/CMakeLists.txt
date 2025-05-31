qt_add_library(local_link_data_lib STATIC
        network/network_api.h network/network_api.cpp
        network/network_model.h
        network/tcp_server_adapter.h network/tcp_server_adapter.cpp
        network/tcp_socket_adapter.h network/tcp_socket_adapter.cpp
        network/udp_socket_adapter.h network/udp_socket_adapter.cpp
        call_manager.h call_manager.cpp
        connection.h connection.cpp
        user.h
        user_repository.h user_repository.cpp
        user_status_manager.h user_status_manager.cpp
        video_recorder.h video_recorder.cpp
)

target_include_directories(
        local_link_data_lib
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(local_link_data_lib PUBLIC
        Qt::Core
        Qt::Network
        Qt6::Multimedia
)
