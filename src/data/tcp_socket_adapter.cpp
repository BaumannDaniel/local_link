#include "tcp_socket_adapter.h"

llink::TcpSocketAdapter::TcpSocketAdapter()
    : tcp_socket_ptr_(new QTcpSocket(this)) {
    tcp_socket_ptr_->bind(SOCKET_PORT);
    connect(tcp_socket_ptr_, &QTcpSocket::readyRead, this, &ITcpSocketAdapter::readyRead);
}

quint64 llink::TcpSocketAdapter::write(const QByteArray &byte_array) const {
    return tcp_socket_ptr_->write(byte_array);
}
