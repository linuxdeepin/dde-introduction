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

#include "desktopmodemodule.h"

DesktopModeModule::DesktopModeModule(QWidget *parent)
    : ModuleInterface(parent)
    , m_layout(new QHBoxLayout(this))
    , m_efficientWidget(new BaseWidget(this))
    , m_fashionWidget(new BaseWidget(this))
{
    m_efficientWidget->setTitle(tr("Efficient Mode"));
    m_fashionWidget->setTitle(tr("Fashion Mode"));

    connect(m_model, &Model::desktopModeChanged, this, &DesktopModeModule::onDesktopTypeChanged);
    connect(m_fashionWidget, &BaseWidget::clicked, this, [=] {
        m_worker->setDesktopMode(Model::FashionMode);
    });
    connect(m_efficientWidget, &BaseWidget::clicked, this, [=] {
        m_worker->setDesktopMode(Model::EfficientMode);
    });

    onDesktopTypeChanged(m_model->desktopMode());

    m_layout->addWidget(m_efficientWidget);
    m_layout->addWidget(m_fashionWidget);

    setLayout(m_layout);
}

void DesktopModeModule::onDesktopTypeChanged(Model::DesktopMode mode)
{
    m_fashionWidget->setChecked(false);
    m_efficientWidget->setChecked(false);

    switch (mode) {
    case Model::EfficientMode:
        m_efficientWidget->setChecked(true);
        break;
    case Model::FashionMode:
        m_efficientWidget->setChecked(true);
        break;
    default:
        break;
    }
}

void DesktopModeModule::updateBigIcon()
{
    m_efficientWidget->setPixmap(":/resources/effective_mode_big.png");
    m_fashionWidget->setPixmap(":/resources/fashion_mode_big.png");
}

void DesktopModeModule::updateSmaillIcon()
{
    m_efficientWidget->setPixmap(":/resources/effective_mode_small.png");
    m_fashionWidget->setPixmap(":/resources/fashion_mode_small.png");
}


