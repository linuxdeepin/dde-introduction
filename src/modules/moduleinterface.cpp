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

#include "moduleinterface.h"

#include <DHiDPIHelper>

DWIDGET_USE_NAMESPACE

ModuleInterface::ModuleInterface(QWidget *parent)
    : QFrame(parent)
    , m_model(Model::Instance())
    , m_worker(Worker::Instance())
    , m_selectBtn(new QLabel(this))
    , m_updateSelectBtnTimer(new QTimer(this))
{
    m_selectBtn->setPixmap(DHiDPIHelper::loadNxPixmap(":/resources/list_select.png"));
    m_selectBtn->setFixedSize(16, 16);

    m_updateSelectBtnTimer->setInterval(0);
    m_updateSelectBtnTimer->setSingleShot(true);

    connect(m_updateSelectBtnTimer, &QTimer::timeout, this, &ModuleInterface::updateSelectBtnPos);
}

void ModuleInterface::setIconType(Model::IconType type)
{
    switch (type) {
    case Model::Big:
        updateBigIcon();
        break;
    case Model::Small:
        updateSmallIcon();
        break;
    default:
        break;
    }
}

void ModuleInterface::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);

    m_updateSelectBtnTimer->start();
}
