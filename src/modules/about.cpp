#include "about.h"

About::About(QWidget *parent)
    : QScrollArea(parent)
{
    DLabel *logo = new DLabel;
    DLabel *label = new DLabel;
    label->setWordWrap(true);
    setWidgetResizable(true);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWidget(label);

    label->setMargin(20);

    QString text;

#ifdef PROFESSIONAL
    text = QString("<body style=\"line-height: 18px;font-size:12px;font-style: normal;\">"
                   "<div style=\"font-style: medium;font-size: 16px;\">%1</div>"
                   "<br>%2"
                   "<br><div style=\"font-style: medium;font-size: 16px;\">%3</div>"
                   "<ul><li>%4</li></ul>"
                   "%5"
                   "<ul><li>%6</li></ul>"
                   "%7"
                   "<ul><li>%8</li></ul>"
                   "%9"
                   "<br><div style=\"font-style: medium;font-size: 16px;\">%10</div>"
                   "<br>%11</body>")
           .arg(tr("About us"))
           .arg(tr("deepin is a Linux distribution committed to providing elegant, user-friendly, safe and stable experience for users all over the world. It not only integrates and configures the best open-source products, but also develops a series of applications for daily use, such as Deepin Store, Deepin Screenshot, Deepin Music, Deepin Movie and so on, among which Deepin Desktop Environment and Deepin Control Center are based on Qt technology. deepin focuses on user-friendly experience and beautiful design, so it’s easy to install and use for most users and can well replace Windows for work and entertainment."))
           .arg(tr("Objective"))
           .arg(tr("Customer First"))
           .arg(tr("Deepin Technology takes user requirements as core, adheres to innovative idea, and bases on the market demand to feedback users with better products and services."))
           .arg(tr("Open Source Idea"))
           .arg(tr("The deepin project is a creative and energetic open source desktop operating system. It insists on the open source idea always, the development are under GPL License and all codes are open source, which has been uploaded to GitHub. Community members, open source fans and Deepin Technology will develop the deepin project together to make a due contribution to China open source."))
           .arg(tr("Open and Free"))
           .arg(tr("Only in a comfortable, pleasure and free working environment, one can get high work efficiency. In Deepin Technology, no long and boring meeting and workflow, no complicated class hierarchy, all are equal and cooperative. It provides regular professional training, prospective career development and mature promote channel for employees."))
           .arg(tr("Open source project"))
           .arg(tr("deepin is an open source desktop system developed for common users. You are free to download, distribute, modify and use it. Detailed address is GitHub: https://github.com/linuxdeepin"));
#else

    text = QString("<br><p style=\"font-family: SourceHanSansSC-Normal;font-size: 12px;color: #303030;line-height: 18px;\">%1<a href=https://github.com>%2</a>%3</p>"
                   "<p style=\"font-family: SourceHanSansSC-Medium;font-size: 16px;color: #000000;line-height: 18px;\">%4"
                   "<p style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%5</p>"
                   "<p style=\"font-family: SourceHanSansSC-Medium;font-size: 16px;color: #000000;line-height: 18px;\">%6"
                   "<p style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%7</br>"
                   "<br style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%8</br>"
                   "<br style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%9</br>"
                   "<br style=\"font-family: SourceHanSansSC-Medium;font-size: 12px;color: #303030;line-height: 18px;\">%10</p>"
                   "<p style=\"font-family: SourceHanSansSC-Medium;font-size: 16px;color: #000000;line-height: 18px;\">%11")
           .arg(tr("    Deep is an open source operating system development team in China, which has a history of 14 years. Many of our members have benefited from open source projects around the world, and based on the Linux open source project, the Deep Team has also received some business revenue to support its development. Therefore, it is very desirable to feed back the open source community through the deep operating system, so that more users around the world can use the best open source Linux operating system products. Our source code is open on "))
           .arg(tr("github"))
           .arg(tr(", and anyone who has doubts is welcome to know or use our code."))
           .arg(tr("■target"))
           .arg(tr("The World's Most Beautiful and Useful Linux Distribution"))
           .arg(tr("■History"))
           .arg(tr("Hiweed Linux was first released in 2004"))
           .arg(tr("Hiweed Linux renamed deepin in 2008"))
           .arg(tr("A new V15 version will be released in 2016"))
           .arg(tr("X Month X, 2018, latest version 1.5.1"))
           .arg(tr("■Open source projects"));
#endif

    label->setText(text);
}
