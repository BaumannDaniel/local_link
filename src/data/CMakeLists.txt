qt_add_library(local_link_data_lib
        user.h
        user_repository.h user_repository.cpp
        user_scanner.h user_scanner.cpp
)

target_include_directories(
        local_link_data_lib
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(local_link_data_lib PUBLIC
        Qt::Core
        Qt::Network
)