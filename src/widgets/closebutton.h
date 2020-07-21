#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QPushButton>
#include <QPainter>
#include <DGuiApplicationHelper>
#include <QKeyEvent>
#include <QMouseEvent>

DGUI_USE_NAMESPACE

class CloseButton : public QPushButton
{
    Q_OBJECT

public:
    CloseButton(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool beFocused;

signals:
    void closeMainWindow();
};

#endif // CLOSEBUTTON_H
