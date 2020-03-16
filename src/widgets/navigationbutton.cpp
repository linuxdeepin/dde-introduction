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

#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QPainter>

#include <DGuiApplicationHelper>
#include <DPalette>

DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

NavigationButton::NavigationButton(QString text, DWidget *parent)
    : DPushButton(text, parent)
{
    setCheckable(true);
    setFocusPolicy(Qt::NoFocus);
    this->setFlat(true);
    this->setText("");

    m_shadow = new QGraphicsDropShadowEffect(this);
    m_label = new DLabel(this);
    m_label->setElideMode(Qt::ElideRight);
    m_label->setText(text);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setContentsMargins(10, 0, 0, 0);
    layout->addWidget(m_label);
    setLayout(layout);
    initButton();

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this,
            &NavigationButton::initButton);
    connect(this, &NavigationButton::clicked, this, &NavigationButton::initButton);
}

void NavigationButton::initButton()
{
    int type = DGuiApplicationHelper::instance()->themeType();
    DPalette pl = m_label->palette();
    if (type == 1) {
        if (isChecked()) {
            pl.setColor(DPalette::WindowText, Qt::white);
            m_shadow->setOffset(0, 4);
            m_shadow->setColor(QColor(44, 167, 248, int(0.4 * 255)));
            m_shadow->setBlurRadius(6);
        } else {
            pl.setColor(DPalette::WindowText, QColor(65, 77, 104));
            m_shadow->setColor(QColor(0, 42, 175, 0));
        }
    } else {
        if (isChecked()) {
            pl.setColor(DPalette::WindowText, Qt::white);
            m_shadow->setOffset(0, 4);
            m_shadow->setColor(QColor(0, 42, 175, int(0.4 * 255)));
            m_shadow->setBlurRadius(6);
        } else {
            pl.setColor(DPalette::WindowText, QColor(192, 198, 212));
            m_shadow->setColor(QColor(0, 42, 175, 0));
        }
    }
    setGraphicsEffect(m_shadow);
    m_label->setPalette(pl);
    m_label->setForegroundRole(DPalette::WindowText);
}

/*QSize NavigationButton::setHint()
{
    QFontMetrics fm(this->font());
    QRect rec = fm.boundingRect(m_label->text());
    return rec.size();
}*/

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
