#pragma once
#include <QObject>
#include <QVideoFrame>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>

namespace llink {
    class VideoRecorder : public QObject {
        Q_OBJECT
        QCamera camera_;
        QMediaCaptureSession media_capture_session_;
        QVideoSink video_sink_;

    signals:
        void newFrame(const QVideoFrame &video_frame);

    public:
        explicit VideoRecorder(QObject *parent = nullptr);

        void start();

        void stop();
    };
}
