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

#include "worker.h"
#include <QDebug>
Worker *Worker::Instance()
{
    static Worker * instance = new Worker;
    return instance;
}

void Worker::onIconChanged(const QString &value)
{

}

void Worker::onWMChanged(const QString &wm)
{

}

void Worker::onDisplayModeChanged(int mode)
{

}

Worker::Worker(QObject *parent)
    : QObject(parent)
    , m_iconInter(new Icon("com.deepin.daemon.Appearance",
                           "/com/deepin/daemon/Appearance",
                           QDBusConnection::sessionBus(), this))
    , m_wmInter(new WMSwitcher("com.deepin.WMSwitcher",
                               "/com/deepin/WMSwitcher",
                               QDBusConnection::sessionBus(), this))
    , m_dockInter(new Dock("com.deepin.dde.daemon.Dock",
                           "/com/deepin/dde/daemon/Dock",
                           QDBusConnection::sessionBus(), this))
{
    connect(m_iconInter, &Icon::Changed, this, &Worker::onIconChanged);
    connect(m_wmInter, &WMSwitcher::WMChanged, this, &Worker::onWMChanged);
    connect(m_dockInter, &Dock::DisplayModeChanged, this, &Worker::onDisplayModeChanged);

    m_iconInter->setSync(false);
    m_wmInter->setSync(false);
    m_dockInter->setSync(false);

    onIconChanged(m_iconInter->iconTheme());
    onWMChanged(m_wmInter->CurrentWM());
    onDisplayModeChanged(m_dockInter->displayMode());
}
