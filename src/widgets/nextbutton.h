#ifndef NEXTBUTTON_H
#define NEXTBUTTON_H

#include <QPushButton>
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#include <DPushButton>

DWIDGET_USE_NAMESPACE

class NextButton : public DPushButton
{
    Q_OBJECT
public:
    explicit NextButton(const QString &text, QWidget *parent = nullptr);

    enum Mode {
        Normal,
        Transparent
    };

    void setMode(Mode mode);

protected:
    //void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QString m_text;
    Mode m_mode;
    QColor m_currentColor;
};

#endif // NEXTBUTTON_H
