import QtQuick
import QtQuick.Controls
import llink 1.0

Item {
    VideoFramePaintedItem {
        id: local_video_painted_item

        width: 160
        height: 90
    }

    property var frameUpdateCallback: null

    Component.onCompleted: {
        frameUpdateCallback = function (frame) {
            local_video_painted_item.setCurrentFrame(frame);
        };
        video_model.frameUpdated.connect(frameUpdateCallback);
    }

    Button {
        text: qsTr("Close Call")
        onClicked: {
            if (frameUpdateCallback) {
                video_model.frameUpdated.disconnect(frameUpdateCallback);
                frameUpdateCallback = null;
            }
            root_stack.pop();
        }
    }
}