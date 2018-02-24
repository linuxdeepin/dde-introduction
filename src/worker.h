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

#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <com_deepin_daemon_appearance.h>
#include <com_deepin_wmswitcher.h>
#include <com_deepin_dde_daemon_dock.h>

using Icon       = com::deepin::daemon::Appearance;
using WMSwitcher = com::deepin::WMSwitcher;
using Dock       = com::deepin::dde::daemon::Dock;

class Worker : public QObject
{
    Q_OBJECT

public:
    static Worker* Instance();

private Q_SLOTS:
    void onIconChanged(const QString & value);
    void onWMChanged(const QString &wm);
    void onDisplayModeChanged(int mode);

private:
    explicit Worker(QObject *parent = nullptr);

private:
    Icon*       m_iconInter;
    WMSwitcher* m_wmInter;
    Dock*       m_dockInter;
};

#endif // WORKER_H
