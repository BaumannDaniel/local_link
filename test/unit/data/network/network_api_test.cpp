#include "network/network_api.h"

#include <gtest/gtest.h>

#include "../test_util/network_api_mock.h"
#include "../test_util/tcp_server_adapter_mock.h"
#include "../test_util/udp_socket_adapter_mock.h"

namespace llink {
    class NetworkApiTest : public testing::Test {
    protected:
        const QString TEST_USER_NAME = "test";
        const QString TEST_HOST_ADDRESS = "192.168.1.1";
        MockUdpSocketAdapter *mock_udp_socket_adapter_ptr = new MockUdpSocketAdapter();
        MockTcpServerAdapter *mock_tcp_server_adapter_ptr = new MockTcpServerAdapter();
        NetworkApi network_api = NetworkApi(mock_udp_socket_adapter_ptr, mock_tcp_server_adapter_ptr);
        NetworkApiSignalTester network_api_signal_tester = NetworkApiSignalTester(&network_api);
    };

    TEST_F(NetworkApiTest, userInfoQuery$emitsSignal) {
        QByteArray message_byte_array;
        QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
        stream << MessageType::USER_INFO_QUERY;
        const QHostAddress test_host_address(TEST_HOST_ADDRESS);
        TestDatagram test_datagram(message_byte_array, test_host_address);
        mock_udp_socket_adapter_ptr->pending_datagrams.enqueue(test_datagram);
        emit mock_udp_socket_adapter_ptr->readyRead();
        ASSERT_EQ(network_api_signal_tester.received_user_info_queries.size(), 1);
        auto host_address = network_api_signal_tester.received_user_info_queries.first();
        ASSERT_EQ(host_address, test_host_address);
    }

    TEST_F(NetworkApiTest, userDisconnected$emitsSignal) {
        QByteArray message_byte_array;
        QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
        stream << MessageType::USER_DISCONNECTED;
        const QHostAddress test_host_address(TEST_HOST_ADDRESS);
        TestDatagram test_datagram(message_byte_array, test_host_address);
        mock_udp_socket_adapter_ptr->pending_datagrams.enqueue(test_datagram);
        emit mock_udp_socket_adapter_ptr->readyRead();
        ASSERT_EQ(network_api_signal_tester.received_user_disconnects.size(), 1);
        auto host_address = network_api_signal_tester.received_user_disconnects.first();
        ASSERT_EQ(host_address, test_host_address);
    }

    TEST_F(NetworkApiTest, userInfoResponse$emitsSignal) {
        UserInfo test_user_info(TEST_USER_NAME);
        QByteArray message_byte_array;
        QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
        stream << MessageType::USER_INFO_RESPONSE << test_user_info;
        const QHostAddress test_host_address(TEST_HOST_ADDRESS);
        TestDatagram test_datagram(message_byte_array, test_host_address);
        mock_udp_socket_adapter_ptr->pending_datagrams.enqueue(test_datagram);
        emit mock_udp_socket_adapter_ptr->readyRead();
        ASSERT_EQ(network_api_signal_tester.received_user_info_responses.size(), 1);
        auto user_info_response = network_api_signal_tester.received_user_info_responses.first();
        ASSERT_EQ(user_info_response->sender_address, test_host_address);
        ASSERT_EQ(user_info_response->payload.name, TEST_USER_NAME);
    }

    TEST_F(NetworkApiTest, broadcastUserInfoQuery$writesDatagram) {
        network_api.broadcastUserInfoQuery();
        ASSERT_EQ(mock_udp_socket_adapter_ptr->written_datagrams.size(), 1);
        auto datagram = mock_udp_socket_adapter_ptr->written_datagrams.first();
        ASSERT_EQ(datagram.host, QHostAddress::Broadcast);
        ASSERT_EQ(datagram.port, INetworkApi::UDP_SOCKET_PORT);
        quint8 message_type;
        QDataStream stream(&datagram.data, QIODeviceBase::ReadOnly);
        stream >> message_type;
        ASSERT_EQ(message_type, MessageType::USER_INFO_QUERY);
    }

    TEST_F(NetworkApiTest, broadcastUserDisconnected$writesDatagram) {
        network_api.broadcastUserDisconnected();
        ASSERT_EQ(mock_udp_socket_adapter_ptr->written_datagrams.size(), 1);
        auto datagram = mock_udp_socket_adapter_ptr->written_datagrams.first();
        ASSERT_EQ(datagram.host, QHostAddress::Broadcast);
        ASSERT_EQ(datagram.port, INetworkApi::UDP_SOCKET_PORT);
        quint8 message_type;
        QDataStream stream(&datagram.data, QIODeviceBase::ReadOnly);
        stream >> message_type;
        ASSERT_EQ(message_type, MessageType::USER_DISCONNECTED);
    }

    TEST_F(NetworkApiTest, sendUserInfo$writesDatagram) {
        const UserInfo test_user_info(TEST_USER_NAME);
        const QHostAddress test_host_address(TEST_HOST_ADDRESS);
        network_api.sendUserInfo(test_host_address, test_user_info);
        ASSERT_EQ(mock_udp_socket_adapter_ptr->written_datagrams.size(), 1);
        auto datagram = mock_udp_socket_adapter_ptr->written_datagrams.first();
        ASSERT_EQ(datagram.host, test_host_address);
        ASSERT_EQ(datagram.port, INetworkApi::UDP_SOCKET_PORT);
        quint8 message_type;
        UserInfo user_info;
        QDataStream stream(&datagram.data, QIODeviceBase::ReadOnly);
        stream >> message_type;
        ASSERT_EQ(message_type, MessageType::USER_INFO_RESPONSE);
        stream >> user_info;
        ASSERT_EQ(user_info.name, test_user_info.name);
    }
}
