#include "closebutton.h"
#include <QDebug>

CloseButton::CloseButton(QWidget *parent)
    : QPushButton(parent)
{
    setFixedSize(QSize(33, 33));
    beFocused = false;
}

void CloseButton::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Return)
    emit closeMainWindow();
}

void CloseButton::paintEvent(QPaintEvent *event)
{
    if (this->hasFocus() || beFocused) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(2, 2, -3, -3), 5, 5);
        painter.setClipRect(QRect(), Qt::NoClip);
        QColor color = DGuiApplicationHelper::instance()->applicationPalette()
                    .highlight().color();
        QPen pen(color);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
    }

    QWidget::paintEvent(event);
}

void CloseButton::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
        emit closeMainWindow();
}
