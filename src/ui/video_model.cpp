#include "video_model.h"

llink::VideoModel::VideoModel(const QSharedPointer<VideoRecorder> &video_recorder_ptr, QObject *parent)
    : QObject(parent),
      video_recorder_ptr_(video_recorder_ptr) {
    connect(video_recorder_ptr_.get(), &VideoRecorder::newFrame,
            this, &VideoModel::frameUpdated);
}
