#pragma once

#include <QHash>
#include <QSharedPointer>

#include "network_api.h"
#include "user.h"

namespace llink {
    class IUserRepository : public QObject {
        Q_OBJECT
    signals:
        void users_updated();

    public:
        explicit IUserRepository(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual QList<User> get_users() const = 0;
    };

    class UserRepository : public IUserRepository {
        Q_OBJECT
        QHash<QHostAddress, User> users_;
        QSharedPointer<INetworkApi> i_network_api_ptr_;

    private slots:
        void add_user(const QSharedPointer<llink::NetworkResponse<llink::UserInfo> > &user_info);

        void remove_user(const QHostAddress &host_address);

    public:
        explicit UserRepository(QSharedPointer<INetworkApi> i_network_api_ptr);

        QList<User> get_users() const override;
    };
}
