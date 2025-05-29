#pragma once
#include <QHostAddress>
#include <QObject>

#include "network/network_api.h"
#include "video_recorder.h"

namespace llink {
    class CallManager : public QObject {
        Q_OBJECT
        QSharedPointer<INetworkApi> network_api_ptr_;
        QSharedPointer<Connection> current_connection_ptr_ = nullptr;
        QSharedPointer<VideoRecorder> video_recorder_ptr_ = nullptr;

    private slots:
        void handleNewConnection(const QSharedPointer<Connection> &connection_ptr);

        void sendVideoFrame(const QSharedPointer<QImage> &video_frame_ptr);

    signals:
        void videoFrameReceived(QSharedPointer<QImage> frame);

    public:
        explicit CallManager(
            const QSharedPointer<INetworkApi> &network_api_ptr,
            const QSharedPointer<VideoRecorder> &video_recorder_ptr,
            QObject *parent = nullptr
            );

        void startCall(QHostAddress host_address);
    };
}
