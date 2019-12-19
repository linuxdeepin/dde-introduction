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
#include <DWidget>
#include <DLog>
#include <QDBusInterface>
#include <DWindowManagerHelper>
#include <DGuiApplicationHelper>

#ifndef DISABLE_VIDEO
#include <compositing_manager.h>
#endif

DWIDGET_USE_NAMESPACE

static QString g_appPath;//全局路径

//获取配置文件主题类型，并重新设置
DGuiApplicationHelper::ColorType getThemeTypeSetting()
{
    //需要找到自己程序的配置文件路径，并读取配置，这里只是用home路径下themeType.cfg文件举例,具体配置文件根据自身项目情况
    QString t_appDir = g_appPath + QDir::separator() + "themetype.cfg";
    QFile t_configFile(t_appDir);

    t_configFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t_readBuf = t_configFile.readAll();
    int t_readType = QString(t_readBuf).toInt();

    //获取读到的主题类型，并返回设置
    switch (t_readType) {
    case 0:
        // 跟随系统主题
        return DGuiApplicationHelper::UnknownType;
    case 1:
//        浅色主题
        return DGuiApplicationHelper::LightType;

    case 2:
//        深色主题
        return DGuiApplicationHelper::DarkType;
    default:
        // 跟随系统主题
        return DGuiApplicationHelper::UnknownType;
    }

}

//保存当前主题类型配置文件
void saveThemeTypeSetting(int type)
{
    //需要找到自己程序的配置文件路径，并写入配置，这里只是用home路径下themeType.cfg文件举例,具体配置文件根据自身项目情况
    QString t_appDir = g_appPath + QDir::separator() + "themetype.cfg";
    QFile t_configFile(t_appDir);

    t_configFile.open(QIODevice::WriteOnly | QIODevice::Text);
    //直接将主题类型保存到配置文件，具体配置key-value组合根据自身项目情况
    QString t_typeStr = QString::number(type);
    t_configFile.write(t_typeStr.toUtf8());
    t_configFile.close();
}

int main(int argc, char *argv[])
{
    bool isx86 = QSysInfo::currentCpuArchitecture().startsWith("x86");
//#ifndef DISABLE_VIDEO
    if (isx86)
        qputenv("DXCB_FAKE_PLATFORM_NAME_XCB", "TRUE");
//#endif

    //QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    g_appPath = QDir::homePath() + QDir::separator() + "." + qApp->applicationName();
    QDir t_appDir;
    t_appDir.mkpath(g_appPath);

    a.setApplicationName("dde-introduction");

    // dapplication default setting is true
    a.setAttribute(Qt::AA_ForceRasterWidgets, false);

    if (!a.setSingleInstance(a.applicationName(), DApplication::UserScope)) {
        qWarning() << QString("There is a %1 running!!").arg(a.applicationName());
        return -1;
    }

    a.setAutoActivateWindows(true);
    a.setOrganizationName("deepin");
    a.setApplicationVersion(DApplication::buildVersion("1.0"));
    a.loadTranslator();
    a.setApplicationDisplayName(QObject::tr("Welcome"));

    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.registerService("com.deepin.introduction");
    using namespace Dtk::Core;
    Dtk::Core::DLogManager::registerConsoleAppender();
    Dtk::Core::DLogManager::registerFileAppender();
    QCommandLineParser cmdParser;
    cmdParser.setApplicationDescription("dde-introduction");
    cmdParser.addHelpOption();
    cmdParser.addVersionOption();
    cmdParser.process(a);

    // 应用已保存的主题设置
    DGuiApplicationHelper::instance()->setPaletteType(getThemeTypeSetting());
    saveThemeTypeSetting(0);

    //监听当前应用主题切换事件
    QObject::connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::paletteTypeChanged,
    [] (DGuiApplicationHelper::ColorType type) {
        qDebug() << type;
        // 保存程序的主题设置  type : 0,系统主题， 1,浅色主题， 2,深色主题
        saveThemeTypeSetting(0);
        DGuiApplicationHelper::instance()->setPaletteType(type);
    });

    static const QDate buildDate = QLocale( QLocale::English ).toDate( QString(__DATE__).replace("  ", " 0"), "MMM dd yyyy");
    QString t_date = buildDate.toString("MMdd");
    // Version Time
    a.setApplicationVersion(DApplication::buildVersion(t_date));




    MainWindow w;
    DPlatformWindowHandle::enableDXcbForWindow(&w, true);
    dbus.registerObject("/com/deepin/introduction", &w, QDBusConnection::ExportScriptableSlots);

    w.show();
    moveToCenter(&w);

    return a.exec();
}
