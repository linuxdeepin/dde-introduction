#include "about.h"

#include <QLabel>

About::About(QWidget *parent)
    : QScrollArea(parent)
{
    QLabel *label = new QLabel;
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

#ifndef PROFESSIONAL
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
    text = QString("<body style=\"line-height: 18px;font-size:12px;font-style: normal;\">"
                    "<p>%1</p>"
                    "<p>%2</p>"
                    "<p>%3</p>")
                    .arg(tr("deepin, bringing the world's leading technology and innovation into government information construction and enterprise information technology infrastructure, is one of the fastest growing operating systems in China today. Because of its ease of use and extendibility, many government and enterprise users choose deepin as their daily operating system, while the information departments and the maintenance departments are attracted by the stability, security and flexibility of deepin desktop environment. Deepin desktop, which can be installed on laptops and desktops, is stable and efficient as well as very easy to use, based on the wonderful product design and the advanced technology. Its simple user experience can help users reduce the browsing and searching time, and put more time into work."))
                    .arg(tr("The research and development team of deepin - Wuhan Deepin Technology Co., Ltd (Deepin Technology), established in 2011, taking operating system products as the core, focuses on the development of operating system software based on the Linux kernel, and provides users with solutions, management, maintenance, consultation, customization, development and other related services. As the core product of Deepin Technology, deepin software has obtained various outstanding achievements in domestic Linux operating system products and has been widely recognized in the world. "))
                    .arg(tr("Deepin Technology will continue to adhere to the open source and innovative spirit, take the opportunity of autonomous, controllable and replaceable operating system, build domestic operating system ecosystem and become a leading supplier of basic software products and solutions."));
#endif

    label->setText(text);
}
