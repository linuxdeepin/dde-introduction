/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     xiepengfei <xiepengfei@uniontech.com>
*
* Maintainer: xiepengfei <xiepengfei@uniontech.com>
*
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

#ifndef BOTTOMNAVIGATION_H
#define BOTTOMNAVIGATION_H


#include "bottombutton.h"

#include <QDesktopServices>
#include <QEvent>
#include <QHBoxLayout>
#include <QProcess>
#include <QUrl>
#include <QMap>

#include <DWidget>

#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

//不是用的类，可以删除，现在使用NavigationBottom
class BottomNavigation : public DWidget
{
    Q_OBJECT
public:
    explicit BottomNavigation(DWidget *parent = nullptr);

private slots:
    void onButtonClicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QMap<DWidget*, QString> m_buttons;
};

#endif // BOTTOMNAVIGATION_H
