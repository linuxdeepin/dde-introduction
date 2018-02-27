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
#include "basemodulewidget.h"

#include <QHBoxLayout>

static const QSize WINDOW_SIZE { 700, 450 };
MainWindow::MainWindow(QWidget *parent)
    : DDialog(parent)
    , m_index(1)
    , m_current(nullptr)
    , m_last(nullptr)
    , m_currentAni(new QPropertyAnimation(this))
    , m_lastAni(new QPropertyAnimation(this))
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
}

void MainWindow::next()
{
    if (m_currentAni->state() == QPropertyAnimation::Running) {
        return;
    }

    // create new QWidget, change pointer
    updateModule(++m_index);

    // update animation direction
    m_currentAni->start();
    m_lastAni->start();
}

void MainWindow::initUI()
{
    setFixedSize(WINDOW_SIZE);

    m_fakerWidget = new QWidget(this);
    m_fakerWidget->show();
    m_fakerWidget->setFixedSize(WINDOW_SIZE);

    m_previousBtn = new DImageButton;
    m_nextBtn     = new QPushButton(tr("next"), this);

    m_current = initVideoWidgt();
    m_current->setFixedSize(WINDOW_SIZE);
    m_current->show();

    m_nextBtn->move(550, 405);

    m_currentAni->setPropertyName("pos");
    m_lastAni->setPropertyName("pos");
}

void MainWindow::initConnect()
{
    connect(m_previousBtn, &DImageButton::clicked, this, &MainWindow::previous);
    connect(m_nextBtn, &QPushButton::clicked, this, &MainWindow::next);
    connect(m_currentAni, &QPropertyAnimation::finished, this, &MainWindow::animationHandle);
    connect(m_lastAni, &QPropertyAnimation::finished, this, &MainWindow::animationHandle);
}

void MainWindow::bindAnimation()
{
    m_currentAni->setTargetObject(m_last);
    m_lastAni->setTargetObject(m_current);
}

void MainWindow::updateModule(const int index)
{
    m_last = m_current;
    switch (index) {
    case 1:
        m_current = initVideoWidgt();
        break;
    case 2:
        m_current = initDesktopModeModule();
        break;
    case 3:
        m_current = initWMModeModule();
        break;
    case 4:
        m_current = initIconModule();
        break;
    default:
        break;
    }

    m_current->setFixedSize(WINDOW_SIZE);
    m_current->show();

    bindAnimation();

    m_currentAni->setDuration(500);
    m_currentAni->setStartValue(m_last->rect().topLeft());
    m_currentAni->setEndValue(QPoint(m_last->x() - m_last->width(), 0));

    m_lastAni->setDuration(500);
    m_lastAni->setStartValue(QPoint(m_last->rect().topRight()));
    m_lastAni->setEndValue(QPoint(0, 0));
}

void MainWindow::animationHandle()
{
    m_last->deleteLater();
}

BaseModuleWidget *MainWindow::initVideoWidgt()
{
    BaseModuleWidget* w = new BaseModuleWidget(new VideoWidget, m_fakerWidget);
    return w;
}

BaseModuleWidget *MainWindow::initDesktopModeModule()
{
    BaseModuleWidget* w = new BaseModuleWidget(new DesktopModeModule, m_fakerWidget);
    w->setTitle(tr("Please select desktop mode"));
    w->setDescribe(tr("You can switch it in Mode by right clicking on dock"));
    return w;
}

BaseModuleWidget *MainWindow::initWMModeModule()
{
    BaseModuleWidget* w = new BaseModuleWidget(new WMModeModule, m_fakerWidget);
    return w;
}

BaseModuleWidget *MainWindow::initIconModule()
{
    BaseModuleWidget* w = new BaseModuleWidget(new IconModule, m_fakerWidget);
    w->setTitle(tr("Please select icon theme"));
    w->setDescribe(tr("You can change it in Control Center > Personalization > Theme > Icon Theme"));
    return w;
}
