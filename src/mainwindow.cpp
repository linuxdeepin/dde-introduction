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

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : DDialog(parent)
    , m_index(1)
    , m_current(nullptr)
    , m_last(nullptr)
    , m_currentAni(new QPropertyAnimation(this))
    , m_lastAni(new QPropertyAnimation(this))
{
    m_current = new VideoWidget(this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::previous()
{
    updateModule(--m_index);
}

void MainWindow::next()
{
    // create new QWidget, change pointer
    updateModule(++m_index);

    // update animation direction
}

void MainWindow::initUI()
{
    m_previousBtn = new DImageButton;
    m_nextBtn     = new QPushButton;
}

void MainWindow::initConnect()
{
    connect(m_previousBtn, &DImageButton::clicked, this, &MainWindow::previous);
    connect(m_nextBtn, &QPushButton::clicked, this, &MainWindow::next);
}

void MainWindow::bindAnimation()
{
    m_currentAni->setTargetObject(m_current);
    m_lastAni->setTargetObject(m_last);
}

void MainWindow::updateModule(const int index)
{
    m_last = m_current;
    switch (index) {
    case 1:
        m_current = new VideoWidget(this);
        break;
    default:
        break;
    }

    bindAnimation();
}
