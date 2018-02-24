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

#include "basewidget.h"

BaseWidget::BaseWidget(QWidget *parent)
    : QFrame(parent)
    , m_layout(new QVBoxLayout(this))
    , m_title(new QLabel(this))
    , m_borderWidget(new BorderWidget(this))
    , m_selectBtn(new DImageButton(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_borderWidget, 0, Qt::AlignCenter);
    m_layout->addSpacing(5);
    m_layout->addWidget(m_title, 0, Qt::AlignCenter);

    setLayout(m_layout);
}

void BaseWidget::setPixmap(const QPixmap &pixmap)
{
    m_borderWidget->setFixedSize(pixmap.size());
    m_borderWidget->setPixmap(pixmap);

    adjustSize();

    m_selectBtn->raise();
    m_selectBtn->move(rect().topRight());
}

void BaseWidget::setTitle(const QString &title)
{
    m_title->setText(title);
}

void BaseWidget::setChecked(const bool checked)
{

}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mouseReleaseEvent(event);

    emit clicked();
}
