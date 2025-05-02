qt_add_library(local_link_ui
        users_list_model.h users_list_model.cpp
)

target_link_libraries(local_link_ui PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Multimedia
        Qt::Qml
        Qt::Quick
)

set(local_link_ui_resource_files
        "qml/home.qml"
)

qt_add_resources(local_link_ui "local_link_ui"
        PREFIX "/"
        FILES ${local_link_ui_resource_files}
)