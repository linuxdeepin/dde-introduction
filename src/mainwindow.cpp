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

#include "mainwindow.h"
#include "modules/videowidget.h"
#include "modules/desktopmodemodule.h"
#include "modules/wmmodemodule.h"
#include "modules/iconmodule.h"
#include "modules/normalmodule.h"
#include "basemodulewidget.h"

#include <QHBoxLayout>
#include <DTitlebar>
#include <DPlatformWindowHandle>

DWIDGET_USE_NAMESPACE

static const QSize WINDOW_SIZE { 700, 450 };
MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_index(1)
    , m_current(nullptr)
    , m_last(nullptr)
    , m_currentAni(new QPropertyAnimation(this))
    , m_lastAni(new QPropertyAnimation(this))
    , m_settings(new QSettings("deepin", "dde-introduction"))
{
    initUI();
    initConnect();
}

MainWindow::~MainWindow()
{

}

void MainWindow::previous()
{
    if (m_currentAni->state() == QPropertyAnimation::Running) {
        return;
    }

    updateModule(--m_index);

    m_currentAni->setDuration(300);
    m_lastAni->setEasingCurve(QEasingCurve::InOutCubic);
    m_currentAni->setStartValue(QPoint(m_last->x() - m_last->width(), 0));
    m_currentAni->setEndValue(m_last->rect().topLeft());

    m_lastAni->setDuration(300);
    m_currentAni->setEasingCurve(QEasingCurve::InOutCubic);
    m_lastAni->setStartValue(m_last->rect().topLeft());
    m_lastAni->setEndValue(m_last->rect().topRight());

    m_currentAni->start();
    m_lastAni->start();
}

void MainWindow::next()
{
    if (m_currentAni->state() == QPropertyAnimation::Running) {
        return;
    }

    // create new QWidget, change pointer
    updateModule(++m_index);

    m_lastAni->setDuration(300);
    m_lastAni->setEasingCurve(QEasingCurve::InOutCubic);
    m_lastAni->setStartValue(m_last->rect().topLeft());
    m_lastAni->setEndValue(QPoint(m_last->x() - m_last->width(), 0));

    m_currentAni->setDuration(300);
    m_currentAni->setEasingCurve(QEasingCurve::InOutCubic);
    m_currentAni->setStartValue(QPoint(m_last->rect().topRight()));
    m_currentAni->setEndValue(QPoint(0, 0));

    m_currentAni->start();
    m_lastAni->start();
}

void MainWindow::initUI()
{
    setFixedSize(WINDOW_SIZE);
    setWindowFlags(Qt::FramelessWindowHint);

    DPlatformWindowHandle* handle = new DPlatformWindowHandle(this);
    handle->setBorderWidth(0);
    handle->setWindowRadius(5);
    handle->setEnableSystemMove(true);
    handle->setEnableSystemResize(false);

    m_fakerWidget = new QWidget(this);
    m_fakerWidget->show();
    m_fakerWidget->setFixedSize(WINDOW_SIZE);

    m_previousBtn = new DImageButton(this);
    m_previousBtn->setNormalPic(":/resources/previous_normal.svg");
    m_previousBtn->setHoverPic(":/resources/previous_hover.svg");
    m_previousBtn->setPressPic(":/resources/previous_press.svg");
    m_previousBtn->setDisabledPic(":/resources/previous_disabled.svg");
    m_previousBtn->setFixedSize(27, 26);

    m_nextBtn = new NextButton(tr("Next"), this);
    m_doneBtn = new NextButton(tr("Done"), this);

    DImageButton *closeBtn = new DImageButton(":/resources/close_round_normal.svg",
                                              ":/resources/close_round_hover.svg",
                                              ":/resources/close_round_press.svg",this);

    closeBtn->setFixedSize(24, 24);

    closeBtn->move(rect().topRight() - QPoint(closeBtn->width(), 0));
    closeBtn->show();

#ifndef QT_DEBUG
    const bool isFirst = m_settings->value("IsFirst", true).toBool();

    if (isFirst) {
        m_settings->setValue("IsFirst", false);
        m_current = new VideoWidget(m_fakerWidget);
        m_previousBtn->hide();
        m_nextBtn->show();
        m_nextBtn->setMode(NextButton::Transparent);
    } else {
        m_current = new NormalModule(m_fakerWidget);
        m_previousBtn->hide();
        m_nextBtn->hide();
    }
#else
    m_current = new VideoWidget(m_fakerWidget);
    m_previousBtn->hide();
    m_nextBtn->show();
    m_nextBtn->setMode(NextButton::Transparent);
#endif

    m_nextBtn->setFixedHeight(24);
    m_doneBtn->setFixedHeight(24);

    m_current->setFixedSize(WINDOW_SIZE);
    m_current->show();

    m_previousBtn->move(20, height() - m_previousBtn->height() - 20);
    m_nextBtn->move(width() - m_nextBtn->width() - 20, height() - m_nextBtn->height()- 20);
    m_doneBtn->move(m_nextBtn->pos());
    m_doneBtn->hide();

    m_currentAni->setPropertyName("pos");
    m_lastAni->setPropertyName("pos");

    connect(closeBtn, &DImageButton::clicked, this, &MainWindow::close);
}

void MainWindow::initConnect()
{
    connect(m_previousBtn, &DImageButton::clicked, this, &MainWindow::previous);
    connect(m_nextBtn, &NextButton::clicked, this, &MainWindow::next);
    connect(m_currentAni, &QPropertyAnimation::finished, this, &MainWindow::animationHandle);
    connect(m_doneBtn, &NextButton::clicked, qApp, &QCoreApplication::quit);
}

void MainWindow::bindAnimation()
{
    m_currentAni->setTargetObject(m_current);
    m_lastAni->setTargetObject(m_last);
}

void MainWindow::updateModule(const int index)
{
    m_nextBtn->show();
    m_previousBtn->show();
    m_nextBtn->setMode(NextButton::Normal);
    m_doneBtn->hide();

    m_last = m_current;
    switch (index) {
    case 1:
        m_current = new VideoWidget(m_fakerWidget);
        m_current->setFixedSize(WINDOW_SIZE);
        m_previousBtn->hide();
        m_nextBtn->setMode(NextButton::Transparent);
        break;
    case 2:
        m_current = initDesktopModeModule();
        break;
    case 3:
    {
        QFile file(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first() + QDir::separator() + "deepin/deepin-wm-switcher/config.json");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QJsonDocument doc = std::move(QJsonDocument::fromJson(file.readAll()));
            QJsonObject obj = std::move(doc.object());
            if (obj["allow_switch"].toBool()) {
                m_current = initWMModeModule();
                break;
            }
        }
        ++m_index;
    }
    case 4:
        m_current = initIconModule();
        m_nextBtn->hide();
        m_doneBtn->show();
        break;
    case 5:
//        m_current = new NormalModule(m_fakerWidget);
//        m_nextBtn->hide();
//        m_previousBtn->hide();
        break;
    default:
        break;
    }

    m_current->show();

    bindAnimation();
}

void MainWindow::animationHandle()
{
    if (m_last) {
        m_last->deleteLater();
        m_last = nullptr;
    }
}

BaseModuleWidget *MainWindow::initDesktopModeModule()
{
    DesktopModeModule *module = new DesktopModeModule;
    module->updateBigIcon();

    BaseModuleWidget* w = new BaseModuleWidget(module, m_fakerWidget);
    w->setTitle(tr("Please select desktop mode"));
    w->setDescribe(tr("You can switch it in Mode by right clicking on dock"));
    w->setFixedSize(WINDOW_SIZE);
    return w;
}

BaseModuleWidget *MainWindow::initWMModeModule()
{
    WMModeModule *module = new WMModeModule;
    module->updateBigIcon();

    BaseModuleWidget* w = new BaseModuleWidget(module, m_fakerWidget);
    w->setTitle(tr("Please select to enable window effect or not"));
    w->setDescribe(tr("You can enable or disable it in Control Center > Personalization > Enable window effect, or use shortcuts Shift+Super+Tab"));
    w->setFixedSize(WINDOW_SIZE);
    return w;
}

BaseModuleWidget *MainWindow::initIconModule()
{
    IconModule *module = new IconModule;
    module->updateBigIcon();

    BaseModuleWidget* w = new BaseModuleWidget(module, m_fakerWidget);
    w->setTitle(tr("Please select icon theme"));
    w->setDescribe(tr("You can change it in Control Center > Personalization > Theme > Icon Theme"));
    w->setFixedSize(WINDOW_SIZE);
    return w;
}
