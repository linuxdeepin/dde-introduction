#ifndef ABOUT_H
#define ABOUT_H

#include <QScrollArea>
#include <DLabel>

DWIDGET_USE_NAMESPACE

class About : public QScrollArea
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = nullptr);

};

#endif // ABOUT_H
