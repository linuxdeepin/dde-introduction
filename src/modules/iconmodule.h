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
#include <QGridLayout>
#include <dflowlayout.h>
#include <QScrollArea>

DWIDGET_USE_NAMESPACE

class IconModule : public ModuleInterface
{
    Q_OBJECT
public:
    explicit IconModule(QWidget *parent = nullptr);

    void updateBigIcon() Q_DECL_OVERRIDE;
    void updateSmallIcon() Q_DECL_OVERRIDE;
    void updateSelectBtnPos() Q_DECL_OVERRIDE;

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void addIcon(const IconStruct &icon);
    void removeIcon(const IconStruct &icon);
    void currentIconChanged(const IconStruct &icon);

private:
    QScrollArea *m_scroll;
    QWidget *m_scrollWidget;
    DFlowLayout* m_layout;
    QMap<IconStruct, BaseWidget*> m_iconList;
};

#endif // ICONMODULE_H
