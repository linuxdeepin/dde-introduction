#include "nextbutton.h"

#include <QPainterPath>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#define DEFAULT_BG_COLOR  255, 255, 255, 1.0 * 255
#define HOVER_BG_COLOR    255, 255, 255, 0.3 * 255
#define PRESS_BG_COLOR    255, 255, 255, 0.1 * 255

NextButton::NextButton(const QString &text, QWidget *parent)
    : DPushButton(parent)
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
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(rect(), 8, 8);

    //Setting Gradient
    QLinearGradient linear(rect().topLeft(), rect().bottomRight());
    linear.setColorAt(0, QColor(230,230,230,255));
    linear.setColorAt(1, QColor(227,227,227,255));
    linear.setSpread(QGradient::PadSpread);
    painter.fillPath(path, linear);

    //Inner border
    painter.setPen(QPen(QColor(0,0,0,0.03*255), 1));
    painter.drawRoundedRect(QRect(QPoint(rect().topLeft().x() + 1, rect().topLeft().y() + 1),
                                  QPoint(rect().bottomRight().x() - 1, rect().bottomRight().y() - 1)), 8, 8);
    //Text
    painter.setPen(QPen(Qt::black, 1));
    painter.drawText(rect(), Qt::AlignCenter, m_text);
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
