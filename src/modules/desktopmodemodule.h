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

#ifndef DESKTOPMODEMODULE_H
#define DESKTOPMODEMODULE_H

#include "../model.h"
#include "../widgets/basewidget.h"
#include "../worker.h"
#include "moduleinterface.h"

#include <QHBoxLayout>
#include <QKeyEvent>

class DesktopModeModule : public ModuleInterface
{
    Q_OBJECT
public:
    explicit DesktopModeModule(QWidget* parent = nullptr);

    void updateBigIcon() Q_DECL_OVERRIDE;
    void updateSmallIcon() Q_DECL_OVERRIDE;
    void updateSelectBtnPos() Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent*) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

    void setFirst(bool first);
    void updateInterface(float);

private slots:
    void onDesktopTypeChanged(Model::DesktopMode mode);

private:
    QHBoxLayout* m_layout;
    BaseWidget* m_efficientWidget;
    BaseWidget* m_fashionWidget;
    QSize m_size;
    bool isfirst;
};

#endif  // DESKTOPMODEMODULE_H
