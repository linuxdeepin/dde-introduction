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

#include "basemodulewidget.h"
#include <QDebug>
#include <DPalette>

DGUI_USE_NAMESPACE

BaseModuleWidget::BaseModuleWidget(QWidget *content, QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
    , m_titleLbl(new DLabel(this))
    , m_describeLbl(new DLabel(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_describeLbl->setFixedSize(460, 40);
    m_describeLbl->setWordWrap(true);
    m_describeLbl->setAlignment(Qt::AlignCenter);
    m_describeLbl->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    m_layout->addSpacing(20);
    m_layout->addWidget(m_titleLbl, 0, Qt::AlignHCenter);
    m_layout->addStretch();
    m_layout->addWidget(content, 0, Qt::AlignCenter);
    m_layout->addStretch();
    m_layout->addWidget(m_describeLbl, 0, Qt::AlignHCenter);
    m_layout->addSpacing(15);

    setLayout(m_layout);

    m_type = 1;
}

void BaseModuleWidget::setTitle(const QString &title)
{
    QFont font;
    font.setFamily("SourceHanSansSC");
    font.setStyleName("Bold");
    font.setPixelSize(17);
    m_titleLbl->setFont(font);
    if (m_type == 1) {
        DPalette pa = m_titleLbl->palette();
        pa.setColor(DPalette::WindowText, QColor(0,26,46,255));
        m_titleLbl->setPalette(pa);
    } else {
        DPalette pa = m_titleLbl->palette();
        pa.setColor(DPalette::WindowText, QColor(192,198,212,255));
        m_titleLbl->setPalette(pa);
    }
    m_titleLbl->setText(title);
}

void BaseModuleWidget::setDescribe(const QString &describe)
{
    QFont font;
    font.setFamily("SourceHanSansSC");
    font.setStyleName("Normal");
    font.setPixelSize(12);
    m_describeLbl->setFont(font);
    if (m_type == 1) {
        DPalette pa = m_describeLbl->palette();
        pa.setColor(DPalette::WindowText, QColor(82,106,127,255));
        m_describeLbl->setPalette(pa);
    } else {
        DPalette pa = m_describeLbl->palette();
        pa.setColor(DPalette::WindowText, QColor(109,124,136,255));
        m_describeLbl->setPalette(pa);
    }
    m_describeLbl->setText(describe);
    m_describeLbl->adjustSize();
}

void BaseModuleWidget::setType(int type)
{
    m_type = type;
}
