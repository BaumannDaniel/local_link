#pragma once

#include <QQuickPaintedItem>
#include <QImage>
#include <QPainter>

#include "video_recorder.h"

namespace llink {
    class VideoFrameItem : public QQuickPaintedItem {
        Q_OBJECT
        QSharedPointer<QImage> current_frame_ptr_;

    public:
        explicit VideoFrameItem(QQuickItem *parent = nullptr);

        void paint(QPainter *painter) override;

        Q_INVOKABLE void setCurrentFrame(const QSharedPointer<QImage> &current_frame_ptr);
    };
}
