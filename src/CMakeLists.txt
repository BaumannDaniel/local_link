add_subdirectory(ui)
qt_add_executable(local_link app.cpp)

target_link_libraries(
        local_link
        PRIVATE local_link_ui
)