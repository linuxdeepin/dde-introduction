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

#include "closebutton.h"
#include <QDebug>

CloseButton::CloseButton(QWidget *parent)
    : QPushButton(parent)
{
    setFixedSize(QSize(51, 51));
    beFocused = false;
}

void CloseButton::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    emit closeMainWindow();
}

//自己画一个选中框
void CloseButton::paintEvent(QPaintEvent *event)
{
    if (this->hasFocus() || beFocused) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(2, 2, -3, -3), 5, 5);
        painter.setClipRect(QRect(), Qt::NoClip);
        QColor color = DGuiApplicationHelper::instance()->applicationPalette()
                    .highlight().color();
        QPen pen(color);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
    }

    QWidget::paintEvent(event);
}

void CloseButton::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
        emit closeMainWindow();
}
