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

#include <player_engine.h>
#include <QBitmap>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QIcon>
#include <QLocale>
#include <QMediaPlaylist>
#include <QPainter>
#include <QPushButton>
#include <QResizeEvent>
#include <QTimer>

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
    , m_background(new CoverPhoto(this))
//, m_label(new DLabel(m_background))
{
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

    //社区版/专业版/个人版视频封面不同
    if (DSysInfo::isCommunityEdition()) {
        m_strVideoCoverIcon = QString(":/resources/community_Moment.png");
    } else if(DSysInfo::deepinType() == DSysInfo::DeepinProfessional || DSysInfo::deepinType() == DSysInfo::DeepinPersonal) {
        m_strVideoCoverIcon = QString(":/resources/demo_Moment.jpg");
    }

    connect(m_hideAni, &QPropertyAnimation::finished, this, [=] { m_control->hide(); });

    connect(m_leaveTimer, &QTimer::timeout, this, [=] { m_hideAni->start(); });

    /*connect(m_pauseTimer, &QTimer::timeout, this, [=] {
        m_video->engine().pauseResume();
    });*/

    // m_pauseTimer->setSingleShot(true);
    // dmr::Backend::setDebugLevel(dmr::Backend::DebugLevel::Debug);

    setObjectName("VideoWidget");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addWidget(m_video, 0, Qt::AlignCenter);

    updateBigIcon();

    m_control->setFixedSize(48, 48);
    m_control->raise();

    /*qreal ratio = 1.0;

    QDir videoPath(ResourcesQDir());

    const QString &file = videoPath.path() + QString("/demo.mp4");*/

    connect(m_control, &DImageButton::clicked, this, &VideoWidget::onControlButtonClicked,
            Qt::QueuedConnection);
    connect(&m_video->engine(), &dmr::PlayerEngine::stateChanged, this,
            &VideoWidget::updateControlButton, Qt::QueuedConnection);

    autoPlay = !autoPlay;
    m_video->engine().setBackendProperty("pause-on-start", autoPlay ? "false" : "true");

    // m_video->engine().playlist().append(QUrl::fromLocalFile(qt_findAtNxFile(file,
    // devicePixelRatioF(), &ratio)));
    // m_video->engine().playlist().setPlayMode(dmr::PlaylistModel::SingleLoop);
    // m_video->engine().play();

    /*QTimer::singleShot(1000, this, [=] {
        m_pauseTimer->setInterval(m_video->engine().duration() * 1000);
    });*/

    updateControlButton();
    setLayout(layout);

    // m_label->show();
    // m_label->raise();
    m_background->setWindowFlags(Qt::FramelessWindowHint);
    m_background->raise();
    m_control->raise();
    m_load = false;
}

void VideoWidget::updateBigIcon()
{
    setFixedSize(700, 450);
    m_video->setFixedSize(this->size());
    if (m_background != nullptr) {
        QPixmap pixmap(m_strVideoCoverIcon);
        pixmap = pixmap.scaled(m_video->size() /* * devicePixelRatioF()*/, Qt::IgnoreAspectRatio,
                               Qt::SmoothTransformation);
        // m_label->setPixmap(pixmap);
        // m_label->setFixedSize(m_video->size());
        m_background->setFixedSize(m_video->size());
        m_background->setPixmap(pixmap);
    }

    updateClip();
}

void VideoWidget::updateSmallIcon()
{
    const QSize size(540, 340);
    setFixedSize(size);
    m_video->setFixedSize(size);
    if (m_background != nullptr) {
        QPixmap pixmap(m_strVideoCoverIcon);
        pixmap = pixmap.scaled(m_video->size() /* * devicePixelRatioF()*/, Qt::IgnoreAspectRatio,
                               Qt::SmoothTransformation);
        // m_label->setPixmap(pixmap);
        // m_label->setFixedSize(m_video->size());
        m_background->setFixedSize(m_video->size());
        m_background->setPixmap(pixmap);
    }

    updateClip();
}

void VideoWidget::updateSelectBtnPos() {}

void VideoWidget::updateControlButton()
{
    const QPoint &p = rect().center() - m_control->rect().center();

    // switch (m_video->engine().state()) {
    if (m_video->engine().state() == dmr::PlayerEngine::Playing) {
        /*QLocale locale;
        const QString &file = QString("15.5 SP3_%1.ass").arg(locale.language() == QLocale::Chinese ?
                                                             "zh_CN" :
                                                             "en_US");
        m_video->engine().loadSubtitle(QFileInfo(ResourcesQDir().path() +
        QString("/%1").arg(file)));

        const dmr::PlayingMovieInfo info = m_video->engine().playingMovieInfo();

        for (const dmr::SubtitleInfo sub : info.subs) {
            const QString &title = sub["title"].toString();
            if (title == file) {
                m_video->engine().selectSubtitle(info.subs.indexOf(sub));
                break;
            }
        }*/

        m_control->setNormalPic(":/resources/pause_normal.svg");
        m_control->setHoverPic(":/resources/pause_hover.svg");
        m_control->setPressPic(":/resources/pause_press.svg");
        m_btnAni->stop();
        m_btnAni->setStartValue(p);
        m_btnAni->setEndValue(QPoint(p.x(), height() - m_control->height() - 20));
        m_btnAni->start();
        if (m_background != nullptr) {
            delete m_background;
            m_background = nullptr;
        }
    } else {
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
        /*int elapsed = m_video->engine().duration() - m_video->engine().elapsed() + 1;
        if (elapsed == 0)
            m_pauseTimer->setInterval(1000);*/
    }
}

void VideoWidget::onControlButtonClicked()
{
    /*if (m_video->engine().paused()) {
        m_pauseTimer->start();
    } else {
        m_pauseTimer->stop();
    }*/

    if (!m_load) {
        qreal ratio = 1.0;
        QDir videoPath(ResourcesQDir());
        const QString &file = videoPath.path() + QString("/demo.mp4");
        m_video->engine().playlist().append(
            QUrl::fromLocalFile(qt_findAtNxFile(file, devicePixelRatioF(), &ratio)));
        m_video->engine().playlist().setPlayMode(dmr::PlaylistModel::SingleLoop);
        m_load = true;
    }
    m_video->engine().pauseResume();
    m_video->engine().play();

    // updateControlButton();
}

void VideoWidget::stop()
{
    if (m_video->engine().state() == dmr::PlayerEngine::Playing) {
        m_video->engine().pauseResume();
        m_video->engine().play();
    }
    // updateControlButton();
}

void VideoWidget::updateInterface(QSize size)
{
    setFixedSize(size);
    m_video->setFixedSize(size);
    if (m_background != nullptr) {
        QPixmap pixmap(m_strVideoCoverIcon);
        pixmap = pixmap.scaled(m_video->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_background->setFixedSize(m_video->size());
        m_background->setPixmap(pixmap);
    }

    updateClip();
}

void VideoWidget::showVideoControlButton()
{
    m_hideEffect->setOpacity(1);
    m_control->show();
    m_leaveTimer->stop();
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

void VideoWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
        onControlButtonClicked();
}

void VideoWidget::updateClip()
{
    QPainterPath path;
    QRectF rectF;
    rectF.setTopLeft(rect().topLeft() - QPointF(2, 2));
    rectF.setBottomRight(rect().bottomRight());
    path.addRoundedRect(rectF, 5, 5);
    m_clip->setClipPath(path);
}
