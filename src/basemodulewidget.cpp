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

    /*m_titleLbl->setStyleSheet("font-size: 20px;"
                              "font-weight: medium;");*/

    /*m_describeLbl->setStyleSheet("color: #848484;"
                                 "font-size: 11px;"
                                 "font-weight: 500;");*/
}

void BaseModuleWidget::setTitle(const QString &title)
{
    m_titleLbl->setText(title);
}

void BaseModuleWidget::setDescribe(const QString &describe)
{
    m_describeLbl->setText(describe);
    m_describeLbl->adjustSize();
}
