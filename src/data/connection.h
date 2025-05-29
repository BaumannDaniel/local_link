#pragma once
#include <QSharedPointer>

#include "network/tcp_socket_adapter.h"

namespace llink {
    class Connection : public QObject {
        Q_OBJECT
        QSharedPointer<ITcpSocketAdapter> i_tcp_socket_adapter_ptr_;
        QByteArray data_stream_buffer;
        quint32 remaining_bytes_in_message = 0;

    private slots:
        void processDataStream();

    signals:
        void videoFrameReceived(QSharedPointer<QImage> video_frame_ptr);

    public:
        explicit Connection(QSharedPointer<ITcpSocketAdapter> i_tcp_socket_adapter_ptr, QObject *parent = nullptr);

        void sendVideoFrame(const QSharedPointer<QImage> &video_frame_ptr) const;
    };
}
