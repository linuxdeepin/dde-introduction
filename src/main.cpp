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
#include "normalwindow.h"
#include <DApplication>
#include <QDebug>
#include <DWidgetUtil>
#include <DPlatformWindowHandle>

#ifndef DISABLE_VIDEO
#include <compositing_manager.h>
#endif

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
#ifndef DISABLE_VIDEO
    qputenv("DXCB_FAKE_PLATFORM_NAME_XCB", "TRUE");
#endif

    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setApplicationName("dde-introduction");

    // dapplication default setting is true
    a.setAttribute(Qt::AA_ForceRasterWidgets, false);

    if (!a.setSingleInstance(a.applicationName(), DApplication::UserScope)) {
        qWarning() << QString("There is a %1 running!!").arg(a.applicationName());
        return -1;
    }

    a.setOrganizationName("deepin");
    a.setApplicationVersion(DApplication::buildVersion("1.0"));
    a.loadTranslator();

    static const QDate buildDate = QLocale( QLocale::English ).toDate( QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");
    QString t_date = buildDate.toString("MMdd");
    // Version Time
    a.setApplicationVersion(DApplication::buildVersion(t_date));


#ifndef DISABLE_VIDEO
    setlocale(LC_NUMERIC, "C");

    // 强制不使用嵌入mpv窗口的模式
    dmr::CompositingManager::get().overrideCompositeMode(true);
#endif

    MainWindow w;

    DPlatformWindowHandle::enableDXcbForWindow(&w, true);

    w.show();
    moveToCenter(&w);

    return a.exec();
}
