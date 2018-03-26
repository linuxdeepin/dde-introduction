/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "normalmodule.h"
#include "../widgets/navigationbutton.h"
#include "desktopmodemodule.h"
#include "iconmodule.h"
#include "wmmodemodule.h"
#include "videowidget.h"
#include "support.h"
#include "about.h"
#include "../widgets/bottomnavigation.h"

NormalModule::NormalModule(QWidget *parent)
    : QWidget(parent)
    , m_leftNavigationLayout(new QVBoxLayout)
    , m_rightContentLayout(new QVBoxLayout)
    , m_buttonGrp(new QButtonGroup)
    , m_currentWidget(nullptr)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_leftNavigationLayout->setMargin(0);
    m_leftNavigationLayout->setSpacing(0);

    m_rightContentLayout->setSpacing(0);
    m_rightContentLayout->setMargin(0);

    QWidget *content = new QWidget;
    content->setLayout(m_rightContentLayout);

    QWidget *leftWidget = new QWidget;
    leftWidget->setObjectName("LeftWidget");
    leftWidget->setLayout(m_leftNavigationLayout);
    leftWidget->setStyleSheet("#LeftWidget {"
                              "border: solid #eee;"
                              "border-right-width: 1px;"
                              "}"
                              ""
                              "#LeftWidget > QPushButton {"
                              "margin: 0;"
                              "text-align: left;"
                              "padding: 5px 15px;"
                              "border: none;"
                              "}"
                              ""
                              "#LeftWidget > QPushButton:checked {"
                              "color: #2ca7f8;"
                              "font-weight: 500;"
                              "background-color: #d5edfe;"
                              "border: 1px solid rgba(44, 167, 248, .1);"
                              "border-left: none;"
                              "border-right: none;"
                              "}");

    layout->addWidget(leftWidget);
    layout->addWidget(content);

    // bottom navigation
    BottomNavigation *bottomNavigation = new BottomNavigation;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(bottomNavigation);

    setLayout(mainLayout);

    setFixedSize(700, 450);
    content->setFixedSize(580, 450);

    NavigationButton * videoBtn = new NavigationButton;
    NavigationButton * desktopBtn = new NavigationButton;
    NavigationButton * iconBtn = new NavigationButton;
    NavigationButton * wmBtn = new NavigationButton;
    NavigationButton * supportBtn = new NavigationButton;
    NavigationButton * aboutBtn = new NavigationButton;

    VideoWidget *video = new VideoWidget;
    DesktopModeModule *desktop = new DesktopModeModule;
    IconModule *icon = new IconModule;
    WMModeModule *wm = new WMModeModule;
    Support *support = new Support;
    About *about = new About;

    videoBtn->setText(tr("Introduction"));
    desktopBtn->setText(tr("Desktop mode"));
    iconBtn->setText(tr("Icon theme"));
    wmBtn->setText(tr("Window effect"));
    supportBtn->setText(tr("Support us"));
    aboutBtn->setText(tr("About us"));

    videoBtn->setChecked(true);

    m_rightContentLayout->addStretch();

    m_rightContentLayout->addWidget(video);
    m_rightContentLayout->addWidget(desktop);
    m_rightContentLayout->addWidget(icon);
    m_rightContentLayout->addWidget(wm);
    m_rightContentLayout->addWidget(support);
    m_rightContentLayout->addWidget(about);

    m_rightContentLayout->addStretch();

    video->setFixedWidth(580);
    desktop->setFixedWidth(580);
    icon->setFixedWidth(580);
    wm->setFixedWidth(580);

    desktop->updateSmaillIcon();
    icon->updateSmaillIcon();
    wm->updateSmaillIcon();

    video->hide();
    desktop->hide();
    icon->hide();
    wm->hide();
    support->hide();
    about->hide();

    m_moduleMap[videoBtn] = video;
    m_moduleMap[desktopBtn] = desktop;
    m_moduleMap[iconBtn] = icon;
    m_moduleMap[wmBtn] = wm;
    m_moduleMap[supportBtn] = support;
    m_moduleMap[aboutBtn] = about;

    m_currentWidget = video;

    videoBtn->setFixedWidth(120);
    desktopBtn->setFixedWidth(120);
    iconBtn->setFixedWidth(120);
    wmBtn->setFixedWidth(120);
    supportBtn->setFixedWidth(120);
    aboutBtn->setFixedWidth(120);

    m_buttonGrp->addButton(videoBtn);
    m_buttonGrp->addButton(desktopBtn);
    m_buttonGrp->addButton(iconBtn);
    m_buttonGrp->addButton(wmBtn);
    m_buttonGrp->addButton(supportBtn);
    m_buttonGrp->addButton(aboutBtn);

    m_buttonGrp->setExclusive(true);

    m_leftNavigationLayout->addStretch();
    m_leftNavigationLayout->addWidget(videoBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_leftNavigationLayout->addWidget(desktopBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_leftNavigationLayout->addWidget(iconBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_leftNavigationLayout->addWidget(wmBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_leftNavigationLayout->addWidget(supportBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_leftNavigationLayout->addWidget(aboutBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    m_leftNavigationLayout->addStretch();

    connect(m_buttonGrp, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked), this, [=] (QAbstractButton *btn) {
        QWidget *w = m_moduleMap[btn];
        m_currentWidget->hide();
        w->show();
        m_currentWidget = w;
    });
}
