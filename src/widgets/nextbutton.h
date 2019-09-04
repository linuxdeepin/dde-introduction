#ifndef NEXTBUTTON_H
#define NEXTBUTTON_H

#include <QPushButton>
//#include <dpushbutton.h>
#include <DPushButton>

class NextButton : public QPushButton
{
    Q_OBJECT
public:
    explicit NextButton(const QString &text, QWidget *parent = nullptr);

    enum Mode {
        Normal,
        Transparent
    };

    void setMode(Mode mode);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QString m_text;
    Mode m_mode;
    QColor m_currentColor;
};

#endif // NEXTBUTTON_H
