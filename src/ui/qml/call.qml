import QtQuick
import QtQuick.Controls
import llink 1.0

Item {
    VideoFrameItem {
        id: local_video_frame

        width: 160
        height: 90
    }

    property var frameUpdateCallback: null

    Component.onCompleted: {
        frameUpdateCallback = function (frame) {
            local_video_frame.setCurrentFrame(frame);
        };
        call_model.frameUpdated.connect(frameUpdateCallback);
    }

    Button {
        text: qsTr("Close Call")
        onClicked: {
            if (frameUpdateCallback) {
                call_model.frameUpdated.disconnect(frameUpdateCallback);
                frameUpdateCallback = null;
            }
            root_stack.pop();
        }
    }
}