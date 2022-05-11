/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     xiepengfei <xiepengfei@uniontech.com>
*
* Maintainer: xiepengfei <xiepengfei@uniontech.com>
*
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

#ifndef NEXTBUTTON_H
#define NEXTBUTTON_H

#include <QPushButton>
#include <QPainterPath>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsDropShadowEffect>

#include <DPushButton>

DWIDGET_USE_NAMESPACE

class NextButton : public DPushButton
{
    Q_OBJECT
public:
    explicit NextButton(const QString &text, QWidget *parent = nullptr);

    //Normal 正常　Transparent 透明
    enum Mode {
        Normal,
        Transparent
    };

    void setMode(Mode mode);

public:
    //void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *) override;

private:
    QString m_text;
    Mode m_mode;
    QColor m_currentColor;
};

#endif // NEXTBUTTON_H
