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

#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPushButton>
#include <QTimer>
#include <QHBoxLayout>
#include <QResizeEvent>

VideoWidget::VideoWidget(QWidget *parent)
    : ModuleInterface(parent)
    , m_scene(new QGraphicsScene)
    , m_video(new QGraphicsView(m_scene))
    , m_videoItem(new QGraphicsVideoItem)
    , m_player(new QMediaPlayer(this))
    , m_control(new DImageButton(this))
{
    m_selectBtn->hide();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_video);

    setLayout(layout);

    m_scene->addItem(m_videoItem);

    m_video->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
    m_video->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_video->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_video->setGeometry(0, 0, 700, 450);
    m_videoItem->setSize(QSize(700, 450));

    m_control->setFixedSize(48, 48);
    m_control->raise();

    QMediaPlaylist *playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("file:///home/rekols/Videos/一択彼女加藤恵.mov"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_player->setPlaylist(playlist);
    m_player->setVideoOutput(m_videoItem);

    m_player->play();
    m_player->pause();

    updateControlButton();

    connect(m_control, &DImageButton::clicked, this, &VideoWidget::onControlButtonClicked);
    connect(m_player, &QMediaPlayer::stateChanged, this, &VideoWidget::updateControlButton);
}

void VideoWidget::updateBigIcon()
{
    m_video->setGeometry(0, 0, 700, 450);
    m_videoItem->setSize(QSize(700, 450));
}

void VideoWidget::updateSmaillIcon()
{
    m_video->setGeometry(0, 0, 580, 450);
    m_videoItem->setSize(QSize(580, 450));
}

void VideoWidget::updateControlButton()
{
    switch (m_player->state()) {
    case QMediaPlayer::PlayingState:
        m_control->setNormalPic(":/resources/pause.svg");
        m_control->setHoverPic(":/resources/pause_hover.svg");
        m_control->setPressPic(":/resources/pause_press.svg");
        break;
    case QMediaPlayer::PausedState:
        m_control->setNormalPic(":/resources/play.svg");
        m_control->setHoverPic(":/resources/play_hover.svg");
        m_control->setPressPic(":/resources/play_press.svg");
        break;
    }
}

void VideoWidget::onControlButtonClicked()
{
    switch (m_player->state()) {
    case QMediaPlayer::PlayingState:
        m_player->pause();
        break;
    case QMediaPlayer::PausedState:
        m_player->play();
        break;
    }

    updateControlButton();
}

void VideoWidget::resizeEvent(QResizeEvent *e)
{
    ModuleInterface::resizeEvent(e);

    m_control->move(QPoint((rect().width() - m_control->width()) / 2,
                            rect().height() / 2));
}
