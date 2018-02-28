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

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setApplicationName("dde-introduction");

    if (!a.setSingleInstance(a.applicationName(), DApplication::UserScope)) {
        qWarning() << QString("There is a %1 running!!").arg(a.applicationName());
        return -1;
    }

    a.setOrganizationName("deepin");
    a.setApplicationVersion(DApplication::buildVersion("1.0"));
    a.loadTranslator();

    MainWindow w;
    w.moveToCenter();
    w.exec();

    NormalWindow n;
    n.setFixedWidth(750);
    n.exec();

    return 0;
}
