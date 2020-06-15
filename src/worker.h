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

#include "model.h"

#include <QObject>
#include <QJsonDocument>
#include <QProcess>

#include <com_deepin_daemon_appearance.h>
#include <com_deepin_wmswitcher.h>
#include <com_deepin_dde_daemon_dock.h>
#include <DWindowManagerHelper>

using Icon       = com::deepin::daemon::Appearance;
using WMSwitcher = com::deepin::WMSwitcher;
using Dock       = com::deepin::dde::daemon::Dock;

DGUI_USE_NAMESPACE
class Worker : public QObject
{
    Q_OBJECT

public:
    static Worker* Instance();

public slots:
    void setDesktopMode(Model::DesktopMode mode);
    void setWMMode(Model::WMType type);
    void setIcon(const IconStruct &icon);

private slots:
    void onWMChanged(const QString &wm);
    void onWMChang(/*const quint32 &wm*/);
    void onDisplayModeChanged(int mode);
    void onIconRefreshed(const QString &name);
    void onIconListChanged(const QString & value);
    void onIconPixmapFinished(QDBusPendingCallWatcher *w);

private:
    explicit Worker(QObject *parent = nullptr);

private:
    Model*      m_model;
    Icon*       m_iconInter;
    WMSwitcher* m_wmInter;
    Dock*       m_dockInter;
    DWindowManagerHelper* m_windowManage;
};

#endif // WORKER_H
