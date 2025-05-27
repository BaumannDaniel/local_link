import QtQuick
import QtQuick.Controls
import llink 1.0

Item {
    VideoFrameItem {
        id: local_video_frame

        width: 160
        height: 90
    }

    VideoFrameItem {
        id: remote_video_frame

        anchors.top: local_video_frame.bottom
        height: 180
        width: 320
    }

    Button {
        text: qsTr("Close Call")

        anchors.top: remote_video_frame.bottom
        onClicked: {
            if (localFrameUpdateCallback) {
                call_model.localFrameUpdated.disconnect(localFrameUpdateCallback);
                localFrameUpdateCallback = null;
            }
            if (remoteFrameUpdateCallback) {
                call_model.remoteFrameUpdated.disconnect(remoteFrameUpdateCallback);
                remoteFrameUpdateCallback = null;
            }
            root_stack.pop();
        }
    }

    property var localFrameUpdateCallback: null
    property var remoteFrameUpdateCallback: null

    Component.onCompleted: {
        localFrameUpdateCallback = function (frame) {
            local_video_frame.setCurrentFrame(frame);
        };
        call_model.localFrameUpdated.connect(localFrameUpdateCallback);

        remoteFrameUpdateCallback = function (frame) {
            remote_video_frame.setCurrentFrame(frame);
        };
        call_model.remoteFrameUpdated.connect(remoteFrameUpdateCallback);
    }
}