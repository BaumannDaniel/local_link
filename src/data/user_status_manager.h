#pragma once

#include "network/network_api.h"

namespace llink {
    class IUserStatusManager : public QObject {
        Q_OBJECT

    public:
        virtual void send_user_info_query() const = 0;

        virtual void send_user_info_broadcast() const = 0;

        virtual void send_user_disconnect_broadcast() const = 0;
    };

    class UserStatusManager : public IUserStatusManager {
        Q_OBJECT
        QSharedPointer<INetworkApi> i_network_api_ptr_;

    private slots:
        void respond_to_user_info_query(const QHostAddress &sender_address) const;

    public:
        explicit UserStatusManager(QSharedPointer<INetworkApi> i_network_api_ptr);

        void send_user_info_query() const override;

        void send_user_info_broadcast() const override;

        void send_user_disconnect_broadcast() const override;
    };
}
