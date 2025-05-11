#pragma once
#include <QUdpSocket>

#include "user.h"

namespace llink {
    class IUserScanner : public QObject {
    signals:
        void user_connected(llink::User connected_user);

        void user_disconnected(QString ip_address);

    public:
        explicit IUserScanner(QObject *parent = nullptr) : QObject(parent) {
        }

        virtual void start_listener() = 0;

        virtual void send_broadcast() = 0;
    };

    class UserScanner : public IUserScanner {
        QUdpSocket *udp_socket_ = nullptr;

    private slots:
        void process_datagrams();

    public:
        UserScanner();

        void start_listener() override;

        void send_broadcast() override;
    };
}
