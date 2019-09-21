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
#include <QGraphicsOpacityEffect>
#include <QMediaPlaylist>
#include <QIcon>
#include <QLocale>
#include <player_engine.h>

static QDir ResourcesQDir()
{
    QDir videoPath(qApp->applicationDirPath());
    videoPath.setSorting(QDir::Name);
    videoPath.cd("/usr/share/dde-introduction");
    return videoPath;
}

VideoWidget::VideoWidget(bool autoPlay, QWidget *parent)
    : ModuleInterface(parent)
    , m_video(new dmr::PlayerWidget(this))
    , m_control(new DImageButton(this))
    , m_clip(new DClipEffectWidget(m_video))
    , m_btnAni(new QPropertyAnimation(m_control, "pos", this))
    , m_hideAni(new QPropertyAnimation(this))
    , m_leaveTimer(new QTimer(this))
    , m_pauseTimer(new QTimer(this))
{

    //dmr::Backend::setDebugLevel(dmr::Backend::DebugLevel::Debug);
    m_selectBtn->hide();

    m_leaveTimer->setSingleShot(true);
    m_leaveTimer->setInterval(1000);

    m_hideEffect = new QGraphicsOpacityEffect(m_control);
    m_hideEffect->setOpacity(1);
    m_control->setGraphicsEffect(m_hideEffect);

    m_btnAni->setDuration(250);
    m_btnAni->setEasingCurve(QEasingCurve::InOutCubic);

    m_hideAni->setDuration(250);
    m_hideAni->setEasingCurve(QEasingCurve::InOutCubic);
    m_hideAni->setPropertyName("opacity");
    m_hideAni->setTargetObject(m_hideEffect);
    m_hideAni->setStartValue(1.0f);
    m_hideAni->setEndValue(0.0f);
    click = true;
    first - true;

    connect(m_hideAni, &QPropertyAnimation::finished, this, [ = ] {
        m_control->hide();
    });

    connect(m_leaveTimer, &QTimer::timeout, this, [ = ] {
        m_hideAni->start();
    });

    connect(m_pauseTimer, &QTimer::timeout, this, [ = ] {
        m_video->engine().pauseResume();
    });

    m_pauseTimer->setSingleShot(true);

    setObjectName("VideoWidget");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_video, 0, Qt::AlignCenter);

    updateBigIcon();

    m_control->setFixedSize(48, 48);
    m_control->raise();

    qreal ratio = 1.0;

    QDir videoPath(ResourcesQDir());

    const QString &file = videoPath.path() + QString("/demo.mp4");

    connect(m_control, &DImageButton::clicked, this, &VideoWidget::onControlButtonClicked, Qt::QueuedConnection);
    connect(m_control, &DImageButton::clicked, this, &VideoWidget::clickButton);
    connect(&m_video->engine(), &dmr::PlayerEngine::stateChanged, this, &VideoWidget::updateControlButton, Qt::QueuedConnection);

    m_video->engine().setBackendProperty("pause-on-start", autoPlay ? "false" : "true");

    m_video->engine().playlist().append(QUrl::fromLocalFile(qt_findAtNxFile(file, devicePixelRatioF(), &ratio)));
    m_video->engine().playlist().setPlayMode(dmr::PlaylistModel::SingleLoop);
    m_video->engine().play();
    //m_video->play(QUrl::fromLocalFile(qt_findAtNxFile(file, devicePixelRatioF(), &ratio)));

    QTimer::singleShot(1000, this, [ = ] {
        m_pauseTimer->setInterval(m_video->engine().duration() * 1000);
    });

    updateControlButton();

    setLayout(layout);

    m_control->raise();
}

void VideoWidget::updateBigIcon()
{
    setFixedSize(720, 450);
    m_video->setFixedSize(700, 450);

    updateClip();
}

void VideoWidget::updateSmallIcon()
{
    const QSize size(550, 346);
    setFixedSize(size);
    m_video->setFixedSize(size);

    updateClip();
}

void VideoWidget::updateSelectBtnPos()
{
}

void VideoWidget::updateControlButton()
{
    const QPoint &p = rect().center() - m_control->rect().center();

    switch (m_video->engine().state()) {
    case dmr::PlayerEngine::Playing: {
        QLocale locale;

        /*#ifdef PROFESSIONAL

                const QString &file = QString("15.5 SP3_%1.ass").arg(locale.language() == QLocale::Chinese ?
                                                                     "zh_CN" :
                                                                     "en_US");
                m_video->engine().loadSubtitle(QFileInfo(ResourcesQDir().path() + QString("/%1").arg(file)));

        #else
                const QString &file = QString("%1.ass").arg(locale.language() == QLocale::Chinese ?
                                                                     "zh_CN" :
                                                                     "en_US");
                QString tt = ResourcesQDir().path() + QString("/%1").arg(file);
                m_video->engine().loadSubtitle(QFileInfo(ResourcesQDir().path() + QString("/%1").arg(file)));
        #endif*/
        const QString &file = QString("15.5 SP3_%1.ass").arg(locale.language() == QLocale::Chinese ?
                                                             "zh_CN" :
                                                             "en_US");
        m_video->engine().loadSubtitle(QFileInfo(ResourcesQDir().path() + QString("/%1").arg(file)));


        const dmr::PlayingMovieInfo info = m_video->engine().playingMovieInfo();

        for (const dmr::SubtitleInfo sub : info.subs) {
            const QString &title = sub["title"].toString();
            if (title == file) {
                m_video->engine().selectSubtitle(info.subs.indexOf(sub));
                break;
            }
        }

        m_control->setNormalPic(":/resources/pause_normal.svg");
        m_control->setHoverPic(":/resources/pause_hover.svg");
        m_control->setPressPic(":/resources/pause_press.svg");
        m_btnAni->stop();
        m_btnAni->setStartValue(p);
        m_btnAni->setEndValue(QPoint(p.x(), height() - m_control->height() - 20));
        m_btnAni->start();
    }
    break;
    case dmr::PlayerEngine::Paused: {
        m_control->setNormalPic(":/resources/play_normal.svg");
        m_control->setHoverPic(":/resources/play_hover.svg");
        m_control->setPressPic(":/resources/play_press.svg");
        if (m_btnAni->startValue().toPoint() == p) {
            m_hideEffect->setOpacity(1);
            m_control->show();
            m_leaveTimer->stop();
            m_btnAni->stop();
            m_btnAni->setStartValue(m_control->pos());
            m_btnAni->setEndValue(p);
            m_btnAni->start();
        }
        // update pause timer
        int elapsed = m_video->engine().duration() - m_video->engine().elapsed() + 1;
        if (elapsed != 0)
            m_pauseTimer->setInterval(elapsed * 1000);
    }
    break;
    default:
        break;
    }
}

void VideoWidget::clickButton()
{
    click = !click;
}

void VideoWidget::onControlButtonClicked()
{
    if (m_video->engine().paused()) {
        m_pauseTimer->start();
    } else {
        m_pauseTimer->stop();
    }

    m_video->engine().pauseResume();
    m_video->engine().play();

    updateControlButton();
}

void VideoWidget::enterEvent(QEvent *e)
{
    ModuleInterface::enterEvent(e);

    m_hideEffect->setOpacity(1);
    m_control->show();
    m_leaveTimer->stop();
}

void VideoWidget::leaveEvent(QEvent *e)
{
    ModuleInterface::leaveEvent(e);

    if (m_video->engine().state() != dmr::PlayerEngine::Paused) {
        m_leaveTimer->start();
    }
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
