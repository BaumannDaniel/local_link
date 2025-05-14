#include <QDebug>

#include "user_status_manager.h"
#include "network_message.h"

llink::UserStatusManager::UserStatusManager(QSharedPointer<INetworkApi> i_network_api_ptr)
    : i_network_api_ptr_(std::move(i_network_api_ptr)) {
}


void llink::UserStatusManager::send_user_info_query() const {
    qDebug() << "sending user info query";
    i_network_api_ptr_->broadcast_user_info_query();
}

void llink::UserStatusManager::send_user_info_broadcast() const {
    UserInfo user_info("Test User 1");
    i_network_api_ptr_->send_user_info(QHostAddress::Broadcast, user_info);
}
