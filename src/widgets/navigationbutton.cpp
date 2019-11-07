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

#include "navigationbutton.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>

#include <DPalette>
#include <DLabel>

DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

NavigationButton::NavigationButton(QString text, DWidget *parent)
    : DPushButton(text, parent)
{
    setCheckable(true);
    setFocusPolicy(Qt::NoFocus);
    this->setFlat(true);
    m_text = text;

    /*DLabel *label = new DLabel(this);
    label->setText(m_text);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layoutlayoutlayoutlayout->setContentsMargins();
    layout->addWidget(label);
    setLayout(layout);*/
}

/*void NavigationButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QFont font;
    font.setFamily("SourceHanSansSC-Medium");
    font.setPixelSize(14);
    painter.setFont(font);
    QRect r = rect();
    r.setLeft(rect().left() + 10);
    r.setTop(rect().top() + 4);
    if (!isChecked()) {
        painter.fillRect(rect(),QColor(248,248,248));
        painter.setPen(QPen(QColor(65,77,104)));
        painter.drawText(r, m_text);
    } else {
        QRect bacrRect = rect();
        painter.setRenderHint(QPainter :: Antialiasing);
        QPainterPath path;
        path.addRoundedRect(bacrRect, 8, 8);
        painter.setPen(Qt::NoPen);
        painter.fillPath(path, QColor(0,129,255));
        painter.drawPath(path);
        painter.setPen(QPen(QColor(255,255,255)));
        painter.drawText(r, m_text);
    }
}*/
