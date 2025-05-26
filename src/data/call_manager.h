#pragma once
#include <QHostAddress>
#include <QObject>

#include "network_api.h"

namespace llink {
    class CallManager : public QObject {
        QSharedPointer<INetworkApi> network_api_ptr_;
        QSharedPointer<Connection> current_connection_ptr_ = nullptr;

    private slots:
        void handleNewConnection(const QSharedPointer<Connection> &connection_ptr);

    signals:
        void videoFrameReceived(QSharedPointer<QImage> frame);

    public:
        explicit CallManager(const QSharedPointer<INetworkApi> &network_api_ptr, QObject *parent = nullptr);

        void startCall(QHostAddress host_address);
    };
}
