#include "network_api_mock.h"

llink::NetworkApiSignalTester::NetworkApiSignalTester(INetworkApi *i_network_api_ptr)
    : i_network_api_ptr_(i_network_api_ptr) {
    connect(i_network_api_ptr_, &INetworkApi::userInfoQuery,
            this, &NetworkApiSignalTester::userInfoQueryReceived);
    connect(i_network_api_ptr_, &INetworkApi::userDisconnected,
            this, &NetworkApiSignalTester::userDisconnectedReceived);
    connect(i_network_api_ptr_, &INetworkApi::userInfoResponse,
            this, &NetworkApiSignalTester::userInfoResponseReceived);
}

void llink::NetworkApiSignalTester::userInfoQueryReceived(const QHostAddress &host_address) {
    received_user_info_queries.append(host_address);
}

void llink::NetworkApiSignalTester::userDisconnectedReceived(const QHostAddress &host_address) {
    received_user_disconnects.append(host_address);
}

void llink::NetworkApiSignalTester::userInfoResponseReceived(const QSharedPointer<llink::NetworkResponse<llink::UserInfo> > &user_info_response) {
    received_user_info_responses.append(user_info_response);
}

