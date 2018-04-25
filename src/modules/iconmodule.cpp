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
    , m_scroll(new QScrollArea)
    , m_layout(new DFlowLayout)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_scroll, 0, Qt::AlignCenter);
    setLayout(layout);

    m_scrollWidget = new QWidget;
    m_scrollWidget->setLayout(m_layout);

    m_layout->setSpacing(0);
    m_layout->setMargin(0);
    m_layout->setContentsMargins(15, 8, 20, -10);

    m_selectBtn->setParent(m_scrollWidget);

    m_scroll->setWidget(m_scrollWidget);
    m_scroll->setWidgetResizable(true);
    m_scroll->setFocusPolicy(Qt::NoFocus);
    m_scroll->setFrameStyle(QFrame::NoFrame);
    m_scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_scroll->setContentsMargins(0, 0, 0, 0);
    m_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(m_model, &Model::iconAdded, this, &IconModule::addIcon);
    connect(m_model, &Model::iconRemoved, this, &IconModule::removeIcon);
    connect(m_model, &Model::iconChanged, this, &IconModule::currentIconChanged);

    for (const IconStruct &icon : m_model->iconList()) {
        addIcon(icon);
    }

    QTimer::singleShot(100, this, [=] {
        currentIconChanged(m_model->currentIcon());
    });

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
    m_selectBtn->move(w->mapTo(m_scrollWidget, m_iconList[icon]->rect().topRight())  - QPoint(8, 8));

    for (BaseWidget *base : m_iconList.values()) {
        base->setChecked(base == w);
    }
}

void IconModule::updateBigIcon()
{
    const QSize size(700, 330);
    setFixedSize(size);
    m_scroll->setFixedSize(size);
    m_scrollWidget->setFixedWidth(size.width());

    QMapIterator<IconStruct, BaseWidget*>map(m_iconList);

    while (map.hasNext()) {
        map.next();
        QPixmap pixmap(map.key().Pixmap);
        pixmap = pixmap.scaled(QSize(320, 70) * devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        map.value()->setPixmap(pixmap);
    }
}

void IconModule::updateSmallIcon()
{
    const QSize size(580, 330);
    setFixedSize(size);
    m_scroll->setFixedSize(size);
    m_scrollWidget->setFixedWidth(size.width());

    QMapIterator<IconStruct, BaseWidget*>map(m_iconList);

    while (map.hasNext()) {
        map.next();
        QPixmap pixmap(map.key().Pixmap);
        pixmap = pixmap.scaled(QSize(260, 52) * devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
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
