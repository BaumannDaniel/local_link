#pragma once

#include <gmock/gmock.h>

#include "network/tcp_socket_adapter.h"

namespace llink {
    class MockTcpSocketAdapter : public ITcpSocketAdapter {
    public:
        QByteArray pending_data;
        mutable QList<QByteArray> written_data;

        quint64 write(const QByteArray &byte_array) const override;

        QByteArray readAll() const override;

        MOCK_METHOD(void, connectToHost, (QHostAddress host_address, qint16 port), (const, override));
    };
}
