qt_add_library(local_link_data_lib STATIC
        network_api.h network_api.cpp
        network_message.h
        tcp_socket_adapter.h tcp_socket_adapter.cpp
        udp_socket_adapter.h udp_socket_adapter.cpp
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
