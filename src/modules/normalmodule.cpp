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
#include "support.h"
#include "about.h"
#include "photoslide.h"
#include "../widgets/bottomnavigation.h"

#include <dlabel.h>

#ifndef DISABLE_VIDEO
#include "videowidget.h"
#endif

NormalModule::NormalModule(QWidget *parent)
    : QWidget(parent)
    , m_leftNavigationLayout(new QVBoxLayout)
    , m_rightContentLayout(new QVBoxLayout)
    , m_buttonGrp(new QButtonGroup)
    , m_currentWidget(nullptr)
    , m_wmSwitcher(new WMSwitcher("com.deepin.WMSwitcher", "/com/deepin/WMSwitcher", QDBusConnection::sessionBus(), this))
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
                              "background: #0081FF;"
                              "box-shadow: 0 4px 6px 0 rgba(44,167,248,0.40);"
                              "border-radius: 8px;"
                              "border-radius: 8px;"
                              "font-family: SourceHanSansSC-Medium;"
                              "font-size: 14px;"
                              "color: #FFFFFF;"
                              "}");

    layout->addWidget(leftWidget);
    layout->addWidget(content);

    // bottom navigation
    BottomNavigation *bottomNavigation = new BottomNavigation;

    DLabel *titleLabel = new DLabel;
    titleLabel->setStyleSheet("font-size: 20px;"
                              "font-weight: medium;");

    DLabel *describe = new DLabel;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(describe, 0, Qt::AlignCenter);
    mainLayout->addWidget(bottomNavigation);

    setLayout(mainLayout);

    setFixedSize(700, 450);
    content->setFixedWidth(580);

    int moduleCount = 0;
    bool allow_switch_wm = m_wmSwitcher->AllowSwitch();

#ifndef DISABLE_VIDEO
    // video button
    NavigationButton * videoBtn = new NavigationButton;
    m_buttonMap[videoBtn]   = ++moduleCount;
    videoBtn->setText(tr("Introduction"));
    m_titleMap[videoBtn] = tr("Welcome");
    m_buttonGrp->addButton(videoBtn);
    VideoWidget *videoModule = new VideoWidget(false, this);
    videoModule->hide();
    m_modules[moduleCount] = videoModule;
#else
    NavigationButton *slideBtn = new NavigationButton;
    m_buttonMap[slideBtn] = ++moduleCount;
    slideBtn->setText(tr("Introduction"));
    m_titleMap[slideBtn] = tr("Welcome");
    m_buttonGrp->addButton(slideBtn);
    PhotoSlide *slideModule = new PhotoSlide;
    slideModule->hide();
    slideModule->start(false, false, 2000);
    m_modules[moduleCount] = slideModule;
#endif

    // desktop button
    NavigationButton * desktopBtn = new NavigationButton;
    m_buttonMap[desktopBtn] = ++moduleCount;
    desktopBtn->setText(tr("Desktop mode"));
    m_titleMap[desktopBtn] = tr("Please select desktop mode");
    m_describeMap[desktopBtn] = tr("You can switch it in Mode by right clicking on dock");
    m_buttonGrp->addButton(desktopBtn);
    DesktopModeModule *desktopModeModule = new DesktopModeModule(this);
    desktopModeModule->hide();
    m_modules[moduleCount] = desktopModeModule;

    // wm button
    NavigationButton * wmBtn = nullptr;
    if (allow_switch_wm) {
        wmBtn = new NavigationButton;
        m_buttonMap[wmBtn]      = ++moduleCount;
        wmBtn->setText(tr("Operation mode"));
        m_titleMap[wmBtn] = tr("Please select the mode of operation");
        m_describeMap[wmBtn] = tr("If your computer configuration is not high, you are recommended to choose extreme speed mode");
        m_buttonGrp->addButton(wmBtn);
        WMModeModule *wmModeModule = new WMModeModule(this);
        wmModeModule->hide();
        m_modules[moduleCount] = wmModeModule;
    }

    // icon button
    NavigationButton * iconBtn = new NavigationButton;
    m_buttonMap[iconBtn]    = ++moduleCount;
    iconBtn->setText(tr("Icon theme"));
    m_titleMap[iconBtn] = tr("Please select icon theme");
    m_describeMap[iconBtn] = tr("You can change it in Control Center > Personalization > Theme > Icon Theme");
    m_buttonGrp->addButton(iconBtn);
    IconModule *iconModule = new IconModule(this);
    iconModule->hide();
    m_modules[moduleCount] = iconModule;

#ifndef PROFESSIONAL
    // support button
    NavigationButton * supportBtn = new NavigationButton;
    m_buttonMap[supportBtn] = ++moduleCount;
    supportBtn->setText(tr("Support us"));
    m_titleMap[supportBtn] = tr("Support us");
    m_buttonGrp->addButton(supportBtn);
    Support *support = new Support(this);
    support->hide();
    m_modules[moduleCount] = support;
#endif

    //support us
    NavigationButton * supportBtn = new NavigationButton;
    m_buttonMap[supportBtn]   = ++moduleCount;
    supportBtn->setText(tr("Support us"));
    m_titleMap[supportBtn] = tr("Support us");
    m_buttonGrp->addButton(supportBtn);
    Support *support = new Support(this);
    support->hide();
    m_modules[moduleCount] = support;

    // about button
    NavigationButton * aboutBtn = new NavigationButton;
    m_buttonMap[aboutBtn]   = ++moduleCount;
    aboutBtn->setText(tr("About us"));
    m_titleMap[aboutBtn] = tr("About us");
    m_buttonGrp->addButton(aboutBtn);
    About *about = new About(this);
    about->hide();
    m_modules[moduleCount] = about;

#ifndef DISABLE_VIDEO
    videoBtn->setChecked(true);
    titleLabel->setText(m_titleMap[videoBtn]);
#else
    slideBtn->setChecked(true);
    titleLabel->setText(m_titleMap[slideBtn]);
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
        describe->setText(m_describeMap[btn]);
    });

#ifndef DISABLE_VIDEO
    updateCurrentWidget(m_buttonMap[videoBtn]);
#else
    updateCurrentWidget(m_buttonMap[slideBtn]);
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
