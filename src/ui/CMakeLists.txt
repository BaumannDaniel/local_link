qt_add_library(local_link_ui_lib
        UsersListModel.h UsersListModel.cpp
)

target_link_libraries(local_link_ui_lib PUBLIC
        local_link_data_lib
        Qt::Gui
        Qt::Multimedia
        Qt::Qml
        Qt::Quick
)

set(local_link_ui_resource_files
        "qml/home.qml"
)

qt_add_resources(local_link_ui_lib "local_link_ui"
        PREFIX "/"
        FILES ${local_link_ui_resource_files}
)