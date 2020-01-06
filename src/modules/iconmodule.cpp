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
    QVBoxLayout *widgetLayout = new QVBoxLayout;
    m_scrollWidget->setLayout(widgetLayout);

    m_scrollWidget->installEventFilter(this);

    widgetLayout->setContentsMargins(0, 30, 0, 25);
    widgetLayout->setMargin(0);
    widgetLayout->setSpacing(0);
    widgetLayout->addStretch();
    widgetLayout->addLayout(m_layout);
    widgetLayout->addStretch();

    m_layout->setSpacing(10);
    m_layout->setMargin(0);
    m_layout->setContentsMargins(10, 3, 0, 15);
    m_layout->setVerticalSpacing(35);

    m_selectBtn->setParent(m_scrollWidget);

    m_scroll->setWidget(m_scrollWidget);
    m_scroll->setWidgetResizable(true);
    m_scroll->setFocusPolicy(Qt::NoFocus);
    m_scroll->setFrameStyle(DFrame::NoFrame);
    m_scroll->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_scroll->setContentsMargins(0, 0, 0, 0);
    m_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(m_model, &Model::iconAdded, this, &IconModule::addIcon);
    connect(m_model, &Model::iconRemoved, this, &IconModule::removeIcon);
    connect(m_model, &Model::iconChanged, this, &IconModule::currentIconChanged);

    for (const IconStruct &icon : m_model->iconList()) {
        addIcon(icon);
    }

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

     m_layout->insertWidget(m_model->iconList().indexOf(icon), base);
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
    QPoint p = w->mapTo(m_scrollWidget, m_iconList[icon]->rect().topRight())  - QPoint(9, 3);
    m_scroll->ensureVisible(p.x(), p.y() + m_height, 50, m_height);
    m_selectBtn->move(w->mapTo(m_scrollWidget, m_iconList[icon]->rect().topRight())  - QPoint(9, 3));

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
    m_layout->setContentsMargins(10, 43, 0, 15);
    updateSelectBtnPos();

    QMapIterator<IconStruct, BaseWidget*>map(m_iconList);

    while (map.hasNext()) {
        map.next();
        QPixmap pixmap(map.key().Pixmap);
        pixmap = pixmap.scaled(QSize(320, 70) * devicePixelRatioF(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        map.value()->setPixmap(pixmap);
    }
    m_height = 70;
}

void IconModule::updateSmallIcon()
{
    const QSize size(580, 250);
    setFixedSize(size);
    m_scroll->setFixedSize(size);
    m_scrollWidget->setFixedWidth(size.width());
    updateSelectBtnPos();

    QMapIterator<IconStruct, BaseWidget*>map(m_iconList);

    while (map.hasNext()) {
        map.next();
        QPixmap pixmap(map.key().Pixmap);
        pixmap = pixmap.scaled(QSize(240, 60) * devicePixelRatioF(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        map.value()->setPixmap(pixmap);
        map.value()->setLayoutSpacing(10);
    }
    m_height = 60;
}

void IconModule::updateSelectBtnPos()
{
    currentIconChanged(m_model->currentIcon());
}

void IconModule::keyPressEvent(QKeyEvent *e)
{
    IconStruct icon = m_model->currentIcon();
    int index = -1;
    for (int i = 0; i < m_model->iconList().size(); ++i) {
        if (m_model->iconList().at(i) == icon) {
            index = i;
            break;
        }
    }
    if (e->key() == Qt::Key_Left) {
        if (index == 0)
            return;
        m_worker->setIcon(m_model->iconList().at(index - 1));
    } else if (e->key() == Qt::Key_Right) {
        if (index == m_model->iconList().size() - 1)
            return;
        m_worker->setIcon(m_model->iconList().at(index + 1));
    } else if (e->key() == Qt::Key_Up) {
        if (index < 2)
            return;
        m_worker->setIcon(m_model->iconList().at(index - 2));
    } else if (e->key() == Qt::Key_Down) {
        if (index > m_model->iconList().size() - 3)
            return;
        m_worker->setIcon(m_model->iconList().at(index + 2));
    }
    updateSelectBtnPos();
}

bool IconModule::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_scrollWidget && event->type() == QEvent::Resize) {
        m_updateSelectBtnTimer->start();
    }

    return ModuleInterface::eventFilter(watched, event);
}
