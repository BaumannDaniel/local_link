#pragma once
#include <qobject.h>
#include <QTcpSocket>

namespace llink {
    class ITcpSocketAdapter : public QObject {
        Q_OBJECT

    signals:
        void readyRead();

    public:
        static constexpr quint16 SOCKET_PORT = 10051;

        explicit ITcpSocketAdapter(QObject *parent = nullptr) : QObject(parent) {
        }
    };

    class TcpSocketAdapter : public ITcpSocketAdapter {
        QTcpSocket *tcp_socket_ptr_;

    public:
        TcpSocketAdapter();

        quint64 write(const QByteArray &byte_array) const;
    };
}
