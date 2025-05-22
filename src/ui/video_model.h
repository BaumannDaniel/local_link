#pragma once

#include <QObject>

#include "video_recorder.h"

namespace llink {
    class VideoModel : public QObject {
        Q_OBJECT
        QSharedPointer<VideoRecorder> video_recorder_ptr_;
        QSharedPointer<QImage> current_frame_ptr_;

        signals:
            void frameUpdated(QSharedPointer<QImage> frame);

    public:
        explicit VideoModel(const QSharedPointer<VideoRecorder> &video_recorder_ptr, QObject *parent = nullptr);
    };
}
