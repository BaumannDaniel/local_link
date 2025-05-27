#pragma once

#include <QObject>

#include "call_manager.h"
#include "video_recorder.h"

namespace llink {
    class CallModel : public QObject {
        Q_OBJECT
        QSharedPointer<VideoRecorder> video_recorder_ptr_;
        QSharedPointer<CallManager> call_manager_ptr_;

    signals:
        void localFrameUpdated(QSharedPointer<QImage> frame);

        void remoteFrameUpdated(QSharedPointer<QImage> frame);

    public:
        explicit CallModel(
            const QSharedPointer<VideoRecorder> &video_recorder_ptr,
            const QSharedPointer<CallManager> &call_manager_ptr,
            QObject *parent = nullptr
        );
    };
}
