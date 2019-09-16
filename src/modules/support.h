#ifndef SUPPORT_H
#define SUPPORT_H

#include <QScrollArea>
#include <DGuiApplicationHelper>

DGUI_USE_NAMESPACE

class Support : public QScrollArea
{
    Q_OBJECT
public:
    explicit Support(QWidget *parent = nullptr);

signals:

public slots:
    void initTheme(int type);
private:
    QString m_text;
};

#endif // SUPPORT_H
