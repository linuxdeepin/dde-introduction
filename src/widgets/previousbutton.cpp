#include "previousbutton.h"

previousButton::previousButton(QWidget *parent)
    : DIconButton(parent)
{
    setFixedSize(36, 36);
}

void previousButton::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left ||
        event->key() == Qt::Key_Right ||
        event->key() == Qt::Key_Up ||
        event->key() == Qt::Key_Down)
        return;

    DIconButton::keyPressEvent(event);
}
