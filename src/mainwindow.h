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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basemodulewidget.h"
#include "modules/desktopmodemodule.h"
#include "modules/iconmodule.h"
#include "modules/normalmodule.h"
#include "modules/photoslide.h"
#include "modules/wmmodemodule.h"
#include "widgets/nextbutton.h"
#include "widgets/closebutton.h"
#include "widgets/previousbutton.h"
#ifndef DISABLE_VIDEO
#include "modules/videowidget.h"
#endif

#include <QPropertyAnimation>
#include <QPushButton>
#include <QSettings>
#include <QWidget>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QHBoxLayout>

#include <DMainWindow>
#include <DIconButton>
#include <DImageButton>
#include <DWidget>
#include <DGuiApplicationHelper>
#include <DPalette>
#include <DPlatformWindowHandle>
#include <DSysInfo>
#include <DTitlebar>

#include <com_deepin_wmswitcher.h>

DCORE_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

#define DDE_STARTGUIDE_PATH "/usr/bin/dde-startguide"

using WMSwitcherInter = com::deepin::WMSwitcher;

class BaseModuleWidget;
class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(DWidget *parent = nullptr);
    ~MainWindow() override;
    void initWindowWidget();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
//    void QWheelEvent(const QPoint& pos, int delta, Qt::MouseButtons buttons,
//                       Qt::KeyboardModifiers modifiers, Qt::Orientation orient = Qt::Vertical);

private slots:
    void previous();
    void next();

private:
    void slotTheme();
    void initUI();
    void initConnect();
    void bindAnimation();
    void updateModule(const int index);
    void animationHandle();

    BaseModuleWidget *initDesktopModeModule();
    BaseModuleWidget *initWMModeModule();
    BaseModuleWidget *initIconModule();

private:
    int m_index;
    CloseButton *m_closeFrame;
    NextButton *m_nextBtn;
    DIconButton *m_previousBtn;
    NextButton *m_doneBtn;
    DWidget *m_current;
    DWidget *m_last;
    QPropertyAnimation *m_currentAni;
    QPropertyAnimation *m_lastAni;
    DWidget *m_fakerWidget;
    QSettings *m_settings;
    WMSwitcherInter *m_displayInter;
    bool isx86;
    bool m_isFirst;
    bool m_supportWM;
};

#endif // MAINWINDOW_H
