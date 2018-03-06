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

#include "normalwindow.h"
#include "modules/desktopmodemodule.h"
#include "modules/wmmodemodule.h"
#include "modules/iconmodule.h"
#include "basemodulewidget.h"

static QWidget *createDesktopModeHandle(QObject *opt) {
    Q_UNUSED(opt);

    DesktopModeModule *module = new DesktopModeModule;
    module->updateSmaillIcon();

    return new BaseModuleWidget(module);
}

static QWidget *createWMModeHandle(QObject *opt) {
    Q_UNUSED(opt);

    WMModeModule *module = new WMModeModule;
    module->updateSmaillIcon();

    return new BaseModuleWidget(module);
}

static QWidget *createIconHandle(QObject *opt) {
    Q_UNUSED(opt);

    return new BaseModuleWidget(new IconModule);
}

NormalWindow::NormalWindow(QWidget *parent)
    : DDialog(parent),
      m_mainLayout(new QVBoxLayout),
      m_navigationBar(new NavigationBar)
{
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(m_mainLayout);
    centralWidget->setFixedSize(700, 450);

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(m_navigationBar);
    contentLayout->addStretch();

    m_mainLayout->addLayout(contentLayout);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    addContent(centralWidget);
    setContentLayoutContentsMargins(QMargins(0, 0, 0, 0));
}
