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

#include "videowidget.h"

#include <QMediaPlayer>
#include <QPushButton>
#include <QTimer>
#include <QHBoxLayout>

VideoWidget::VideoWidget(QWidget *parent)
    : ModuleInterface(parent)
    , m_video(new QVideoWidget(this))
    , m_player(new QMediaPlayer(this))
    , m_control(new DImageButton())
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_video);

    setLayout(layout);

    m_player->setVideoOutput(m_video);

    m_player->setMedia(QUrl("file:///home/haruyukilxz/Videos/羽毛的光芒.mp4"));
    m_video->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    m_video->setGeometry(0, 0, 700, 450);

    m_player->play();
    m_player->pause();
}

void VideoWidget::updateBigIcon()
{
    m_video->setFixedSize(700, 450);
}

void VideoWidget::updateSmaillIcon()
{
    m_video->setFixedSize(580, 450);
}
