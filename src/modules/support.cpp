#include "support.h"

#include <QLabel>

Support::Support(QWidget *parent)
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

    label->setMargin(20);

    const QString &text = QString("<body style=\"line-height: 18px;font-size:12px;font-style: normal;\">"
                                  "<div style=\"font-style: medium;font-size: 16px;\">%1</div>"
                                  "<br>%2"
                                  "<br>%3"
                                  "<br>%4"
                                  "<br>%5"
                                  "<br>%6"
                                  "<br><div style=\"font-style: medium;font-size: 16px;\">%7</div>"
                                  "<br>%8"
                                  "<br>%9"
                                  "<br>%10"
                                  "<br><div style=\"font-style: medium;font-size: 16px;\">%11</div>"
                                  "<br>%12"
                                  "<ul>"
                                  "<li>%13</li>"
                                  "<li>%14</li>"
                                  "<li>%15</li>"
                                  "<li>%16</li>"
                                  "</ul></body>")
            .arg(tr("Internationalization"))
            .arg(tr("deepin was born in China and aimed to go global. So as to make it possible for more and more users from around the world to experience the Linux distribution from China, let the system widely spread all over the world and enlarge its global impact, we hope that more and more people from the Linux community can join to help the translation work to let our open source work benefit the world!"))
            .arg(tr("The i18n translation work is mainly about:"))
            .arg(tr("deepin: Joining the document writing and i18n work to let our open source work benefit the world!"))
            .arg(tr("Deepin community: Providing community news, download, mirrors, projects and a gathering place for developers!"))
            .arg(tr("Welcome to join i18n project."))
            .arg(tr("Donations"))
            .arg(tr("The development of deepin can not move on without community support, for further improve the construction of the deepin community environment, Deepin Technology has made the decision to officially open channels of donation."))
            .arg(tr("The donation upholds the principle of completely voluntary and no matter who you are, wherever you are, how much you contribute, are all making contributions to the development of Deepin community and we are very grateful for your donation."))
            .arg(tr("The donation aims to make a survey and decide the orientation and priority of the projects, support the continuous further development, and support community activities and construction."))
            .arg(tr("Internal Testing"))
            .arg(tr("For quality assurance of the deepin project, we welcome more people to participate in the internal testing and feedback tracking. Become an Internal Testing Team member, you will"))
            .arg(tr("Get the latest achievements of deepin and software timely."))
            .arg(tr("Obtain the latest development plans and progress of deepin project in advance."))
            .arg(tr("Be on deepin contributors list."))
            .arg(tr("Outstanding members will get a souvenir of deepin."));

    label->setText(text);
}
