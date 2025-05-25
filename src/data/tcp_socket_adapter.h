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

        virtual quint64 write(const QByteArray &byte_array) const = 0;

        virtual QByteArray readAll() const = 0;
    };

    class TcpSocketAdapter : public ITcpSocketAdapter {
        QTcpSocket *tcp_socket_ptr_;

    public:
        explicit TcpSocketAdapter(QTcpSocket* tcp_socket_ptr, QObject *parent = nullptr);

        quint64 write(const QByteArray &byte_array) const override;

        QByteArray readAll() const override;
    };
}
