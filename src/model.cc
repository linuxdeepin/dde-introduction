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

#include "model.h"

Model *Model::Instance()
{
    static Model * instance = new Model;
    return instance;
}

void Model::addIcon(const IconStruct &icon)
{
    if (m_iconList.contains(icon)) {
        return;
    }

    m_iconList << icon;

    emit iconAdded(icon);
}

void Model::removeIcon(const IconStruct &icon)
{
    Q_ASSERT(!m_iconList.contains(icon));

    m_iconList.removeOne(icon);

    emit iconRemoved(icon);
}

void Model::setCurrentIcon(const QString &icon)
{
    for (const IconStruct &tmp : m_iconList) {
        if (tmp.Id == icon) {
            m_currentIcon = tmp;
            emit iconChanged(tmp);
        }
    }
}

Model::Model(QObject *parent)
    : QObject(parent)
{

}

void Model::setDesktopMode(DesktopMode desktopMode)
{
    if (m_desktopMode == desktopMode) {
        return;
    }

    m_desktopMode = desktopMode;

    emit desktopModeChanged(desktopMode);
}

void Model::setWmType(WMType wmType)
{
    if (m_wmType == wmType) {
        return;
    }

    m_wmType = wmType;

    emit wmTypeChanged(wmType);
}
