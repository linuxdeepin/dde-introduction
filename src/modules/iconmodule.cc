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

#include "iconmodule.h"

IconModule::IconModule(QWidget *parent)
    : QScrollArea(parent)
    , m_layout(new DFlowLayout(this))
    , m_model(Model::Instance())
    , m_worker(Worker::Instance())
{
    connect(m_model, &Model::iconAdded, this, &IconModule::addIcon);
    connect(m_model, &Model::iconRemoved, this, &IconModule::removeIcon);
    connect(m_model, &Model::iconChanged, this, &IconModule::currentIconChanged);

    for (const IconStruct &icon : m_model->iconList()) {
        addIcon(icon);
    }

    currentIconChanged(m_model->currentIcon());

    m_layout->setSpacing(20);
    m_layout->setContentsMargins(20, 0, 10, 0);

    QWidget *content = new QWidget;
    content->setLayout(m_layout);

    setWidget(content);
    setWidgetResizable(true);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setContentsMargins(0, 0, 0, 0);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color:transparent;");

    setFixedSize(700, 350);
}

void IconModule::addIcon(const IconStruct &icon)
{
     if (m_iconList.keys().contains(icon)) {
         return;
     }

     BaseWidget *base = new BaseWidget(this);
     base->setPixmap(icon.Pixmap);

     connect(base, &BaseWidget::clicked, this, [=] {
         m_worker->setIcon(icon);
     });

     m_iconList[icon] = base;

     m_layout->addWidget(base);
}

void IconModule::removeIcon(const IconStruct &icon)
{
    BaseWidget *base = m_iconList[icon];

    m_layout->removeWidget(base);

    m_iconList.remove(icon);

    base->deleteLater();
}

void IconModule::currentIconChanged(const IconStruct &icon)
{
    QMapIterator<IconStruct, BaseWidget*> map(m_iconList);

    while (map.hasNext()) {
        map.value()->setChecked(icon == map.key());
        map.next();
    }
}
