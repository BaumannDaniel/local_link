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
        explicit ITcpServerAdapter(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual QSharedPointer<ITcpSocketAdapter> nextPendingConnection() const = 0;

        virtual bool listen(const QHostAddress &host_address, quint16 port) = 0;
    };

    class TcpServerAdapter : public ITcpServerAdapter {
        QTcpServer *tcp_server_ptr_;

    public:
        TcpServerAdapter(QObject *parent = nullptr);

        QSharedPointer<ITcpSocketAdapter> nextPendingConnection() const override;

        bool listen(const QHostAddress &host_address, quint16 port) override;
    };
}
