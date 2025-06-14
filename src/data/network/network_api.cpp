#include <QDebug>
#include <QBuffer>
#include <QImage>

#include "network_api.h"

llink::NetworkApi::NetworkApi(
    IUdpSocketAdapter *i_udp_socket_adapter_ptr,
    ITcpServerAdapter *i_tcp_server_adapter_ptr,
    QObject *parent
)
    : INetworkApi(parent),
      i_udp_socket_adapter_ptr_(i_udp_socket_adapter_ptr),
      i_tcp_server_adapter_ptr_(i_tcp_server_adapter_ptr) {
    connect(i_udp_socket_adapter_ptr_, &IUdpSocketAdapter::readyRead,
            this, &NetworkApi::processDatagrams);
    connect(i_tcp_server_adapter_ptr_, &ITcpServerAdapter::newConnection,
            this, &NetworkApi::processNewConnection);
    i_udp_socket_adapter_ptr_->setParent(this);
    i_tcp_server_adapter_ptr_->setParent(this);
    i_udp_socket_adapter_ptr_->bind(UDP_SOCKET_PORT, QAbstractSocket::DefaultForPlatform);
    i_tcp_server_adapter_ptr_->listen(QHostAddress::Any, TCP_SOCKET_PORT);
}

void llink::NetworkApi::processDatagrams() {
    QByteArray datagram_array;
    QHostAddress host_address;
    quint8 message_type;
    while (i_udp_socket_adapter_ptr_->hasPendingDatagrams()) {
        datagram_array.resize(i_udp_socket_adapter_ptr_->pendingDatagramSize());
        i_udp_socket_adapter_ptr_->readDatagram(datagram_array.data(), datagram_array.size(), &host_address, nullptr);
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

void llink::NetworkApi::processNewConnection() {
    auto tcp_socket_ptr = i_tcp_server_adapter_ptr_->nextPendingConnection();
    auto connection = QSharedPointer<Connection>::create(tcp_socket_ptr);
    emit newConnection(connection);
}

void llink::NetworkApi::broadcastUserInfoQuery() const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_INFO_QUERY;
    i_udp_socket_adapter_ptr_->writeDatagram(message_byte_array, QHostAddress::Broadcast, UDP_SOCKET_PORT);
}

void llink::NetworkApi::broadcastUserDisconnected() const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_DISCONNECTED;
    i_udp_socket_adapter_ptr_->writeDatagram(message_byte_array, QHostAddress::Broadcast, UDP_SOCKET_PORT);
}

void llink::NetworkApi::sendUserInfo(QHostAddress host_address, UserInfo user_info) const {
    QByteArray message_byte_array;
    QDataStream stream(&message_byte_array, QIODevice::WriteOnly);
    stream << MessageType::USER_INFO_RESPONSE << user_info;
    i_udp_socket_adapter_ptr_->writeDatagram(message_byte_array, host_address, UDP_SOCKET_PORT);
}

QSharedPointer<llink::Connection> llink::INetworkApi::createConnection(const QHostAddress &host_address) {
    auto tcp_socket_ptr = new QTcpSocket();
    auto tcp_socket_adapter_ptr = new TcpSocketAdapter(tcp_socket_ptr);
    tcp_socket_adapter_ptr->connectToHost(host_address, TCP_SOCKET_PORT);
    return QSharedPointer<Connection>::create(tcp_socket_adapter_ptr);
}
