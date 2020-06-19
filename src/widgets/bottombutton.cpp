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

#include "bottombutton.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>

BottomButton::BottomButton(DWidget *parent)
    : DImageButton(parent)
{
    setCheckable(true);
    setFixedSize(QSize(85,30));
}

void BottomButton::paintEvent(QPaintEvent *event)
{
    QFont font;
    font.setFamily("SourceHanSansSC");
    font.setStyleName("Medium");
    font.setPixelSize(14);

    QFontMetrics fm(font);
    QRect rec = fm.boundingRect(m_text);
    setFixedWidth(rec.width());

    QPainter painter(this);
    painter.setFont(font);
    painter.setPen(QPen(QColor(0,129,255)));
    painter.drawText(rect(), m_text);
}
