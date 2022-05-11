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

#ifndef SUPPORT_H
#define SUPPORT_H

#include <QScrollArea>
#include <DGuiApplicationHelper>
#include <DLabel>
#include <DFrame>

DGUI_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

class Support : public QScrollArea
{
    Q_OBJECT
public:
    explicit Support(QWidget *parent = nullptr);

signals:

public slots:
//    void initTheme(int type);
private:
    DLabel *m_label;
    QString m_text;
};

#endif // SUPPORT_H
