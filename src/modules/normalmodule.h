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

#ifndef NORMALMODULE_H
#define NORMALMODULE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QMap>

class NormalModule : public QWidget
{
    Q_OBJECT
public:
    explicit NormalModule(QWidget *parent = nullptr);


private:
    void updateCurrentWidget(const int index);

private:
    QVBoxLayout *m_leftNavigationLayout;
    QVBoxLayout *m_rightContentLayout;
    QButtonGroup *m_buttonGrp;
    QMap<QWidget*, int> m_buttonMap;
    QMap<QAbstractButton*, QString> m_titleMap;
    QWidget *m_currentWidget;
};

#endif // NORMALMODULE_H
