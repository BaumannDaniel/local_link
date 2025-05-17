#pragma once
#include <QUdpSocket>
#include <QQueue>

namespace llink {
    struct TestDatagram {
        QByteArray data;
        QHostAddress host;
        quint16 port = 10050;
    };

    struct BindCall {
        quint16 bind_port{};
        QUdpSocket::BindMode bind_mode;
    };

    class MockQUdpSocket : public QUdpSocket {
    public:
        QList<BindCall> bind_calls;
        QQueue<TestDatagram> pending_datagrams;
        QList<TestDatagram> written_datagrams;

        bool bind(quint16 port = 0, BindMode mode = DefaultForPlatform);

        bool hasPendingDatagrams() const;

        qint64 pendingDatagramSize() const;

        qint64 readDatagram(char *data, qint64 maxlen, QHostAddress *host = nullptr, quint16 *port = nullptr);

        qint64 writeDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port);

        void reset_mock();
    };
}
