#ifndef COVERPHOTO_H
#define COVERPHOTO_H

#include <QPainter>

#include <DFrame>

DWIDGET_USE_NAMESPACE

class CoverPhoto : public DFrame
{
public:
    CoverPhoto(QWidget *parent = nullptr);

public slots:
    void setPixmap(const QPixmap &pixmap);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QPixmap m_pixmap;
};

#endif // COVERPHOTO_H
