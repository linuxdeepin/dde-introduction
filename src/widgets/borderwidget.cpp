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
    : DFrame(parent)
    , m_checked(false)
{
    setLineWidth(0);
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
    DFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect pixRect(QPoint(5, 5), m_pixmap.size() / devicePixelRatioF());

    // draw background
    QPainterPath contentPath;
    contentPath.addRoundedRect(pixRect, 10, 10);
    painter.setClipPath(contentPath);
    painter.drawPixmap(pixRect, m_pixmap);

    QPen pen(QColor(0, 0, 0, 0.1 * 255));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawPath(contentPath);

    // draw border
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(2, 2, -2, -2), 10, 10);
    painter.setClipRect(QRect(), Qt::NoClip);
    if (m_checked) {
        QPen pen(QColor("#0081FF"));
        pen.setWidth(4);

        painter.setPen(pen);
        painter.drawPath(path);
    }
}
