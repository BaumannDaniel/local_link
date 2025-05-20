#pragma once
#include <QUdpSocket>
#include <QSharedPointer>

#include "network_message.h"
#include "udp_socket_adapter.h"

namespace llink {
    class INetworkApi : public QObject {
        Q_OBJECT
    signals:
        void userInfoQuery(QHostAddress host_address);

        void userDisconnected(QHostAddress host_address);

        void userInfoResponse(QSharedPointer<llink::NetworkResponse<llink::UserInfo> > user_info_response);

    public:
        explicit INetworkApi(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual void broadcastUserInfoQuery() const = 0;

        virtual void broadcastUserDisconnected() const = 0;

        virtual void sendUserInfo(QHostAddress host_address, UserInfo user_info) const = 0;
    };

    class NetworkApi : public INetworkApi {
        Q_OBJECT
        QSharedPointer<IUdpSocketAdapter> i_udp_socket_adapter_ptr_;

    private slots:
        void processDatagrams();

    public:
        explicit NetworkApi(QSharedPointer<IUdpSocketAdapter> i_udp_socket_adapter_ptr);

        void broadcastUserInfoQuery() const override;

        void broadcastUserDisconnected() const override;

        void sendUserInfo(QHostAddress host_address, UserInfo user_info) const override;
    };
}
