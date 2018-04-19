#include "nextbutton.h"

#include <QPainterPath>
#include <QPainter>

#define DEFAULT_BG_COLOR  255, 255, 255, 0.2 * 255
#define HOVER_BG_COLOR    255, 255, 255, 0.3 * 255
#define PRESS_BG_COLOR    255, 255, 255, 0.1 * 255

NextButton::NextButton(const QString &text, QWidget *parent)
    : QPushButton(parent)
    , m_text(text)
    , m_mode(Normal)
    , m_currentColor(QColor(DEFAULT_BG_COLOR))
{
    setText(text);

    update();
}

void NextButton::setMode(NextButton::Mode mode)
{
    m_mode = mode;

    update();
}

void NextButton::paintEvent(QPaintEvent *event)
{
    switch (m_mode) {
    case Transparent: {
        QPainter painter(this);

        QPainterPath path;
        path.addRoundedRect(rect(), 5, 5);

        painter.fillPath(path, m_currentColor);

        painter.setPen(Qt::black);
        painter.drawText(rect(), Qt::AlignCenter, m_text);
        break;
    }
    case Normal:
    default:
        QPushButton::paintEvent(event);
        break;
    }
}

void NextButton::enterEvent(QEvent *event)
{
    QPushButton::enterEvent(event);

    m_currentColor = QColor(HOVER_BG_COLOR);

    update();
}

void NextButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);

    m_currentColor = QColor(DEFAULT_BG_COLOR);

    update();
}

void NextButton::mousePressEvent(QMouseEvent *event)
{
    QPushButton::mousePressEvent(event);

    m_currentColor = QColor(PRESS_BG_COLOR);

    update();
}
