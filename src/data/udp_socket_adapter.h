#pragma once
#include <QHostAddress>
#include <QObject>
#include <QUdpSocket>

namespace llink {
    class IUdpSocketAdapter : public QObject {
        Q_OBJECT

    public:
        static constexpr quint16 SOCKET_PORT = 10050;

        explicit IUdpSocketAdapter(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual bool hasPendingDatagrams() const = 0;

        virtual qint64 pendingDatagramSize() const = 0;

        virtual qint64 readDatagram(char *data, qint64 maxSize, QHostAddress *address = nullptr,
                                    quint16 *port = nullptr) = 0;

        virtual qint64 writeDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port) = 0;

    signals:
        void readyRead();
    };

    class UdpSocketAdapter : public IUdpSocketAdapter {
        QUdpSocket *udp_socket_;

    public:
        UdpSocketAdapter();

        bool hasPendingDatagrams() const override;

        qint64 pendingDatagramSize() const override;

        qint64 readDatagram(char *data, qint64 maxSize, QHostAddress *address, quint16 *port) override;

        qint64 writeDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port) override;
    };
}
