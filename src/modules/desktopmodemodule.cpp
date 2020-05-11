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
    isfirst = true;
    m_efficientWidget->setTitle(tr("Efficient Mode"));
    m_fashionWidget->setTitle(tr("Fashion Mode"));

    connect(m_model, &Model::desktopModeChanged, this, &DesktopModeModule::onDesktopTypeChanged);
    connect(m_fashionWidget, &BaseWidget::clicked, this,
            [=] { m_worker->setDesktopMode(Model::FashionMode); });
    connect(m_efficientWidget, &BaseWidget::clicked, this,
            [=] { m_worker->setDesktopMode(Model::EfficientMode); });
    connect(m_efficientWidget, &BaseWidget::sizeChanged, this,
            &DesktopModeModule::updateSelectBtnPos);

    m_layout->setMargin(0);
    m_layout->setSpacing(20);
    m_layout->setContentsMargins(0, 30, 0, 65);

    m_layout->addStretch();
    m_layout->addWidget(m_fashionWidget);
    m_layout->addWidget(m_efficientWidget);
    m_layout->addStretch();

    setLayout(m_layout);

    updateSmallIcon();
}

void DesktopModeModule::onDesktopTypeChanged(Model::DesktopMode mode)
{
    switch (mode) {
        case Model::EfficientMode:
            m_efficientWidget->setChecked(true);
            m_fashionWidget->setChecked(false);
            break;
        case Model::FashionMode:
            m_fashionWidget->setChecked(true);
            m_efficientWidget->setChecked(false);
            break;
        default:
            break;
    }
    update();
}

void DesktopModeModule::updateBigIcon()
{
    m_efficientWidget->setBigPixmap(":/resources/effective_mode_big@community.png");
    m_fashionWidget->setBigPixmap(":/resources/fashion_mode_big@community.png");
    m_layout->setContentsMargins(10, 70, 10, 35);
    m_size = QSize(330, 210);
}

void DesktopModeModule::updateSmallIcon()
{
    QPixmap pixmapeff(":/resources/effective_mode_small@community.png");
    QPixmap pixmapfash(":/resources/fashion_mode_small@community.png");
    m_efficientWidget->setSmallPixmap(pixmapeff);
    m_fashionWidget->setSmallPixmap(pixmapfash);
    m_size = QSize(250, 160);
}

void DesktopModeModule::updateSelectBtnPos()
{
    onDesktopTypeChanged(m_model->desktopMode());
}

void DesktopModeModule::setFirst(bool first)
{
    isfirst = first;
}

void DesktopModeModule::updateInterface(float f)
{
    m_efficientWidget->updateInterface(f);
    m_fashionWidget->updateInterface(f);

    /*switch (m_model->desktopMode()) {
    case Model::EfficientMode:
        m_selectBtn->move(m_efficientWidget->mapTo(this, m_efficientWidget->rect().topRight()) - p);
        break;
    case Model::FashionMode:
        m_selectBtn->move(m_fashionWidget->mapTo(this, m_fashionWidget->rect().topRight()) - p);
        break;
    default:
        break;
    }*/

    update();
}

void DesktopModeModule::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        if (m_model->desktopMode() == 1)
            m_worker->setDesktopMode(Model::FashionMode);
    } else if (event->key() == Qt::Key_Right) {
        if (m_model->desktopMode() == 0)
            m_worker->setDesktopMode(Model::EfficientMode);
    }
}

void DesktopModeModule::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPoint point;

    int x = m_efficientWidget->m_borderWidget->geometry().x() +
            m_fashionWidget->m_borderWidget->geometry().width();
    int y = m_efficientWidget->m_borderWidget->geometry().y();

    if (isfirst) {
        if (m_model->desktopMode() == Model::EfficientMode) {
            point.setX(x * 2 + 17);
            point.setY(y + 66);
        } else if (m_model->desktopMode() == Model::FashionMode) {
            point.setX(x - 1);
            point.setY(y + 66);
        }
    } else {
        if (m_model->desktopMode() == Model::EfficientMode) {
            point.setX(x * 2 + 23);
            point.setY(y + 26);
        } else if (m_model->desktopMode() == Model::FashionMode) {
            point.setX(x + 4);
            point.setY(y + 26);
        }
    }

    m_selectBtn->move(point);
    m_selectBtn->raise();
}
