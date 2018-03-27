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
    layout->setContentsMargins(20, 10, 10, 10);
    layout->setSpacing(10);

    DImageButton *sinaBtn = new DImageButton(":/resources/weibo.svg",
                                             ":/resources/weibo.svg",
                                             ":/resources/weibo.svg");
    DImageButton *twitterBtn = new DImageButton(":/resources/Twitter.svg",
                                                ":/resources/Twitter.svg",
                                                ":/resources/Twitter.svg");
    DImageButton *facebook = new DImageButton(":/resources/Facebook.svg",
                                              ":/resources/Facebook.svg",
                                              ":/resources/Facebook.svg");

    DImageButton *offical = new DImageButton;
    offical->setText(tr("Official website"));

    DImageButton *community = new DImageButton;
    community->setText(tr("Community"));

    DImageButton *feedback = new DImageButton;
    feedback->setText(tr("Feedback"));

    DImageButton *thank = new DImageButton;
    thank->setText(tr("Acknowledgements"));

    DImageButton *mail = new DImageButton(":/resources/Mail.svg",
                                          ":/resources/Mail.svg",
                                          ":/resources/Mail.svg");

    connect(sinaBtn, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(twitterBtn, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(facebook, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(offical, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(community, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(feedback, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(thank, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);
    connect(mail, &DImageButton::clicked, this, &BottomNavigation::onButtonClicked);

    m_buttons[sinaBtn] = "https://weibo.com/p/1006062675284423/home";
    m_buttons[twitterBtn] = "https://twitter.com/linux_deepin";
    m_buttons[facebook] = "https://www.facebook.com/deepinlinux/";
    m_buttons[offical] = "https://www.deepin.org/";
    m_buttons[community] = "https://bbs.deepin.org/";
    m_buttons[feedback] = "http://feedback.deepin.org/";
    m_buttons[thank] = "https://www.deepin.org/acknowledgments/deepin/";
    m_buttons[mail] = "";

    layout->addWidget(sinaBtn, 0, Qt::AlignCenter);
    layout->addWidget(twitterBtn, 0, Qt::AlignCenter);
    layout->addWidget(facebook, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(offical, 0, Qt::AlignCenter);
    layout->addWidget(community, 0, Qt::AlignCenter);
    layout->addWidget(feedback, 0, Qt::AlignCenter);
    layout->addWidget(thank, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(mail, 0, Qt::AlignCenter);

    setLayout(layout);
}

void BottomNavigation::onButtonClicked()
{
    DImageButton *button = qobject_cast<DImageButton*>(sender());

    Q_ASSERT(button);

    QDesktopServices::openUrl(QUrl(m_buttons[button]));
}
