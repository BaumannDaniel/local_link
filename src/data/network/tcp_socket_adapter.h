#pragma once
#include <qobject.h>
#include <QTcpSocket>

namespace llink {
    class ITcpSocketAdapter : public QObject {
        Q_OBJECT

    signals:
        void connected();

        void disconnected();

        void readyRead();

    public:
        explicit ITcpSocketAdapter(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual quint64 write(const QByteArray &byte_array) const = 0;

        virtual QByteArray readAll() const = 0;

        virtual void connectToHost(QHostAddress host_address, qint16 port) const = 0;
    };

    class TcpSocketAdapter : public ITcpSocketAdapter {
        QTcpSocket *tcp_socket_ptr_;

    public:
        explicit TcpSocketAdapter(QTcpSocket *tcp_socket_ptr, QObject *parent = nullptr);

        quint64 write(const QByteArray &byte_array) const override;

        QByteArray readAll() const override;

        void connectToHost(QHostAddress host_address, qint16 port) const override;
    };
}
