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
#include "worker.h"
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
#define FIRST_ICONCONTENT_WINSIZE 278

using WMSwitcherInter = com::deepin::WMSwitcher;

class BaseModuleWidget;
class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private slots:
    //上一步按钮响应函数
    void previous();
    //下一步按钮响应函数
    void next();

private:
    //主题变化响应函数
    void slotTheme();
    void initUI();
    void initConnect();
    //绑定需要动画的界面
    void bindAnimation();
    //根据index值进行欢迎四个界面的创建,并进行动画绑定
    void updateModule(const int index);
    //动画结束后删除m_last保存的界面
    void animationHandle();

    BaseModuleWidget *initDesktopModeModule();
    BaseModuleWidget *initWMModeModule();
    BaseModuleWidget *initIconModule();

    //记录当前所属于界面
    int m_index;
    //CloseButton *m_closeFrame;
    //下一步按钮
    NextButton *m_nextBtn {nullptr};
    //上一步按钮
    DIconButton *m_previousBtn {nullptr};
    //完成按钮
    NextButton *m_doneBtn {nullptr};
    //关闭按钮
    DIconButton *m_pCloseBtn {nullptr};
    //第一个页面widget放置动画或者轮播图
    DWidget *m_current;
    DWidget *m_last;
    //上一步和下一步选择的界面的动画
    QPropertyAnimation *m_currentAni;
    //当前还没变化的界面的动画
    QPropertyAnimation *m_lastAni;
    DWidget *m_fakerWidget;
    QSettings *m_settings;
    WMSwitcherInter *m_displayInter;
    //是否使用视频的标志
    bool m_useVideo;
    bool m_isFirst;
    //标志是否是可以窗口特效的版本
    bool m_supportWM;
};

#endif // MAINWINDOW_H
