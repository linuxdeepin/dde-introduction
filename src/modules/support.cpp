#include "support.h"

#include <QVBoxLayout>
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

    label->setMargin(10);

    label->setText("<body> \
                   <b>Internationalization</b> \
                   <br> deepin was born in China and aimed to go global. So as to make it possible for more and more users from around the world \
                   to experience the Linux distribution from China, let the system widely spread all over the world and enlarge its global \
                   impact, we hope that more and more people from the Linux community can join to help the translation work to let our open \
                   source work benefit the world! The i18n translation work is mainly about: deepin: Joining the document writing and i18n \
                   work to let our open source work benefit the world! Deepin community: Providing community news, download, mirrors, projects \
                   and a gathering place for developers! Welcome to join i18n project. \
                   <br> \
                   <b>Donations</b> \
                   <br> The development of deepin can not move on without community support, for further improve the construction of the deepin \
                   community environment, Deepin Technology has made the decision to officially open channels of donation. The donation \
                   upholds the principle of completely voluntary and no matter who you are, wherever you are, how much you contribute, are \
                   all making contributions to the development of Deepin community and we are very grateful for your donation. The donation \
                   aims to make a survey and decide the orientation and proirity of the projects, support the continuous further development, \
                   and support community activities and construction. \
                   <br> \
                   <b>Internal Testing</b> \
                   <br> For quality assurance of the deepin project, we welcome more people to participate in the internal testing and feedback \
                   tracking. Become a Internal Testing Team member, you will \
                   <li>Get the latest achievements of deepin and software timely.</li> \
                   <li>Obtain the latest development plans and progress of deepin project in advance.</li> \
                   <li>Be on deepin contributors list.</li> \
                   <li>Outstanding members will get a souvenir of deepin.</li> \
                   </body>");
}
