#include "tcp_server_adapter.h"
#include "tcp_socket_adapter.h"

llink::TcpServerAdapter::TcpServerAdapter()
    : tcp_server_ptr_(new QTcpServer(this)) {
    connect(tcp_server_ptr_, &QTcpServer::newConnection, this, &ITcpServerAdapter::newConnection);
    tcp_server_ptr_->listen(QHostAddress::Any, SOCKET_PORT);
}

QSharedPointer<llink::ITcpSocketAdapter> llink::TcpServerAdapter::nextPendingConnection() const {
    auto tcp_socket_ptr = tcp_server_ptr_->nextPendingConnection();
    auto tcp_socket_adapter_ptr = QSharedPointer<TcpSocketAdapter>::create(tcp_socket_ptr);
    return tcp_socket_adapter_ptr;
}
