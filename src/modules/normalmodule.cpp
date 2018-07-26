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
    , m_index(-1)
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
    QIcon::setThemeName("hicolor");
    QPixmap pixmap = std::move(QIcon::fromTheme("dde-introduction", QIcon(":/resources/dde-introduction.svg")).pixmap(QSize(24, 24) * devicePixelRatioF()));
    pixmap.setDevicePixelRatio(devicePixelRatioF());
    logo->setPixmap(pixmap);
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

    bool allow_switch_wm = false;
    QFile file(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first() + QDir::separator() + "deepin/deepin-wm-switcher/config.json");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonDocument doc = std::move(QJsonDocument::fromJson(file.readAll()));
        QJsonObject obj = std::move(doc.object());
        allow_switch_wm = std::move(obj["allow_switch"].toBool());
    }

#ifndef DISABLE_VIDEO
    // video button
    NavigationButton * videoBtn = new NavigationButton;
    m_buttonMap[videoBtn]   = 1;
    videoBtn->setText(tr("Introduction"));
    m_titleMap[videoBtn] = tr("Welcome");
    m_buttonGrp->addButton(videoBtn);
    VideoWidget *videoModule = new VideoWidget(false, this);
    videoModule->hide();
    m_modules[1] = videoModule;
#endif

    // desktop button
    NavigationButton * desktopBtn = new NavigationButton;
    m_buttonMap[desktopBtn] = 2;
    desktopBtn->setText(tr("Desktop mode"));
    m_titleMap[desktopBtn] = tr("Please select desktop mode");
    m_buttonGrp->addButton(desktopBtn);
    DesktopModeModule *desktopModeModule = new DesktopModeModule(this);
    desktopModeModule->hide();
    m_modules[2] = desktopModeModule;

    // icon button
    NavigationButton * iconBtn = new NavigationButton;
    m_buttonMap[iconBtn]    = 3;
    iconBtn->setText(tr("Icon theme"));
    m_titleMap[iconBtn] = tr("Please select icon theme");
    m_buttonGrp->addButton(iconBtn);
    IconModule *iconModule = new IconModule(this);
    iconModule->hide();
    m_modules[3] = iconModule;

    // wm button
    NavigationButton * wmBtn = nullptr;
    if (allow_switch_wm) {
        wmBtn = new NavigationButton;
        m_buttonMap[wmBtn]      = 4;
        wmBtn->setText(tr("Window effect"));
        m_titleMap[wmBtn] = tr("Please select to enable window effect or not");
        m_buttonGrp->addButton(wmBtn);
        WMModeModule *wmModeModule = new WMModeModule(this);
        wmModeModule->hide();
        m_modules[4] = wmModeModule;
    }

    // support button
    NavigationButton * supportBtn = new NavigationButton;
    m_buttonMap[supportBtn] = 5;
    supportBtn->setText(tr("Support us"));
    m_titleMap[supportBtn] = tr("Support us");
    m_buttonGrp->addButton(supportBtn);
    Support *support = new Support(this);
    support->hide();
    m_modules[5] = support;

    // about button
    NavigationButton * aboutBtn = new NavigationButton;
    m_buttonMap[aboutBtn]   = 6;
    aboutBtn->setText(tr("About us"));
    m_titleMap[aboutBtn] = tr("About us");
    m_buttonGrp->addButton(aboutBtn);
    About *about = new About(this);
    about->hide();
    m_modules[6] = about;

#ifndef DISABLE_VIDEO
    videoBtn->setChecked(true);
    titleLabel->setText(m_titleMap[videoBtn]);
#else
    desktopBtn->setChecked(true);
    titleLabel->setText(m_titleMap[desktopBtn]);
#endif

    m_buttonGrp->setExclusive(true);

    m_leftNavigationLayout->addStretch();

    for (QWidget * w : m_buttonGrp->buttons()) {
        w->setFixedSize(120, 30);
        m_leftNavigationLayout->addWidget(w, 0, Qt::AlignLeft | Qt::AlignVCenter);
        w->installEventFilter(this);
    }

    m_leftNavigationLayout->addStretch();

    connect(m_buttonGrp, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked), this, [=] (QAbstractButton *btn) {
        updateCurrentWidget(m_buttonMap[btn]);
        titleLabel->setText(m_titleMap[btn]);
    });

#ifndef DISABLE_VIDEO
    updateCurrentWidget(m_buttonMap[videoBtn]);
#else
    updateCurrentWidget(m_buttonMap[desktopBtn]);
#endif
}

bool NormalModule::eventFilter(QObject *watched, QEvent *event)
{
    if (qobject_cast<NavigationButton*>(watched) && event->type() == QEvent::KeyPress) {
        return true;
    }

    return false;
}

void NormalModule::updateCurrentWidget(const int index)
{
    if (index == m_index) return;

    m_index = index;

    if (m_currentWidget) {
        m_rightContentLayout->removeWidget(m_currentWidget);
        m_currentWidget->hide();
    }

    QTimer::singleShot(100, this, [=] {
        QWidget *w = m_modules[index];
        ModuleInterface *module = qobject_cast<ModuleInterface*>(w);
        if (module) {
            module->updateSmallIcon();
            module->updateSelectBtnPos();
        }

        m_currentWidget = w;

        m_rightContentLayout->addWidget(m_currentWidget, 0, Qt::AlignCenter);
        m_currentWidget->setFixedWidth(580);
        m_currentWidget->show();
    });
}
