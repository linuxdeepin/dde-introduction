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

#include <QVBoxLayout>

#include <DFrame>
#include <DLabel>
#include <DImageButton>

DWIDGET_USE_NAMESPACE

class BaseWidget : public DFrame
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);

signals:
    void clicked();

public slots:
    void setBigPixmap(const QString &url);
    void setSmallPixmap(const QString &url);
    void setPixmap(const QPixmap &pixmap);
    void setBigPixmap(const QPixmap &pixmap);
    void setSmallPixmap(const QPixmap &pixmap);
    void setTitle(const QString &title);
    void setChecked(bool checked);
    void setLayoutSpacing(int i);

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QVBoxLayout* m_layout;
    DLabel* m_title;
    BorderWidget* m_borderWidget;
    DImageButton* m_selectBtn;
};

#endif // BASEWIDGET_H
