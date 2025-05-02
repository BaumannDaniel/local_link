import QtQuick
import QtQuick.Controls


Window {
    color: "black"
    height: 600
    visible: true
    width: 600

    ListView {
        height: parent.height
        width: parent.width
        model: users_list_model

        delegate: Rectangle {
            height: 100
            width: parent.width
            radius: 10
            border.color: "white"
            border.width: 1
            color: Qt.rgba(1, 1, 1, 0.1)

            Row {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 10

                Text {
                    color: "white"
                    font.bold: true
                    font.pointSize: 16
                    text: name
                }

                Rectangle {

                }
                Button {
                    text: "Call"

                    onClicked: {
                        console.log("Calling", name);
                    }
                }
            }

            // Optional hover effect
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true

                onEntered: parent.color = Qt.rgba(1, 1, 1, 0.2)
                onExited: parent.color = Qt.rgba(1, 1, 1, 0.1)
            }
        }
    }
}