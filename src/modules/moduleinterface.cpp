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

ModuleInterface::ModuleInterface(QWidget *parent)
    : DFrame(parent)
    , m_model(Model::Instance())
    , m_worker(Worker::Instance())
    , m_selectBtn(new IconButton(this))
    , m_updateSelectBtnTimer(new QTimer(this))
{
    m_updateSelectBtnTimer->setInterval(0);
    m_updateSelectBtnTimer->setSingleShot(true);
    setLineWidth(0);

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
    }
}

void ModuleInterface::resizeEvent(QResizeEvent *event)
{
    DFrame::resizeEvent(event);
    m_updateSelectBtnTimer->start();
}
