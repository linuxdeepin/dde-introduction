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
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color:transparent;");
    setWidget(label);

    label->setMargin(10);

    const QString &text = QString("<body>"
                                  "<b>%1</b>"
                                  "<br>"
                                  "%2"
                                  "<br><b>%3</b>"
                                  "<li>%4</li>"
                                  "%5"
                                  "<li>%6</li>"
                                  "%7"
                                  "<li>%8</li>"
                                  "%9"
                                  "<br><b>%10</b>"
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

    label->setText(text);
}
