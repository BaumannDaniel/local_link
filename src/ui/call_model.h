#pragma once

#include <QObject>

#include "video_recorder.h"

namespace llink {
    class CallModel : public QObject {
        Q_OBJECT
        QSharedPointer<VideoRecorder> video_recorder_ptr_;
        QSharedPointer<QImage> current_frame_ptr_;

        signals:
            void frameUpdated(QSharedPointer<QImage> frame);

    public:
        explicit CallModel(const QSharedPointer<VideoRecorder> &video_recorder_ptr, QObject *parent = nullptr);
    };
}
