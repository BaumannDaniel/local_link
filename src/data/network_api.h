#pragma once
#include <QUdpSocket>

#include "network_message.h"

namespace llink {
    class INetworkApi : public QObject {
        Q_OBJECT
    signals:
        void user_info_query(QHostAddress host_address);

        void user_disconnected(QHostAddress host_address);

        void user_info_response(QSharedPointer<llink::NetworkResponse<llink::UserInfo> >);

    public:
        constexpr quint16 SOCKET_PORT = 10050;
        explicit INetworkApi(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual void broadcast_user_info_query() const = 0;

        virtual void broadcast_user_disconnected() const = 0;

        virtual void send_user_info(QHostAddress host_address, UserInfo user_info) const = 0;
    };

    class NetworkApi : public INetworkApi {
        Q_OBJECT
        QUdpSocket *udp_socket_;

    private slots:
        void process_datagrams();

    public:
        explicit NetworkApi(QUdpSocket *udp_socket);

        void broadcast_user_info_query() const override;

        void broadcast_user_disconnected() const override;

        void send_user_info(QHostAddress host_address, UserInfo user_info) const override;
    };
}
