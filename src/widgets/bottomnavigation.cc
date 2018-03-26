#include "bottomnavigation.h"

#include <QHBoxLayout>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

BottomNavigation::BottomNavigation(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    DImageButton *sinaBtn = new DImageButton;
    DImageButton *twitterBtn = new DImageButton;
    DImageButton *facebook = new DImageButton;

    setLayout(layout);
}
