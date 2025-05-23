qt_add_library(local_link_ui_lib STATIC
        UsersListModel.h UsersListModel.cpp
        video_frame_painted_item.h video_frame_painted_item.cpp
        video_model.h video_model.cpp
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
