qt_add_library(local_link_ui_lib STATIC
        call_model.h call_model.cpp
        users_list_model.h users_list_model.cpp
        video_frame_item.h video_frame_item.cpp
)

target_link_libraries(local_link_ui_lib PUBLIC
        local_link_data_lib
        Qt::Gui
        Qt::Multimedia
        Qt::Qml
        Qt::Quick
)

set(local_link_ui_resource_files
        "qml/call.qml"
        "qml/home.qml"
        "qml/root.qml"
)

qt_add_resources(local_link_ui_lib "local_link_ui"
        PREFIX "/"
        FILES ${local_link_ui_resource_files}
)
