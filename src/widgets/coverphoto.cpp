/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     xiepengfei <xiepengfei@uniontech.com>
*
* Maintainer: xiepengfei <xiepengfei@uniontech.com>
*
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

#include "coverphoto.h"

CoverPhoto::CoverPhoto(QWidget *parent)
: DFrame(parent)
{

}

void CoverPhoto::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;

    update();
}

void CoverPhoto::paintEvent(QPaintEvent *event)
{
    DFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect pixRect(QPoint(0, 0), m_pixmap.size()/* * devicePixelRatioF()*/);

    // draw background
//    QPainterPath contentPath;
//    contentPath.addRoundedRect(pixRect, 10, 10);
//    painter.setClipPath(contentPath);
    painter.drawPixmap(pixRect, m_pixmap);
}
