#pragma once
#include <QHostAddress>
#include <QObject>

#include "network_api.h"

namespace llink {
    class NetworkApiSignalTester : public QObject {
        INetworkApi *i_network_api_ptr_;

    public slots:
        void userInfoQueryReceived(const QHostAddress &host_address);

        void userDisconnectedReceived(const QHostAddress &host_address);

        void userInfoResponseReceived(const QSharedPointer<llink::NetworkResponse<llink::UserInfo> > &user_info_response);

    public:
        explicit NetworkApiSignalTester(INetworkApi *i_network_api_ptr);

        QList<QHostAddress> received_user_info_queries;
        QList<QHostAddress> received_user_disconnects;
        QList<QSharedPointer<llink::NetworkResponse<llink::UserInfo> > > received_user_info_responses;
    };
}
