#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

#include "tcp_socket_adapter.h"

namespace llink {
    class ITcpServerAdapter : public QObject {
        Q_OBJECT

    signals:
        void newConnection();

    public:
        static constexpr quint16 SOCKET_PORT = 10051;

        explicit ITcpServerAdapter(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual QSharedPointer<ITcpSocketAdapter> nextPendingConnection() const = 0;
    };

    class TcpServerAdapter : public ITcpServerAdapter {
        QTcpServer *tcp_server_ptr_;

    public:
        TcpServerAdapter();

        QSharedPointer<ITcpSocketAdapter> nextPendingConnection() const override;
    };
}
