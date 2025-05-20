#include <QDebug>

#include "user_status_manager.h"
#include "network_message.h"

llink::UserStatusManager::UserStatusManager(QSharedPointer<INetworkApi> i_network_api_ptr)
    : i_network_api_ptr_(std::move(i_network_api_ptr)) {
}


void llink::UserStatusManager::send_user_info_query() const {
    qDebug() << "sending user info query";
    i_network_api_ptr_->broadcastUserInfoQuery();
}

void llink::UserStatusManager::send_user_info_broadcast() const {
    UserInfo user_info("Test User 1");
    i_network_api_ptr_->sendUserInfo(QHostAddress::Broadcast, user_info);
}

void llink::UserStatusManager::send_user_disconnect_broadcast() const {
    i_network_api_ptr_->broadcastUserDisconnected();
}

