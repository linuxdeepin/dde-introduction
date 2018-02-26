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

#ifndef WMMODEMODULE_H
#define WMMODEMODULE_H

#include "../widgets/basewidget.h"
#include "../model.h"
#include "../worker.h"

#include <QFrame>
#include <QHBoxLayout>

class WMModeModule : public QFrame
{
    Q_OBJECT
public:
    explicit WMModeModule(QWidget *parent = nullptr);

private Q_SLOTS:
    void onWMModeChanged(Model::WMType type);

private:
    QHBoxLayout* m_layout;
    Model* m_model;
    Worker* m_worker;
    BaseWidget* m_efficientWidget;
    BaseWidget* m_fashionWidget;
};

#endif // WMMODEMODULE_H
