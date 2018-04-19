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

#include "borderwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

BorderWidget::BorderWidget(QWidget *parent)
    : QFrame(parent)
    , m_checked(false)
{
}

void BorderWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;

    update();
}

void BorderWidget::setChecked(bool checked)
{
    m_checked = checked;

    update();
}

void BorderWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPainterPath contentPath;

    QRect pixRect(QPoint(3, 3), m_pixmap.size() / devicePixelRatioF());

    contentPath.addRoundedRect(pixRect, 5, 5);
    painter.setClipPath(contentPath);

    painter.drawPixmap(pixRect, m_pixmap);

    // draw border
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(1, 1, -1, -1), 5, 5);
    painter.setClipRect(QRect(), Qt::NoClip);
    if (m_checked) {
        QPen pen(QColor("#2CA7F8"));
        pen.setWidth(2);

        painter.setPen(pen);
        painter.drawPath(path);
    } else {
        QPen pen(QColor(0, 0, 0, 0.1 * 255));
        pen.setWidth(1);

        painter.setPen(pen);
        painter.drawPath(path);
    }
}
