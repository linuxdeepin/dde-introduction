#include "bottomnavigation.h"

#include <QHBoxLayout>
#include <dimagebutton.h>
#include <QDesktopServices>
#include <QUrl>

DWIDGET_USE_NAMESPACE

BottomNavigation::BottomNavigation(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(20, 0, 10, 0);
    layout->setSpacing(0);

    DImageButton *sinaBtn = new DImageButton;
    DImageButton *twitterBtn = new DImageButton;
    DImageButton *facebook = new DImageButton;

    DImageButton *offical = new DImageButton;
    offical->setText(tr("Official website"));

    DImageButton *community = new DImageButton;
    community->setText(tr("Community"));

    DImageButton *feedback = new DImageButton;
    feedback->setText(tr("Feedback"));

    DImageButton *thank = new DImageButton;
    thank->setText(tr("Acknowledgements"));

    connect(sinaBtn, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(twitterBtn, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(facebook, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(offical, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(community, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(feedback, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(thank, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);

    m_buttons[sinaBtn] = "https://weibo.com/p/1006062675284423/home";
    m_buttons[twitterBtn] = "https://twitter.com/linux_deepin";
    m_buttons[facebook] = "https://www.facebook.com/deepinlinux/";
    m_buttons[offical] = "https://www.deepin.org/";
    m_buttons[community] = "https://bbs.deepin.org/";
    m_buttons[feedback] = "http://feedback.deepin.org/";
    m_buttons[thank] = "https://www.deepin.org/acknowledgments/deepin/";

    layout->addWidget(sinaBtn);
    layout->addWidget(twitterBtn);
    layout->addWidget(facebook);
    layout->addWidget(offical);
    layout->addWidget(community);
    layout->addWidget(facebook);
    layout->addWidget(thank);

    setLayout(layout);
}

void BottomNavigation::onButtonClicked()
{
    DImageButton *button = qobject_cast<DImageButton*>(sender());

    Q_ASSERT(button);

    QDesktopServices::openUrl(QUrl(m_buttons[button]));
}
