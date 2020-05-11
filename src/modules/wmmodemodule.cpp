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

#include "wmmodemodule.h"

WMModeModule::WMModeModule(QWidget *parent)
    : ModuleInterface(parent)
    , m_layout(new QHBoxLayout(this))
    , m_efficientWidget(new BaseWidget(this))
    , m_fashionWidget(new BaseWidget(this))
{
    m_first = true;
    m_efficientWidget->setTitle(tr("Normal Mode"));
    m_fashionWidget->setTitle(tr("Effect Mode"));

    connect(m_model, &Model::wmTypeChanged, this, &WMModeModule::onWMModeChanged);
    connect(m_fashionWidget, &BaseWidget::clicked, this,
            [=] { m_worker->setWMMode(Model::WM_3D); });
    connect(m_efficientWidget, &BaseWidget::clicked, this,
            [=] { m_worker->setWMMode(Model::WM_2D); });

    connect(m_efficientWidget, &BaseWidget::sizeChanged, this, &WMModeModule::updateSelectBtnPos);

    QTimer::singleShot(100, this, [=] { onWMModeChanged(m_model->wmType()); });

    m_layout->setContentsMargins(0, 30, 0, 65);

    m_layout->addWidget(m_fashionWidget);
    m_layout->addWidget(m_efficientWidget);

    setLayout(m_layout);

    updateSmallIcon();
}

void WMModeModule::updateBigIcon()
{
    m_efficientWidget->setBigPixmap(":/resources/2d_big@community.png");
    m_fashionWidget->setBigPixmap(":/resources/3d_big@community.png");
    m_layout->setContentsMargins(10, 70, 10, 35);
}

void WMModeModule::updateSmallIcon()
{
    m_efficientWidget->setSmallPixmap(":/resources/2d_small@community.png");
    m_fashionWidget->setSmallPixmap(":/resources/3d_small@community.png");
}

void WMModeModule::updateSelectBtnPos()
{
    onWMModeChanged(m_model->wmType());
}

void WMModeModule::onWMModeChanged(Model::WMType type)
{
    switch (type) {
        case Model::WM_2D:
            m_efficientWidget->setChecked(true);
            m_fashionWidget->setChecked(false);
            break;
        case Model::WM_3D:
            m_fashionWidget->setChecked(true);
            m_efficientWidget->setChecked(false);
            break;
        default:
            break;
    }
    update();
}

void WMModeModule::setFirst(bool first)
{
    m_first = first;
}

void WMModeModule::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        if (m_model->wmType() == 0)
            m_worker->setWMMode(Model::WM_3D);
    } else if (event->key() == Qt::Key_Right) {
        if (m_model->wmType() == 1)
            m_worker->setWMMode(Model::WM_2D);
    }
}

void WMModeModule::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPoint point;

    int x = m_efficientWidget->m_borderWidget->geometry().x() +
            m_fashionWidget->m_borderWidget->geometry().width();
    int y = m_efficientWidget->m_borderWidget->geometry().y();

    if (m_first) {
        if (m_model->wmType() == Model::WM_2D) {
            point.setX(x * 2 + 4);
            point.setY(y + 66);
        } else if (m_model->wmType() == Model::WM_3D) {
            point.setX(x);
            point.setY(y + 66);
        }
    } else {
        if (m_model->wmType() == Model::WM_2D) {
            point.setX(x * 2 + 22);
            point.setY(y + 26);
        } else if (m_model->wmType() == Model::WM_3D) {
            point.setX(x + 4);
            point.setY(y + 26);
        }
    }

    m_selectBtn->move(point);
    m_selectBtn->raise();
}
