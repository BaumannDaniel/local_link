#include "video_recorder.h"

llink::VideoRecorder::VideoRecorder(QObject *parent) : QObject(parent) {
    media_capture_session_.setCamera(&camera_);
    media_capture_session_.setVideoSink(&video_sink_);
    connect(&video_sink_, &QVideoSink::videoFrameChanged, this, &VideoRecorder::newFrame);
}

void llink::VideoRecorder::start() {
    camera_.start();
}

void llink::VideoRecorder::stop() {
    camera_.stop();
}
