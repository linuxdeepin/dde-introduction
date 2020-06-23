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

NormalModule::NormalModule(DWidget *parent)
    : DWidget(parent)
    , m_leftNavigationLayout(new QVBoxLayout)
    , m_rightContentLayout(new QVBoxLayout)
    , m_buttonGrp(new QButtonGroup)
    , m_currentWidget(nullptr)
    , m_wmSwitcher(new WMSwitcher("com.deepin.WMSwitcher", "/com/deepin/WMSwitcher",
                                  QDBusConnection::sessionBus(), this))
    , m_titleLabel(new DLabel(this))
    , m_describe(new DLabel(this))
    , m_index(-1)
{
    isx86 = QSysInfo::currentCpuArchitecture().startsWith("x86");
    // initTheme(0);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 13, 20, 0);
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this,
            &NormalModule::updateLabel);

    // m_leftNavigationLayout->setMargin(0);
    m_leftNavigationLayout->setSpacing(10);
    m_leftNavigationLayout->setContentsMargins(0, 50, 0, 0);

    m_rightContentLayout->setSpacing(0);
    m_rightContentLayout->setMargin(0);
    m_rightContentLayout->setContentsMargins(0, 0, 0, 0);

    /*DLabel *logo = new DLabel(this);
    //    QIcon::setThemeName("hicolor");
    //    QPixmap pixmap = std::move(QIcon::fromTheme("dde-introduction",
    QIcon(":/resources/dde-introduction.svg")).pixmap(QSize(24, 24) * devicePixelRatioF())); QPixmap
    pixmap = QIcon::fromTheme("dde-introduction").pixmap(QSize(24, 24) * devicePixelRatioF());
    pixmap.setDevicePixelRatio(devicePixelRatioF());
    logo->setPixmap(pixmap);
    logo->move(rect().topLeft() + QPoint(12, 8));
    logo->show();*/

    m_content = new DWidget;
    m_content->setLayout(m_rightContentLayout);

    DWidget *leftWidget = new DWidget;
    leftWidget->setObjectName("LeftWidget");
    leftWidget->setLayout(m_leftNavigationLayout);

    layout->addWidget(leftWidget);
    layout->addWidget(m_content);

    // bottom navigation
    // BottomNavigation *bottomNavigation = new BottomNavigation;

    QFont font;
    font.setFamily("SourceHanSansSC");
    font.setStyleName("Bold");
    m_titleLabel->setFont(font);
    DFontSizeManager::instance()->bind(m_titleLabel, DFontSizeManager::T5);

    QFont deFont;
    deFont.setFamily("SourceHanSansSC");
    deFont.setStyleName("Normal");
    deFont.setPixelSize(12);
    m_describe->setFont(deFont);
    DFontSizeManager::instance()->bind(m_describe, DFontSizeManager::T8);

    updateLabel();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(m_titleLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(m_describe, 0, Qt::AlignCenter);
    // mainLayout->addWidget(bottomNavigation);
    mainLayout->setContentsMargins(0, 0, 0, 20);

    setLayout(mainLayout);

    setFixedSize(700, 450);
    m_content->setFixedSize(549, 343);

    int moduleCount = 0;
    bool allow_switch_wm = m_wmSwitcher->AllowSwitch();

#ifndef DISABLE_VIDEO
    NavigationButton *videoBtn = new NavigationButton(tr("Introduction"));
    videoBtn->setToolTip(tr("Introduction"));
    m_buttonMap[videoBtn] = ++moduleCount;
    m_titleMap[videoBtn] = tr("Welcome");
    m_buttonGrp->addButton(videoBtn);
    VideoWidget *videoModule = new VideoWidget(false, this);
    videoModule->hide();
    m_modules[moduleCount] = videoModule;
#else
    NavigationButton *slideBtn = new NavigationButton(tr("Introduction"));
    slideBtn->setToolTip(tr("Introduction"));
    m_buttonMap[slideBtn] = ++moduleCount;
    m_titleMap[slideBtn] = tr("Welcome");
    m_buttonGrp->addButton(slideBtn);
    PhotoSlide *slideModule = new PhotoSlide;
    slideModule->hide();
    slideModule->start(false, false, 2000);
    m_modules[moduleCount] = slideModule;
#endif

    // desktop button
    NavigationButton *desktopBtn = new NavigationButton(tr("Desktop Mode"));
    desktopBtn->setToolTip(tr("Desktop Mode"));
    m_buttonMap[desktopBtn] = ++moduleCount;
    m_titleMap[desktopBtn] = tr("Choose a desktop mode");
    m_describeMap[desktopBtn] = tr("You can switch modes by right clicking on the dock");
    m_buttonGrp->addButton(desktopBtn);
    DesktopModeModule *desktopModeModule = new DesktopModeModule(this);
    desktopModeModule->setFirst(false);
    desktopModeModule->hide();
    m_modules[moduleCount] = desktopModeModule;

    const DSysInfo::DeepinType DeepinType = DSysInfo::deepinType();
    bool IsServerSystem = (DSysInfo::DeepinServer == DeepinType);
    bool m_bSystemIsServer = IsServerSystem;

    // wm button
    if (!m_bSystemIsServer) {
        NavigationButton *wmBtn = nullptr;
        bool isSuportEffect = QDBusInterface("com.deepin.wm", "/com/deepin/wm", "com.deepin.wm")
                                  .property("compositingAllowSwitch")
                                  .toBool();
        if (allow_switch_wm && isSuportEffect) {
            wmBtn = new NavigationButton(tr("Running Mode"));
            wmBtn->setToolTip(tr("Running Mode"));
            m_buttonMap[wmBtn] = ++moduleCount;
            connect(wmBtn, &NavigationButton::widthChanged, this, &NormalModule::updateInterface);
            m_titleMap[wmBtn] = tr("Choose a running mode");
            m_describeMap[wmBtn] =
                tr("Please choose normal mode if you has a low configuration computer");
            m_buttonGrp->addButton(wmBtn);
            WMModeModule *wmModeModule = new WMModeModule(this);
            wmModeModule->setFirst(false);
            wmModeModule->hide();
            m_modules[moduleCount] = wmModeModule;
        }
    }

    // icon button
    NavigationButton *iconBtn = new NavigationButton(tr("Icon Theme"));
    iconBtn->setFixedSize(200, 200);
    iconBtn->setToolTip(tr("Icon Theme"));
    m_buttonMap[iconBtn] = ++moduleCount;
    // iconBtn->setText(tr("Icon theme"));
    m_titleMap[iconBtn] = tr("Choose an icon theme");
    m_describeMap[iconBtn] = tr("Change it in Control Center > Personalization > Icon Theme");
    m_buttonGrp->addButton(iconBtn);
    IconModule *iconModule = new IconModule(this);
    iconModule->hide();
    m_modules[moduleCount] = iconModule;

    // support us
    /*NavigationButton *supportBtn = new NavigationButton(tr("Support us"));
    m_buttonMap[supportBtn]   = ++moduleCount;
    //supportBtn->setText(tr("Support us"));
    m_titleMap[supportBtn] = tr("Support us");
    m_buttonGrp->addButton(supportBtn);
    Support *support = new Support(this);
    support->hide();
    m_modules[moduleCount] = support;*/

    // about button
    /*NavigationButton *aboutBtn = new NavigationButton(tr("About us"));
    m_buttonMap[aboutBtn] = ++moduleCount;
    aboutBtn->setText(tr("About us"));
    m_titleMap[aboutBtn] = tr("About us");
    m_buttonGrp->addButton(aboutBtn);
    About *about = new About(this);
    about->hide();
    m_modules[moduleCount] = about;*/

#ifndef DISABLE_VIDEO
    //    if (isx86) {
    videoBtn->setChecked(true);
    m_titleLabel->setText(m_titleMap[videoBtn]);
//    } else {
#else
    slideBtn->setChecked(true);
    m_titleLabel->setText(m_titleMap[slideBtn]);
//    }
#endif

    m_buttonGrp->setExclusive(true);

    // m_leftNavigationLayout->addStretch();

    for (QWidget *w : m_buttonGrp->buttons()) {
        // w->setFixedSize(110, 30);
        w->setMinimumSize(110, 10);
        m_leftNavigationLayout->addWidget(w, 0, Qt::AlignHCenter | Qt::AlignVCenter);
        w->installEventFilter(this);
    }
    m_leftNavigationLayout->addStretch();

    // m_leftNavigationLayout->addStretch();

    connect(m_buttonGrp,
            static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            this, [=](QAbstractButton *btn) {
                updataButton(btn);
                updateCurrentWidget(m_buttonMap[btn]);
                m_titleLabel->setText(m_titleMap[btn]);
                m_describe->setText(m_describeMap[btn]);
            });

#ifndef DISABLE_VIDEO
    //    if (isx86) {
    updateCurrentWidget(m_buttonMap[videoBtn]);
    m_button = videoBtn;
//    } else {
#else
    updateCurrentWidget(m_buttonMap[slideBtn]);
    m_button = slideBtn;
//    }
#endif
}

void NormalModule::keyPressEvent(QKeyEvent *event)
{
    QWidget *w = m_modules[m_index];

    if(event->key() == Qt::Key_Up) {
        int index = m_index;
        if (index == 1) return;

        index = -index;

        QAbstractButton *btn = m_buttonGrp->button(index - 1);
        btn->setChecked(false);

        btn = m_buttonGrp->button(index);
        btn->setChecked(true);

        updataButton(btn);
        updateCurrentWidget(m_buttonMap[btn]);
        m_titleLabel->setText(m_titleMap[btn]);
        m_describe->setText(m_describeMap[btn]);
    }
    else if(event->key() == Qt::Key_Down) {
        int index = m_index;
        if (index == 4) return;

        index = -index - 2;

        QAbstractButton *btn = m_buttonGrp->button(index + 1);
        btn->setChecked(false);

        btn = m_buttonGrp->button(index);
        btn->setChecked(true);

        updataButton(btn);
        updateCurrentWidget(m_buttonMap[btn]);
        m_titleLabel->setText(m_titleMap[btn]);
        m_describe->setText(m_describeMap[btn]);
    }
    else {
        switch (m_index) {
            case 1:
#ifndef DISABLE_VIDEO
                static_cast<VideoWidget *>(w)->keyPressEvent(event);
                break;
#else
                break;
#endif
            case 2:
                static_cast<DesktopModeModule *>(w)->keyPressEvent(event);
                break;
            case 3:
                static_cast<WMModeModule *>(w)->keyPressEvent(event);
                break;
            case 4:
                static_cast<IconModule *>(w)->keyPressEvent(event);
                break;
            default:
                break;
        }
    };
}

/*void NormalModule::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Left)
        return;
}*/

bool NormalModule::eventFilter(QObject *watched, QEvent *event)
{
    if (qobject_cast<NavigationButton *>(watched) && event->type() == QEvent::KeyPress) {
        return true;
    }

    return false;
}

void NormalModule::updateCurrentWidget(const int index)
{
    if (index == m_index)
        return;

    m_index = index;

    if (m_currentWidget) {
        m_rightContentLayout->removeWidget(m_currentWidget);
        m_currentWidget->hide();
    }

    QTimer::singleShot(100, this, [=] {
        QWidget *w = m_modules[index];
        ModuleInterface *module = qobject_cast<ModuleInterface *>(w);
        if (module) {
            module->updateSmallIcon();
            module->updateSelectBtnPos();
        }
        if (index != 1) {
            QWidget *w = m_modules[1];
#ifndef DISABLE_VIDEO
            VideoWidget *video = qobject_cast<VideoWidget *>(w);
            if (video) {
                video->stop();
            }
            video->showVideoControlButton();
#endif
        }

        m_currentWidget = w;

        m_rightContentLayout->addWidget(m_currentWidget, 0, Qt::AlignCenter);
        m_currentWidget->setFixedSize(549, 309);
        m_currentWidget->show();
    });
}

void NormalModule::updataButton(QAbstractButton *btn)
{
    m_button->initButton();
    m_button = dynamic_cast<NavigationButton *>(btn);
}

void NormalModule::initTheme(int type)
{
    if (type == 0) {
        type = DGuiApplicationHelper::instance()->themeType();
    }
    if (type == 2) {
        DPalette pa = this->palette();
        pa.setColor(DPalette::Window, QColor(40, 40, 40));
        this->setPalette(pa);
    }
}

void NormalModule::updateLabel()
{
    DPalette dePa = m_describe->palette();
    int type = DGuiApplicationHelper::instance()->themeType();
    if (type == 1)
        dePa.setColor(DPalette::WindowText, QColor("#FF8AA1B4"));
    else
        dePa.setColor(DPalette::WindowText, QColor("#FFC0C6D4"));
    m_describe->setPalette(dePa);
}

void NormalModule::updateInterface(int width)
{
    if (width < 110) {
        for (QWidget *w : m_buttonGrp->buttons()) {
            w->setMinimumSize(110, 30);
            m_content->setFixedSize(549, 343);
        }
        QWidget *w = m_modules[m_index];
        switch (m_index) {
            case 1:
#ifndef DISABLE_VIDEO
                static_cast<VideoWidget *>(w)->updateInterface(QSize(549, 343));
#endif
                break;
            case 2:
                static_cast<DesktopModeModule *>(w)->updateInterface(1.0);
                break;
            /*case 3:
                static_cast<WMModeModule *>(w)->keyPressEvent(e);
                break;
            case 4:
                static_cast<IconModule *>(w)->keyPressEvent(e);
                break;*/
            default:
                break;
        };
        return;
    }
    QSize size(549, 343);
    int widgetWidth = size.width() - (width - 110);
    int widgetHeigh = size.height() * (widgetWidth / size.width());
    m_content->setFixedSize(widgetWidth, widgetHeigh);

    QWidget *w = m_modules[m_index];
    float f = float(110.0 / width);
    switch (m_index) {
        case 1:
#ifndef DISABLE_VIDEO
            static_cast<VideoWidget *>(w)->updateInterface(QSize(widgetWidth, widgetHeigh));
#endif
            break;
        case 2:
            static_cast<DesktopModeModule *>(w)->updateInterface(f);
            break;
        /*case 3:
            static_cast<WMModeModule *>(w)->keyPressEvent(e);
            break;
        case 4:
            static_cast<IconModule *>(w)->keyPressEvent(e);
            break;*/
        default:
            break;
    };

    for (QWidget *w : m_buttonGrp->buttons()) {
        w->setMinimumSize(width + 15, 30);
    }
}

NormalModule::~NormalModule()
{
    delete m_buttonGrp;
}
