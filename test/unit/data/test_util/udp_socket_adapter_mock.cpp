#include "udp_socket_adapter_mock.h"

bool llink::MockUdpSocketAdapter::hasPendingDatagrams() const {
    return !pending_datagrams.empty();
}

qint64 llink::MockUdpSocketAdapter::pendingDatagramSize() const {
    if (pending_datagrams.empty()) return -1;
    return pending_datagrams.first().data.size();
}

qint64 llink::MockUdpSocketAdapter::readDatagram(char *data, qint64 maxlen, QHostAddress *host, quint16 *port) {
    if (pending_datagrams.isEmpty()) return -1;

    const TestDatagram test_datagram = pending_datagrams.dequeue();

    const qint64 number_of_bytes = qMin(maxlen, test_datagram.data.size());
    memcpy(data, test_datagram.data.constData(), number_of_bytes);

    if (host) *host = test_datagram.host;
    if (port) *port = test_datagram.port;

    return number_of_bytes;
}

qint64 llink::MockUdpSocketAdapter::writeDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port) {
    const TestDatagram test_datagram(datagram, host, port);
    written_datagrams.append(test_datagram);
    return datagram.size();
}

void llink::MockUdpSocketAdapter::reset_mock() {
    pending_datagrams.clear();
    written_datagrams.clear();
}
