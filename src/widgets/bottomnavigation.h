#ifndef BOTTOMNAVIGATION_H
#define BOTTOMNAVIGATION_H

#include <QWidget>
#include <QMap>

class BottomNavigation : public QWidget
{
    Q_OBJECT
public:
    explicit BottomNavigation(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();

private:
    QMap<QWidget*, QString> m_buttons;
};

#endif // BOTTOMNAVIGATION_H
