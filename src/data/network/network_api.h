#pragma once
#include <QUdpSocket>
#include <QSharedPointer>

#include "connection.h"
#include "network_message.h"
#include "tcp_server_adapter.h"
#include "tcp_socket_adapter.h"
#include "udp_socket_adapter.h"

namespace llink {
    class INetworkApi : public QObject {
        Q_OBJECT
    signals:
        void userInfoQuery(QHostAddress host_address);

        void userDisconnected(QHostAddress host_address);

        void userInfoResponse(QSharedPointer<llink::NetworkResponse<llink::UserInfo> > user_info_response);

        void newConnection(QSharedPointer<llink::Connection> connection_ptr_);

    public:
        static constexpr quint16 TCP_SOCKET_PORT = 10051;

        explicit INetworkApi(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual void broadcastUserInfoQuery() const = 0;

        virtual void broadcastUserDisconnected() const = 0;

        virtual void sendUserInfo(QHostAddress host_address, UserInfo user_info) const = 0;

        static QSharedPointer<Connection> createConnection(const QHostAddress& host_address);
    };

    class NetworkApi : public INetworkApi {
        Q_OBJECT
        QSharedPointer<IUdpSocketAdapter> i_udp_socket_adapter_ptr_ = nullptr;
        ITcpServerAdapter *i_tcp_server_adapter_ptr_ = nullptr;

    private slots:
        void processDatagrams();

        void processNewConnection();

    public:
        NetworkApi(
            QSharedPointer<IUdpSocketAdapter> i_udp_socket_adapter_ptr,
            ITcpServerAdapter *i_tcp_server_adapter_ptr,
            QObject *parent = nullptr
        );

        void broadcastUserInfoQuery() const override;

        void broadcastUserDisconnected() const override;

        void sendUserInfo(QHostAddress host_address, UserInfo user_info) const override;
    };
}
