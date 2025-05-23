import QtQuick
import QtQuick.Controls

Window {
    id: root

    color: "black"
    height: 600
    visible: true
    width: 600

    StackView {
        id: root_stack

        anchors.fill: parent
        initialItem: "home.qml"
    }
}