#include "call_manager.h"

llink::CallManager::CallManager(
    const QSharedPointer<INetworkApi> &network_api_ptr,
    const QSharedPointer<VideoRecorder> &video_recorder_ptr,
    QObject *parent
)
    : QObject(parent),
      network_api_ptr_(network_api_ptr),
      video_recorder_ptr_(video_recorder_ptr) {
    connect(network_api_ptr_.get(), &INetworkApi::newConnection,
            this, &CallManager::handleNewConnection);
}

void llink::CallManager::handleNewConnection(const QSharedPointer<Connection> &connection_ptr) {
    if (current_connection_ptr_ != nullptr) return;
    current_connection_ptr_ = connection_ptr;
    connect(current_connection_ptr_.get(), &Connection::videoFrameReceived,
            this, &CallManager::videoFrameReceived);
    connect(video_recorder_ptr_.get(), &VideoRecorder::newFrame,
        this, &CallManager::sendVideoFrame);
}

void llink::CallManager::sendVideoFrame(const QSharedPointer<QImage> &video_frame_ptr) {
    if (current_connection_ptr_ == nullptr) return;
    current_connection_ptr_->sendVideoFrame(video_frame_ptr);
}

void llink::CallManager::startCall(QHostAddress host_address) {
    auto connection_ptr = INetworkApi::createConnection(host_address);
    handleNewConnection(connection_ptr);
}
