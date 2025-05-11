#include <QDebug>

#include "user_scanner.h"

llink::UserScanner::UserScanner() {
    udp_socket_ = new QUdpSocket(this);
    udp_socket_->bind(10050);
}

void llink::UserScanner::start_listener() {
    connect(udp_socket_, &QUdpSocket::readyRead,
            this, &UserScanner::process_datagrams);
}


void llink::UserScanner::send_broadcast() {
    qDebug() << "sending broadcast";
    QByteArray message = "test";
    udp_socket_->writeDatagram(message, QHostAddress::Broadcast, 10050);
}

void llink::UserScanner::process_datagrams() {
    QByteArray datagram;
    while (udp_socket_->hasPendingDatagrams()) {
        datagram.resize(int(udp_socket_->pendingDatagramSize()));
        udp_socket_->readDatagram(datagram.data(), datagram.size());
        qDebug() << datagram.constData();
    }
}
