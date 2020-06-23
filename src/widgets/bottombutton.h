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

#ifndef BOTTOMBUTTON_H
#define BOTTOMBUTTON_H

#include <QRect>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#include <DImageButton>
#include <DWidget>

DWIDGET_USE_NAMESPACE

class BottomButton : public DImageButton
{
    Q_OBJECT
public:
    explicit BottomButton(DWidget *parent = nullptr);
    void setText(const QString text) {m_text = text;};
    void setRect(const QRect rect) {m_rect = rect;};

protected:
    void paintEvent(QPaintEvent *event);

private:
    QString         m_text;
    QRect           m_rect;
};

#endif // BOTTOMBUTTON_H
