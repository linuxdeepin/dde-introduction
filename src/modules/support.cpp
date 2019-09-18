#include "support.h"

#include <DLabel>

DWIDGET_USE_NAMESPACE

Support::Support(QWidget *parent)
    : QScrollArea(parent)
{
    DLabel *label = new DLabel;
    label->setWordWrap(true);
    setWidgetResizable(true);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(DFrame::NoFrame);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWidget(label);

    label->setMargin(20);

    const QString &text = QString("<p style=\"font-family: SourceHanSansSC-Medium;font-size: 16px;color: #000000;line-height: 18px;\">%1</p>"
                                  "<div style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%2<a href=http://www.deepin.org/donate>%3</a>%4</div>"
                                  "<p style=\"font-family: SourceHanSansSC-Medium;font-size: 16px;color: #000000;line-height: 18px;\">%5</p>"
                                  "<div style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%6<a href=http://www.deepin.org/donate>%7</a></div>"
                                  "<p style=\"font-family: SourceHanSansSC-Medium;font-size: 16px;color: #000000;line-height: 18px;\">%8</p>"
                                  "<div style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%9<a href=http://www.deepin.org>%10</a></div>")
                          .arg(tr("■Localization"))
                          .arg(tr("Deep OS supports 30 languages, but we want to do better! If you want to use your own national language perfectly in Deep Operating System, please join our "))
                          .arg(tr("transfixer"))
                          .arg(tr(" community to help us!"))
                          .arg(tr("■Donate or buy souvenirs"))
                          .arg(tr("Over the past decade, we have been moving forward and striving to provide the best desktop operating system experience. Welcome to buy our souvenirs. It not only makes you more personalized, but also helps us to make depth better!"))
                          .arg(tr("www.deepin.org/donate"))
                          .arg(tr("■Become our charging user"))
                          .arg(tr("You can also become an individual payer to support us and gain more rights and interests at "))
                          .arg(tr("www.deepin.org"));

    label->setText(text);
}
