#include "udp_socket_adapter.h"

llink::UdpSocketAdapter::UdpSocketAdapter()
    : udp_socket_(new QUdpSocket(this)) {
    udp_socket_->bind(SOCKET_PORT);
    connect(udp_socket_, &QUdpSocket::readyRead, this, &IUdpSocketAdapter::readyRead);
}

bool llink::UdpSocketAdapter::hasPendingDatagrams() const {
    return udp_socket_->hasPendingDatagrams();
}

qint64 llink::UdpSocketAdapter::pendingDatagramSize() const {
    return udp_socket_->pendingDatagramSize();
}

qint64 llink::UdpSocketAdapter::readDatagram(char *data, qint64 maxSize, QHostAddress *address, quint16 *port) {
    return udp_socket_->readDatagram(data, maxSize, address, port);
}

qint64 llink::UdpSocketAdapter::writeDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port) {
    return udp_socket_->writeDatagram(datagram, host, port);
}
