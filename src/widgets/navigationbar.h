#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>

class NavigationBar : public QWidget
{
    Q_OBJECT

public:
    NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar();

signals:
    void currentIndexChanged(int);

private:
    void initUI();

private:
    QVBoxLayout *m_layout;
    QButtonGroup *m_buttonsGroup;
    QStringList m_buttonsName;
};

#endif
