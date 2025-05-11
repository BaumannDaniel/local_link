import QtQuick
import QtQuick.Controls

Window {
    color: "black"
    height: 600
    visible: true
    width: 600

    Button {
        id: scan_button
        text: qsTr("Scan")
        onClicked: {
            users_list_model.scan_users();
        }
    }

    ListView {
        height: parent.height
        model: users_list_model
        width: parent.width
        anchors.top: scan_button.bottom

        delegate: Rectangle {
            border.color: "white"
            border.width: 1
            color: Qt.rgba(1, 1, 1, 0.1)
            height: 50
            radius: 10
            width: parent.width

            Text {
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
                font.bold: true
                font.pointSize: 16
                text: name
            }
            Button {
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
                font.pointSize: 14
                padding: 8
                text: qsTr("Call")

                background: Rectangle {
                    border.color: "#A5D6A7"
                    border.width: 1
                    color: "#4CAF50"
                    radius: 6

                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true

                        onEntered: parent.color = "#388E3C"
                        onExited: parent.color = "#4CAF50"
                    }
                }

                onClicked: {
                    console.log("Calling", name);
                }
            }
        }
    }
}