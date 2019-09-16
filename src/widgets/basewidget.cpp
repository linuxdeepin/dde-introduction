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
#include <DHiDPIHelper>
#include <QDebug>

DWIDGET_USE_NAMESPACE

BaseWidget::BaseWidget(QWidget *parent)
    : DFrame(parent)
    , m_layout(new QVBoxLayout(this))
    , m_title(new DLabel(this))
    , m_borderWidget(new BorderWidget(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(16);

    m_layout->addStretch();
    m_layout->addWidget(m_borderWidget, 0, Qt::AlignCenter);
    m_layout->addWidget(m_title, 0, Qt::AlignCenter);
    m_layout->addStretch();

    setLayout(m_layout);
}

void BaseWidget::setPixmap(const QString &url) {
    setPixmap(QPixmap(DHiDPIHelper::loadNxPixmap(url)));
}

void BaseWidget::setPixmap(const QPixmap &pixmap)
{
    m_borderWidget->setFixedSize(pixmap.size() /*/ devicePixelRatioF()*/ + QSize(10, 10));
    m_borderWidget->setPixmap(pixmap);

    setFixedWidth(m_borderWidget->width());
}

void BaseWidget::setTitle(const QString &title)
{
    m_title->setText(title);
}

void BaseWidget::setChecked(bool checked)
{
    m_borderWidget->setChecked(checked);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mouseReleaseEvent(event);

    emit clicked();
}

void BaseWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    return;
}
