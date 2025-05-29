#include <QImage>

#include "connection.h"

#include <QBuffer>

llink::Connection::Connection(QSharedPointer<ITcpSocketAdapter> i_tcp_socket_adapter_ptr, QObject *parent)
    : QObject(parent),
      i_tcp_socket_adapter_ptr_(std::move(i_tcp_socket_adapter_ptr)) {
    connect(i_tcp_socket_adapter_ptr_.get(), &ITcpSocketAdapter::readyRead,
            this, &Connection::processDataStream);
}

void llink::Connection::processDataStream() {
    data_stream_buffer.append(i_tcp_socket_adapter_ptr_->readAll());

    while (true) {
        if (remaining_bytes_in_message == 0) {
            if (data_stream_buffer.size() < 4)
                return;
            QDataStream stream(data_stream_buffer);
            stream.setByteOrder(QDataStream::BigEndian);
            stream >> remaining_bytes_in_message;
            data_stream_buffer.remove(0, 4);
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

void llink::Connection::sendVideoFrame(const QSharedPointer<QImage> &video_frame_ptr) const {
    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    video_frame_ptr->save(&buffer, "JPEG");

    quint32 size = imageData.size();
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::BigEndian);
    stream << size;
    packet.append(imageData); // image payload

    i_tcp_socket_adapter_ptr_->write(packet);
}

