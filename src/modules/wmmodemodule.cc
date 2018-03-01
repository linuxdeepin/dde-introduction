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
    m_efficientWidget->setTitle(tr("Efficient Mode"));
    m_fashionWidget->setTitle(tr("Fashion Mode"));

    connect(m_model, &Model::wmTypeChanged, this, &WMModeModule::onWMModeChanged);
    connect(m_fashionWidget, &BaseWidget::clicked, this, [=] {
        m_worker->setWMMode(Model::WM_3D);
    });
    connect(m_efficientWidget, &BaseWidget::clicked, this, [=] {
        m_worker->setWMMode(Model::WM_2D);
    });

    QTimer::singleShot(100, this, [=] {
        onWMModeChanged(m_model->wmType());
    });

    m_layout->setContentsMargins(10, 8, 10, 0);

    m_layout->addWidget(m_efficientWidget);
    m_layout->addWidget(m_fashionWidget);

    setLayout(m_layout);
}

void WMModeModule::updateBigIcon()
{
    m_efficientWidget->setPixmap(":/resources/2d_big.png");
    m_fashionWidget->setPixmap(":/resources/3d_big.png");
}

void WMModeModule::updateSmaillIcon()
{
    m_efficientWidget->setPixmap(":/resources/2d_small.png");
    m_fashionWidget->setPixmap(":/resources/3d_small.png");
}

void WMModeModule::onWMModeChanged(Model::WMType type)
{
    m_selectBtn->raise();

    switch (type) {
    case Model::WM_2D:
        m_selectBtn->move(m_efficientWidget->mapTo(this, m_efficientWidget->rect().topRight()) - QPoint(8, 8));
        break;
    case Model::WM_3D:
        m_selectBtn->move(m_fashionWidget->mapTo(this, m_fashionWidget->rect().topRight()) - QPoint(8, 8));
        break;
    default:
        break;
    }
}
