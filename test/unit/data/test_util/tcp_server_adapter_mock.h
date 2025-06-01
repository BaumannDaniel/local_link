#pragma once
#include <QQueue>
#include <gmock/gmock.h>

#include "network/tcp_server_adapter.h"

namespace llink {
    class MockTcpServerAdapter : public ITcpServerAdapter {
        mutable QQueue<ITcpSocketAdapter *> pending_connections;

        ITcpSocketAdapter *nextPendingConnection() const override;

        MOCK_METHOD(bool, listen, (const QHostAddress &host_address, quint16 port), (override));
    };
}
