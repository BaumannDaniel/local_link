#pragma once
#include <QUdpSocket>
#include <QQueue>

#include "udp_socket_adapter.h"

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

    class MockUdpSocketAdapter : public IUdpSocketAdapter {
    public:
        QQueue<TestDatagram> pending_datagrams;
        QList<TestDatagram> written_datagrams;

        bool hasPendingDatagrams() const override;

        qint64 pendingDatagramSize() const override;

        qint64 readDatagram(char *data, qint64 maxlen, QHostAddress *host, quint16 *port) override;

        qint64 writeDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port) override;

        void reset_mock();
    };
}
