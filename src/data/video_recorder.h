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

    private slots:
        void processFrame(const QVideoFrame &video_frame);

    signals:
        void newFrame(QSharedPointer<QImage> frame);

    public:
        explicit VideoRecorder(QObject *parent = nullptr);

        void start();

        void stop();
    };
}
