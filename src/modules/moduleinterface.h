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

#ifndef MODULEINTERFACE_H
#define MODULEINTERFACE_H

#include "../model.h"
#include "../worker.h"
#include "../widgets/iconbutton.h"

#include <dimagebutton.h>
#include <QFrame>
#include <DFrame>
#include <DLabel>
#include <DHiDPIHelper>
#include <DFloatingButton>

DWIDGET_USE_NAMESPACE

//视频、轮播图、桌面样式、运行模式、图标主题的基类
class ModuleInterface : public DFrame
{
    Q_OBJECT
public:
    explicit ModuleInterface(QWidget *parent = nullptr);

    virtual void updateBigIcon(){};
    virtual void updateSmallIcon() {};
    virtual void updateSelectBtnPos() {};

    //根据图标的大小，更新图标，首次启动的图标大，日常启动的图标小
    void setIconType(Model::IconType type);

    //调整大小事件，大小变化启动更新选择按钮定时器
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

protected:
    Model  *m_model;
    Worker *m_worker;
    IconButton *m_selectBtn;
    //更新选择按钮的定时器
    QTimer *m_updateSelectBtnTimer;
};

#endif // MODULEINTERFACE_H
