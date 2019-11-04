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
    m_efficientWidget->setTitle(tr("Extreme speed mode"));
    m_fashionWidget->setTitle(tr("Gorgeous mode"));

    connect(m_model, &Model::wmTypeChanged, this, &WMModeModule::onWMModeChanged);
    connect(m_fashionWidget, &BaseWidget::clicked, this, [=] {
        m_worker->setWMMode(Model::WM_3D);
    });
    connect(m_efficientWidget, &BaseWidget::clicked, this, [=] {
        m_worker->setWMMode(Model::WM_2D);
    });

    connect(m_efficientWidget, &BaseWidget::sizeChanged, this, &WMModeModule::updateSelectBtnPos);

    QTimer::singleShot(100, this, [=] {
        onWMModeChanged(m_model->wmType());
    });

    m_layout->setContentsMargins(0, 30, 0, 65);

    m_layout->addWidget(m_fashionWidget);
    m_layout->addWidget(m_efficientWidget);

    setLayout(m_layout);

    updateSmallIcon();
}

void WMModeModule::updateBigIcon()
{
    m_efficientWidget->setBigPixmap(":/resources/2d_big@3x.png");
    m_fashionWidget->setBigPixmap(":/resources/3d_big@3x.png");
    m_layout->setContentsMargins(10, 70, 10, 35);
}

void WMModeModule::updateSmallIcon()
{
    m_efficientWidget->setSmallPixmap(":/resources/2d_small@3x.png");
    m_fashionWidget->setSmallPixmap(":/resources/3d_small@3x.png");
}

void WMModeModule::updateSelectBtnPos()
{
    onWMModeChanged(m_model->wmType());
}

void WMModeModule::onWMModeChanged(Model::WMType type)
{
    m_selectBtn->raise();

    QPoint p(8,8);
    if (!m_first)
        p.setY(-18);
    switch (type) {
    case Model::WM_2D:
        m_selectBtn->move(m_efficientWidget->mapTo(this, m_efficientWidget->rect().topRight()) - p);
        m_efficientWidget->setChecked(true);
        m_fashionWidget->setChecked(false);
        break;
    case Model::WM_3D:
        m_selectBtn->move(m_fashionWidget->mapTo(this, m_fashionWidget->rect().topRight()) - p);
        m_fashionWidget->setChecked(true);
        m_efficientWidget->setChecked(false);
        break;
    default:
        break;
    }
}
void WMModeModule::setFirst(bool first)
{
    m_first = first;
}
