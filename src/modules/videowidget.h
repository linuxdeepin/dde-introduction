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

#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "moduleinterface.h"

#include <QVideoWidget>
#include <QMediaPlayer>
#include <dimagebutton.h>

#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>

DWIDGET_USE_NAMESPACE

class VideoWidget : public ModuleInterface {
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    void updateBigIcon() Q_DECL_OVERRIDE;
    void updateSmaillIcon() Q_DECL_OVERRIDE;
    void updateControlButton();
    void onControlButtonClicked();

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void resizeEvent(QResizeEvent *);

private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_video;
    QGraphicsVideoItem *m_videoItem;
    QMediaPlayer* m_player;
    DImageButton* m_control;
};

#endif
