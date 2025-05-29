#include "tcp_server_adapter.h"
#include "tcp_socket_adapter.h"

llink::TcpServerAdapter::TcpServerAdapter(QObject *parent)
    : ITcpServerAdapter(parent),
      tcp_server_ptr_(new QTcpServer(this)) {
    connect(tcp_server_ptr_, &QTcpServer::newConnection, this, &ITcpServerAdapter::newConnection);
}

QSharedPointer<llink::ITcpSocketAdapter> llink::TcpServerAdapter::nextPendingConnection() const {
    auto tcp_socket_ptr = tcp_server_ptr_->nextPendingConnection();
    auto tcp_socket_adapter_ptr = QSharedPointer<TcpSocketAdapter>::create(tcp_socket_ptr);
    return tcp_socket_adapter_ptr;
}

bool llink::TcpServerAdapter::listen(const QHostAddress &host_address, const quint16 port) {
    return tcp_server_ptr_->listen(host_address, port);
}
