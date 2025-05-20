#include <QDebug>

#include "network_api.h"

llink::NetworkApi::NetworkApi(QSharedPointer<IUdpSocketAdapter> i_udp_socket_adapter_ptr)
    : i_udp_socket_adapter_ptr_(std::move(i_udp_socket_adapter_ptr)) {
    connect(i_udp_socket_adapter_ptr_.get(), &IUdpSocketAdapter::readyRead,
            this, &NetworkApi::processDatagrams);
}

void llink::NetworkApi::processDatagrams() {
    QByteArray datagram_array;
    QHostAddress host_address;
    quint16 message_type;
    while (i_udp_socket_adapter_ptr_->hasPendingDatagrams()) {
        datagram_array.resize(i_udp_socket_adapter_ptr_->pendingDatagramSize());
        i_udp_socket_adapter_ptr_->readDatagram(datagram_array.data(), datagram_array.size(), &host_address);
        QDataStream stream(&datagram_array, QIODeviceBase::ReadOnly);
        stream >> message_type;
        qDebug() << "Received Message of type: " << message_type;
        if (message_type == MessageType::USER_INFO_QUERY) {
            emit userInfoQuery(host_address);
            continue;
        }
        if (message_type == MessageType::USER_DISCONNECTED) {
            emit userDisconnected(host_address);
            continue;
        }
        if (message_type == MessageType::USER_INFO_RESPONSE) {
            UserInfo user_info;
            stream >> user_info;
            auto network_response_ptr = QSharedPointer<NetworkResponse<UserInfo> >::create(host_address, user_info);
            emit userInfoResponse(network_response_ptr);
        }
    }
}


void llink::NetworkApi::broadcastUserInfoQuery() const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_INFO_QUERY;
    i_udp_socket_adapter_ptr_->writeDatagram(message_byte_array, QHostAddress::Broadcast,
                                             IUdpSocketAdapter::SOCKET_PORT);
}

void llink::NetworkApi::broadcastUserDisconnected() const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_DISCONNECTED;
    i_udp_socket_adapter_ptr_->writeDatagram(message_byte_array, QHostAddress::Broadcast,
                                             IUdpSocketAdapter::SOCKET_PORT);
}

void llink::NetworkApi::sendUserInfo(QHostAddress host_address, UserInfo user_info) const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_INFO_RESPONSE << user_info;
    i_udp_socket_adapter_ptr_->writeDatagram(message_byte_array, host_address, IUdpSocketAdapter::SOCKET_PORT);
}
