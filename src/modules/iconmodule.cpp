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

#include <QImageReader>

IconModule::IconModule(QWidget *parent)
    : ModuleInterface(parent)
    , m_layout(new DFlowLayout(this))
{
    connect(m_model, &Model::iconAdded, this, &IconModule::addIcon);
    connect(m_model, &Model::iconRemoved, this, &IconModule::removeIcon);
    connect(m_model, &Model::iconChanged, this, &IconModule::currentIconChanged);

    for (const IconStruct &icon : m_model->iconList()) {
        addIcon(icon);
    }

    QTimer::singleShot(100, this, [=] {
        currentIconChanged(m_model->currentIcon());
    });

    m_layout->setSpacing(20);
    m_layout->setContentsMargins(15, 8, 10, 0);

    setLayout(m_layout);

    updateSmallIcon();
}

void IconModule::addIcon(const IconStruct &icon)
{
     if (m_iconList.keys().contains(icon) && icon.Id.isEmpty()) {
         return;
     }

     BaseWidget *base = new BaseWidget(this);

     QPixmap pixmap(icon.Pixmap);
     pixmap.setDevicePixelRatio(devicePixelRatioF());

     base->setPixmap(pixmap);
     base->setTitle(icon.Id);

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
    if (icon.Id.isEmpty()) {
        return;
    }

    m_selectBtn->raise();

    BaseWidget * w = m_iconList[icon];
    m_selectBtn->move(w->mapTo(this, m_iconList[icon]->rect().topRight())  - QPoint(8, 8));

    for (BaseWidget *base : m_iconList.values()) {
        base->setChecked(base == w);
    }
}

void IconModule::updateBigIcon()
{
    setFixedWidth(700);

    QMapIterator<IconStruct, BaseWidget*>map(m_iconList);

    while (map.hasNext()) {
        map.next();
        QPixmap pixmap(map.key().Pixmap);
        map.value()->setPixmap(pixmap);
    }
}

void IconModule::updateSmallIcon()
{
    setFixedWidth(580);

    QMapIterator<IconStruct, BaseWidget*>map(m_iconList);

    while (map.hasNext()) {
        map.next();
        QPixmap pixmap(map.key().Pixmap);
        pixmap = pixmap.scaled(240, 52, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        map.value()->setPixmap(pixmap);
    }
}

void IconModule::resizeEvent(QResizeEvent *event)
{
    ModuleInterface::resizeEvent(event);

    QTimer::singleShot(1, this, [=] {
        currentIconChanged(m_model->currentIcon());
    });
}
