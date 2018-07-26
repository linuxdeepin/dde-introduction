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

#include <dimagebutton.h>
#include <QFrame>

DWIDGET_USE_NAMESPACE

class ModuleInterface : public QFrame
{
    Q_OBJECT
public:
    explicit ModuleInterface(QWidget *parent = nullptr);

    void setIconType(Model::IconType type);

    virtual void updateBigIcon() = 0;
    virtual void updateSmallIcon() = 0;

    virtual void updateSelectBtnPos() = 0;

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

protected:
    Model  *m_model;
    Worker *m_worker;
    QLabel* m_selectBtn;
    QTimer *m_updateSelectBtnTimer;
};

#endif // MODULEINTERFACE_H
