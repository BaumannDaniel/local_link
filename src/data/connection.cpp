#include <QImage>

#include "connection.h"

#include <QBuffer>

llink::Connection::Connection(ITcpSocketAdapter *i_tcp_socket_adapter_ptr, QObject *parent)
    : QObject(parent),
      i_tcp_socket_adapter_ptr_(i_tcp_socket_adapter_ptr) {
    i_tcp_socket_adapter_ptr_->setParent(this);
    connect(i_tcp_socket_adapter_ptr_, &ITcpSocketAdapter::connected,
            this, &Connection::connected);
    connect(i_tcp_socket_adapter_ptr_, &ITcpSocketAdapter::disconnected,
            this, &Connection::disconnected);
    connect(i_tcp_socket_adapter_ptr_, &ITcpSocketAdapter::readyRead,
            this, &Connection::processDataStream);
}

void llink::Connection::processDataStream() {
    data_stream_buffer.append(i_tcp_socket_adapter_ptr_->readAll());

    while (true) {
        if (remaining_bytes_in_message == 0) {
            if (data_stream_buffer.size() < sizeof(quint32))
                return;
            QDataStream stream(data_stream_buffer);
            stream.setByteOrder(QDataStream::BigEndian);
            stream >> remaining_bytes_in_message;
            data_stream_buffer.remove(0, sizeof(quint32));
        }

        if (data_stream_buffer.size() < remaining_bytes_in_message)
            return;

        QByteArray imageData = data_stream_buffer.left(remaining_bytes_in_message);
        data_stream_buffer.remove(0, remaining_bytes_in_message);
        remaining_bytes_in_message = 0;

        QImage image;
        image.loadFromData(imageData, "JPEG");
        auto image_ptr = QSharedPointer<QImage>::create(std::move(image));

        emit videoFrameReceived(image_ptr);
    }
}

void llink::Connection::disconnect() const {
    i_tcp_socket_adapter_ptr_->disconnect();
}

void llink::Connection::sendVideoFrame(const QSharedPointer<QImage> &video_frame_ptr) const {
    QByteArray image_byte_array;
    QBuffer buffer(&image_byte_array);
    buffer.open(QIODevice::WriteOnly);
    video_frame_ptr->save(&buffer, IMAGE_FORMAT_JPEG);

    quint32 size = image_byte_array.size();
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream << size;
    packet.append(image_byte_array);

    i_tcp_socket_adapter_ptr_->write(packet);
}
