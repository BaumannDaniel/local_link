#include "tcp_socket_adapter_mock.h"

quint64 llink::MockTcpSocketAdapter::write(const QByteArray &byte_array) const {
    written_data.append(byte_array);
    return byte_array.size();
}

QByteArray llink::MockTcpSocketAdapter::readAll() const {
    return pending_data;
}

