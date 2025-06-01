#include "video_frame_item.h"

llink::VideoFrameItem::VideoFrameItem(
    QQuickItem *parent
) : QQuickPaintedItem(parent) {
    setRenderTarget(QQuickPaintedItem::FramebufferObject);
    setAntialiasing(true);
}

void llink::VideoFrameItem::paint(QPainter *painter) {
    if (current_frame_ptr_ && !current_frame_ptr_->isNull()) {
        painter->drawImage(boundingRect(), *current_frame_ptr_);
    } else {
        painter->fillRect(boundingRect(), Qt::black);
    }
}

void llink::VideoFrameItem::setCurrentFrame(const QSharedPointer<QImage> &current_frame_ptr) {
    current_frame_ptr_ = current_frame_ptr;
    update();
}

