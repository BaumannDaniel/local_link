#include "call_manager.h"

llink::CallManager::CallManager(const QSharedPointer<INetworkApi> &network_api_ptr, QObject *parent)
    : QObject(parent),
      network_api_ptr_(network_api_ptr) {
    connect(network_api_ptr_.get(), &INetworkApi::newConnection,
            this, &CallManager::handleNewConnection);
}

void llink::CallManager::handleNewConnection(const QSharedPointer<Connection> &connection_ptr) {
    if (current_connection_ptr_ != nullptr) return;
    current_connection_ptr_ = connection_ptr;
    connect(current_connection_ptr_.get(), &Connection::videoFrameReceived,
        this, &CallManager::videoFrameReceived);
}

void llink::CallManager::startCall(QHostAddress host_address) {
    auto connection_ptr = INetworkApi::createConnection(host_address);
    handleNewConnection(connection_ptr);
}
