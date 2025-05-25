#include "tcp_socket_adapter.h"

llink::TcpSocketAdapter::TcpSocketAdapter(QTcpSocket* tcp_socket_ptr, QObject *parent)
    : ITcpSocketAdapter(parent),
    tcp_socket_ptr_(tcp_socket_ptr) {
    tcp_socket_ptr->setParent(this);
    connect(tcp_socket_ptr_, &QTcpSocket::readyRead, this, &ITcpSocketAdapter::readyRead);
}

quint64 llink::TcpSocketAdapter::write(const QByteArray &byte_array) const {
    return tcp_socket_ptr_->write(byte_array);
}

QByteArray llink::TcpSocketAdapter::readAll() const {
    return tcp_socket_ptr_->readAll();
}

void llink::TcpSocketAdapter::connectToHost(const QHostAddress host_address, const qint16 port) const {
    tcp_socket_ptr_->connectToHost(host_address, port);
}
