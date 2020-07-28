#include "iconbutton.h"

IconButton::IconButton(QWidget *parent)
    : DFloatingButton(parent)
{
    setFixedSize(QSize(22,22));
    setIconSize(QSize(9,9));
    setIcon(DStyle::SP_MarkElement);
    setAttribute(Qt::WA_TransparentForMouseEvents, true);
    setFocusPolicy(Qt::NoFocus);
}

