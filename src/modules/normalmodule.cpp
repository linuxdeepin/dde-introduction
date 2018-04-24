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
    m_leftNavigationLayout->setSpacing(10);

    m_rightContentLayout->setSpacing(0);
    m_rightContentLayout->setMargin(0);
    m_rightContentLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *logo = new QLabel(this);
    logo->setPixmap(QIcon::fromTheme("dde-introduction").pixmap(24, 24));
    logo->move(rect().topLeft() + QPoint(12, 8));
    logo->show();

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
                              "padding: 0px 15px;"
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

    QLabel *titleLabel = new QLabel;
    titleLabel->setStyleSheet("font-size: 20px;"
                              "font-weight: medium;");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(bottomNavigation);

    setLayout(mainLayout);

    setFixedSize(700, 450);
    content->setFixedWidth(580);

    NavigationButton * videoBtn = new NavigationButton;
    NavigationButton * desktopBtn = new NavigationButton;
    NavigationButton * iconBtn = new NavigationButton;
    NavigationButton * wmBtn = new NavigationButton;
    NavigationButton * supportBtn = new NavigationButton;
    NavigationButton * aboutBtn = new NavigationButton;

    m_buttonMap[videoBtn]   = 1;
    m_buttonMap[desktopBtn] = 2;
    m_buttonMap[iconBtn]    = 3;
    m_buttonMap[wmBtn]      = 4;
    m_buttonMap[supportBtn] = 5;
    m_buttonMap[aboutBtn]   = 6;


    videoBtn->setText(tr("Introduction"));
    desktopBtn->setText(tr("Desktop mode"));
    iconBtn->setText(tr("Icon theme"));
    wmBtn->setText(tr("Window effect"));
    supportBtn->setText(tr("Support us"));
    aboutBtn->setText(tr("About us"));

    videoBtn->setChecked(true);

    m_titleMap[videoBtn] = tr("Welcome");
    m_titleMap[desktopBtn] = tr("Please select desktop mode");
    m_titleMap[iconBtn] = tr("Please select icon theme");
    m_titleMap[wmBtn] = tr("Please select to enable window effect or not");
    m_titleMap[supportBtn] = tr("Support us");
    m_titleMap[aboutBtn] = tr("About us");

    titleLabel->setText(m_titleMap[videoBtn]);

    m_buttonGrp->addButton(videoBtn);
    m_buttonGrp->addButton(desktopBtn);
    m_buttonGrp->addButton(iconBtn);
    m_buttonGrp->addButton(wmBtn);
    m_buttonGrp->addButton(supportBtn);
    m_buttonGrp->addButton(aboutBtn);

    m_buttonGrp->setExclusive(true);

    m_leftNavigationLayout->addStretch();

    for (QWidget * w : m_buttonGrp->buttons()) {
        w->setFixedSize(120, 30);
        m_leftNavigationLayout->addWidget(w, 0, Qt::AlignLeft | Qt::AlignVCenter);
    }

    m_leftNavigationLayout->addStretch();

    connect(m_buttonGrp, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked), this, [=] (QAbstractButton *btn) {
        updateCurrentWidget(m_buttonMap[btn]);
        titleLabel->setText(m_titleMap[btn]);
    });

    updateCurrentWidget(m_buttonMap[videoBtn]);
}

void NormalModule::updateCurrentWidget(const int index)
{
    if (m_currentWidget) {
        m_rightContentLayout->removeWidget(m_currentWidget);
        m_currentWidget->deleteLater();
        m_currentWidget = nullptr;
    }

    switch (index) {
    case 1:
    {
        VideoWidget *w = new VideoWidget;
        w->updateSmallIcon();
        m_currentWidget = w;
        break;
    }
    case 2:
    {
        DesktopModeModule *w = new DesktopModeModule;
        w->updateSmallIcon();
        m_currentWidget = w;
        break;
    }
    case 3:
    {
        IconModule *w = new IconModule;
        w->updateSmallIcon();
        m_currentWidget = w;
        break;
    }
    case 4:
    {
        WMModeModule *w = new WMModeModule;
        w->updateSmallIcon();
        m_currentWidget = w;
        break;
    }
    case 5:
    {
        m_currentWidget = new Support;
        break;
    }
    case 6:
    {
        m_currentWidget = new About;
        break;
    }
    default:
        break;
    }

    m_currentWidget->setFixedWidth(580);
    m_rightContentLayout->addWidget(m_currentWidget, 0, Qt::AlignCenter);
    m_currentWidget->show();
}
