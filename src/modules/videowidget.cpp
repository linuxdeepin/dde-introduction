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

#include <QPushButton>
#include <QTimer>
#include <QHBoxLayout>
#include <QResizeEvent>
#include <QBitmap>
#include <QPainter>

VideoWidget::VideoWidget(QWidget *parent)
    : ModuleInterface(parent)
    , m_video(new DVideoWidget)
    , m_player(new QMediaPlayer(this))
    , m_control(new DImageButton(this))
    , m_clip(new DClipEffectWidget(m_video))
    , m_btnAni(new QPropertyAnimation(m_control, "pos", this))
{
    m_selectBtn->hide();

    m_btnAni->setDuration(250);
    m_btnAni->setEasingCurve(QEasingCurve::InOutCubic);

    setObjectName("VideoWidget");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_video, 0, Qt::AlignCenter);

    setLayout(layout);

    updateBigIcon();

    m_control->setFixedSize(48, 48);
    m_control->raise();

    m_player->setMedia(QUrl("http://10.0.13.109/dde-%E6%AC%A2%E8%BF%8E%E6%BC%94%E7%A4%BA%E8%A7%86%E9%A2%91.mp4"));

    m_video->setSource(m_player);
    m_video->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    m_video->setSourceVideoPixelRatio(devicePixelRatioF());

    m_player->setPosition(1);
    m_player->pause();

    updateControlButton();

    connect(m_control, &DImageButton::clicked, this, &VideoWidget::onControlButtonClicked, Qt::QueuedConnection);
    connect(m_player, &QMediaPlayer::stateChanged, this, &VideoWidget::updateControlButton, Qt::QueuedConnection);
}

void VideoWidget::updateBigIcon()
{
    setFixedSize(700, 450);
    m_video->setFixedSize(700, 450);

    updateClip();
}

void VideoWidget::updateSmallIcon()
{
    const QSize size(548, 342);
    setFixedSize(size);
    m_video->setFixedSize(size);

    updateClip();
}

void VideoWidget::updateControlButton()
{
    const QPoint &p = rect().center() - m_control->rect().center();
    switch (m_player->state()) {
    case QMediaPlayer::PlayingState: {
        m_control->setNormalPic(":/resources/pause_normal.svg");
        m_control->setHoverPic(":/resources/pause_hover.svg");
        m_control->setPressPic(":/resources/pause_press.svg");
        m_btnAni->stop();
        m_btnAni->setStartValue(p);
        m_btnAni->setEndValue(QPoint(p.x(), height() - m_control->height() - 20));
        m_btnAni->start();
    }
        break;
    case QMediaPlayer::PausedState: {
        m_control->setNormalPic(":/resources/play_normal.svg");
        m_control->setHoverPic(":/resources/play_hover.svg");
        m_control->setPressPic(":/resources/play_press.svg");
        if (m_btnAni->startValue().toPoint() == p) {
            m_btnAni->stop();
            m_btnAni->setStartValue(m_control->pos());
            m_btnAni->setEndValue(p);
            m_btnAni->start();
        }
    }
        break;
    case QMediaPlayer::StoppedState: {
        m_player->play();
        m_player->setPosition(1);
        m_player->pause();
    }
        break;
    default:
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
    default:
        break;
    }

    updateControlButton();
}

void VideoWidget::enterEvent(QEvent *e)
{
    ModuleInterface::enterEvent(e);

    m_control->show();
}

void VideoWidget::leaveEvent(QEvent *e)
{
    ModuleInterface::leaveEvent(e);

    m_control->setVisible(m_player->state() == QMediaPlayer::PausedState);
}

void VideoWidget::resizeEvent(QResizeEvent *e)
{
    ModuleInterface::resizeEvent(e);

    m_control->move(rect().center() - m_control->rect().center());
}

void VideoWidget::updateClip()
{
    QPainterPath path;
    path.addRoundedRect(rect(), 5, 5);
    m_clip->setClipPath(path);
}
