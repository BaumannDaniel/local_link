#include "call_model.h"

llink::CallModel::CallModel(
    const QSharedPointer<VideoRecorder> &video_recorder_ptr,
    const QSharedPointer<CallManager> &call_manager_ptr,
    QObject *parent
)
    : QObject(parent),
      video_recorder_ptr_(video_recorder_ptr),
      call_manager_ptr_(call_manager_ptr) {
    connect(video_recorder_ptr_.get(), &VideoRecorder::newFrame,
            this, &CallModel::localFrameUpdated);
    connect(call_manager_ptr_.get(), &CallManager::videoFrameReceived,
            this, &CallModel::remoteFrameUpdated);
}
