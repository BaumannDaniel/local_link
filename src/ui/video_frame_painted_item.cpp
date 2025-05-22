#include "video_frame_painted_item.h"

llink::VideoFramePaintedItem::VideoFramePaintedItem(
    QQuickItem *parent
) : QQuickPaintedItem(parent) {
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setAntialiasing(true);
}

void llink::VideoFramePaintedItem::paint(QPainter *painter) {
    if (current_frame_ptr_ && !current_frame_ptr_->isNull()) {
        painter->drawImage(boundingRect(), *current_frame_ptr_);
    } else {
        painter->fillRect(boundingRect(), Qt::black);
    }
}

void llink::VideoFramePaintedItem::setCurrentFrame(const QSharedPointer<QImage> &current_frame_ptr) {
    current_frame_ptr_ = current_frame_ptr;
    update();
}

