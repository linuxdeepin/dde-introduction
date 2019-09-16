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
#include "../dvideowidget.h"

#include <dimagebutton.h>
#include <DClipEffectWidget>
#include <QPropertyAnimation>
#include <player_widget.h>
#include <player_engine.h>

DWIDGET_USE_NAMESPACE

class QGraphicsOpacityEffect;
class VideoWidget : public ModuleInterface {
    Q_OBJECT
public:
    explicit VideoWidget(bool autoPlay, QWidget *parent = nullptr);

    void updateBigIcon() Q_DECL_OVERRIDE;
    void updateSmallIcon() Q_DECL_OVERRIDE;
    void updateSelectBtnPos() Q_DECL_OVERRIDE;
    void updateControlButton();
    void onControlButtonClicked();
    void stop();

protected:
    void enterEvent(QEvent *) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;

private:
    void updateClip();

private:
    dmr::PlayerWidget *m_video;
    DImageButton* m_control;
    DClipEffectWidget *m_clip;
    QPropertyAnimation *m_btnAni;
    QPropertyAnimation *m_hideAni;
    QGraphicsOpacityEffect *m_hideEffect;
    QTimer *m_leaveTimer;
    QTimer *m_pauseTimer;
};

#endif
