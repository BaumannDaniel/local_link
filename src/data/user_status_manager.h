#pragma once

#include "network_api.h"

namespace llink {
    class IUserStatusManager {
    public:
        virtual ~IUserStatusManager() = default;

        virtual void send_user_info_query() const = 0;

        virtual void send_user_info_broadcast() const = 0;
    };

    class UserStatusManager : public IUserStatusManager {
        QSharedPointer<INetworkApi> i_network_api_ptr_;

    public:
        UserStatusManager(QSharedPointer<INetworkApi> i_network_api_ptr);

        void send_user_info_query() const override;

        void send_user_info_broadcast() const override;
    };
}
