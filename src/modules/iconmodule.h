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

#ifndef ICONMODULE_H
#define ICONMODULE_H

#include "moduleinterface.h"
#include "../widgets/basewidget.h"
#include "../model.h"
#include "../worker.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QGridLayout>
#include <QKeyEvent>
#include <QImageReader>
#include <QEvent>
#include <QMouseEvent>

#include <DWidget>
#include <dflowlayout.h>

DWIDGET_USE_NAMESPACE

//图标主题类
class IconModule : public ModuleInterface
{
    Q_OBJECT
public:
    explicit IconModule(QWidget *parent = nullptr);

    //首次启动初始化图片
    void updateBigIcon() Q_DECL_OVERRIDE;
    //日常启动初始化图片
    void updateSmallIcon() Q_DECL_OVERRIDE;
    //更新选择按钮位置
    void updateSelectBtnPos() Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent*) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;

signals:
    void cancelCloseFrame();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private slots:
    //拷贝主题图标到当前界面并保存
    void addIcon(const IconStruct &icon);
    //删除图标，删除界面和本地保存
    void removeIcon(const IconStruct &icon);
    //当前界面主题图标变化响应函数
    void currentIconChanged(const IconStruct &icon);

private:
    //滚动条区域
    QScrollArea *m_scroll;
    //显示主题图标界面
    DWidget *m_scrollWidget;
    //显示主题图标的主体
    DFlowLayout* m_layout;
    //保存主题图标
    QMap<IconStruct, BaseWidget*> m_iconList;
    int m_height;
    //没用到
    QWidget *m_Body;
    QPoint m_TempPoint;
    bool m_bIsMispCpuArch {false};

};

#endif // ICONMODULE_H
