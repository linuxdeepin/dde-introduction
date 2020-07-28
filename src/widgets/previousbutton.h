#ifndef PREVIOUSBUTTON_H
#define PREVIOUSBUTTON_H

#include <DIconButton>
#include <QKeyEvent>

DWIDGET_USE_NAMESPACE

class previousButton : public DIconButton
{
public:
    previousButton(QWidget *parent = nullptr);

    void keyPressEvent(QKeyEvent *) override;
};

#endif // PREVIOUSBUTTON_H
