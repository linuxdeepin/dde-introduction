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

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QMap<QWidget*, QString> m_buttons;
};

#endif // BOTTOMNAVIGATION_H
