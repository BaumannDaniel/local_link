#include "network_api.h"

llink::NetworkApi::NetworkApi(QUdpSocket *udp_socket) : udp_socket_(udp_socket) {
    udp_socket_->setParent(this);
    udp_socket_->bind(10050);
    connect(udp_socket_, &QUdpSocket::readyRead,
            this, &NetworkApi::process_datagrams);
}

void llink::NetworkApi::process_datagrams() {
    QByteArray datagram_array;
    QHostAddress host_address;
    quint16 message_type;
    while (udp_socket_->hasPendingDatagrams()) {
        datagram_array.resize(static_cast<int>(udp_socket_->pendingDatagramSize()));
        udp_socket_->readDatagram(datagram_array.data(), datagram_array.size(), &host_address);
        QDataStream stream(&datagram_array, QIODeviceBase::ReadOnly);
        stream >> message_type;
        if (message_type == MessageType::USER_INFO_QUERY) {
            emit user_info_query(host_address);
            continue;
        }
        if (message_type ==  MessageType::USER_DISCONNECTED) {
            emit user_disconnected(host_address);
            continue;
        }
        if (message_type == MessageType::USER_INFO_RESPONSE) {
            UserInfo user_info;
            stream >> user_info;
            auto network_response_ptr = QSharedPointer<NetworkResponse<UserInfo>>::create(host_address, user_info);
            emit user_info_response(network_response_ptr);
        }
    }
}


void llink::NetworkApi::broadcast_user_info_query() const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_INFO_QUERY;
    udp_socket_->writeDatagram(message_byte_array, QHostAddress::Broadcast, 10050);
}

void llink::NetworkApi::broadcast_user_disconnected() const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_DISCONNECTED;
    udp_socket_->writeDatagram(message_byte_array, QHostAddress::Broadcast, 10050);
}

void llink::NetworkApi::send_user_info(QHostAddress host_address, UserInfo user_info) const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_INFO_RESPONSE << user_info;
    udp_socket_->writeDatagram(message_byte_array, host_address, 10050);
}
