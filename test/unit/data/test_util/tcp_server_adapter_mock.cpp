#include "tcp_server_adapter_mock.h"

llink::ITcpSocketAdapter *llink::MockTcpServerAdapter::nextPendingConnection() const {
    return pending_connections.dequeue();
}
