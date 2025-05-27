#include "user_repository.h"

#include <utility>
#include <QDebug>

llink::UserRepository::UserRepository(QSharedPointer<INetworkApi> i_network_api_ptr)
    : i_network_api_ptr_(std::move(i_network_api_ptr)) {
    connect(i_network_api_ptr_.get(), &INetworkApi::userInfoResponse,
            this, &UserRepository::add_user);
    connect(i_network_api_ptr_.get(), &INetworkApi::userDisconnected,
            this, &UserRepository::remove_user);
}

void llink::UserRepository::add_user(const QSharedPointer<llink::NetworkResponse<llink::UserInfo> > &user_info) {
    User user(user_info->payload.name, user_info->sender_address);
    users_[user_info->sender_address] = user;
    qDebug() << "Adding user with name: " << user.name;
    emit users_updated();
}

void llink::UserRepository::remove_user(const QHostAddress &host_address) {
    if (users_.contains(host_address)) {
        users_.remove(host_address);
    }
    emit users_updated();
}

QList<llink::User> llink::UserRepository::get_users() const {
    return this->users_.values();
}
