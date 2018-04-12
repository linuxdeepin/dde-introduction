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

    label->setText(tr("<body> \
                      <b>About us</b>  \
                      <br> deepin is a Linux distribution committed to providing elegant, user-friendly, safe and stable experience for users all \
                      over the world. It not only integrates and configures the best open-source products, but also develops a series of applications \
                      for daily use, such as Deepin Store, Deepin Screenshot, Deepin Music, Deepin Movie and so on, among which Deepin Desktop \
                      Environment and Deepin Control Center are based on Qt technology. deepin focuses on user-friendly experience and beautiful \
                      design, so it’s easy to install and use for most users and can well replace Windows for work and entertainment. \
                      <br> \
                      <b>Objective</b> \
                      <br> \
                      <li>Customer First</li> \
                      Deepin Technology takes user requirements as core, adheres to innovative idea, and bases on the market demand to feedback \
                      users with better products and services. \
                      <br> \
                      <li>Open Source Idea</li> \
                      The deepin project is a creative and energetic open source desktop operating system. It insists on the open source idea always, \
                      the development are under GPL License and all codes are open source, which has been uploaded to GitHub. Community members, \
                      open source fans and Deepin Technology will develop the deepin project together to make a due contribution to China open \
                      source. \
                      <li>Open and Free</li> \
                      Only in a comfortable, pleasure and free working environment, one can get high work efficiency. In Deepin Technology, no \
                      long and boring meeting and workflow, no complicated class hierarchy, all are equal and cooperative. It provides regular \
                      professional training, prospective career development and mature promote channel for employees. \
                      <br> \
                      <b>source project deepin</b> \
                      <br> is an open source desktop system developed for common users. You are free to download, distribute, modify and use it. \
                      Detailed address is GitHub: https://github.com/linuxdeepin \
                      </body>"));
}
