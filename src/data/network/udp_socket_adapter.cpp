#include "udp_socket_adapter.h"

llink::UdpSocketAdapter::UdpSocketAdapter()
    : udp_socket_ptr_(new QUdpSocket(this)) {
    connect(udp_socket_ptr_, &QUdpSocket::readyRead, this, &IUdpSocketAdapter::readyRead);
}

bool llink::UdpSocketAdapter::bind(const quint16 port, const QAbstractSocket::BindMode bind_mode) {
    return udp_socket_ptr_->bind(port, bind_mode);
}

bool llink::UdpSocketAdapter::hasPendingDatagrams() const {
    return udp_socket_ptr_->hasPendingDatagrams();
}

qint64 llink::UdpSocketAdapter::pendingDatagramSize() const {
    return udp_socket_ptr_->pendingDatagramSize();
}

qint64 llink::UdpSocketAdapter::readDatagram(char *data, qint64 maxSize, QHostAddress *address, quint16 *port) {
    return udp_socket_ptr_->readDatagram(data, maxSize, address, port);
}

qint64 llink::UdpSocketAdapter::writeDatagram(const QByteArray &datagram, const QHostAddress &host, quint16 port) {
    return udp_socket_ptr_->writeDatagram(datagram, host, port);
}
