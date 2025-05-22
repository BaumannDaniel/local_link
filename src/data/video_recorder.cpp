#include <QBuffer>
#include "video_recorder.h"

llink::VideoRecorder::VideoRecorder(QObject *parent) : QObject(parent) {
    media_capture_session_.setCamera(&camera_);
    media_capture_session_.setVideoSink(&video_sink_);
    connect(&video_sink_, &QVideoSink::videoFrameChanged, this, &VideoRecorder::processFrame);
}

void llink::VideoRecorder::processFrame(const QVideoFrame &video_frame) {
    if (!video_frame.isValid()) return;
    auto video_frame_copy = video_frame;
    video_frame_copy.map(QVideoFrame::ReadOnly);
    QImage image = video_frame.toImage();
    video_frame_copy.unmap();
    const auto image_ptr = QSharedPointer<QImage>::create(std::move(image));
    emit newFrame(image_ptr);
}

void llink::VideoRecorder::start() {
    camera_.start();
}

void llink::VideoRecorder::stop() {
    camera_.stop();
}
