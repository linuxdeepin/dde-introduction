#include "coverphoto.h"

#include <QPainter>

CoverPhoto::CoverPhoto(QWidget *parent)
: DFrame(parent)
{

}

void CoverPhoto::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;

    update();
}

void CoverPhoto::paintEvent(QPaintEvent *event)
{
    DFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect pixRect(QPoint(0, 0), m_pixmap.size() / devicePixelRatioF());

    // draw background
    QPainterPath contentPath;
    contentPath.addRoundedRect(pixRect, 10, 10);
    painter.setClipPath(contentPath);
    painter.drawPixmap(pixRect, m_pixmap);
}
