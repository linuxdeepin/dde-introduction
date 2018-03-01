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

#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include "borderwidget.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

class BaseWidget : public QFrame
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

Q_SIGNALS:
    void clicked();

public Q_SLOTS:
    void setPixmap(const QString &url);
    void setPixmap(const QPixmap &pixmap);
    void setTitle(const QString &title);

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QVBoxLayout* m_layout;
    QLabel* m_title;
    BorderWidget* m_borderWidget;
    DImageButton* m_selectBtn;
};

#endif // BASEWIDGET_H
