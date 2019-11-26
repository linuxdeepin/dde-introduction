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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgets/nextbutton.h"

#include <com_deepin_wmswitcher.h>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSettings>
#include <QWidget>
#include <QKeyEvent>

#include <DMainWindow>
#include <DIconButton>
#include <DImageButton>
#include <DWidget>

using WMSwitcherInter = com::deepin::WMSwitcher;

DWIDGET_USE_NAMESPACE

class BaseModuleWidget;
class MainWindow : public DMainWindow {
  Q_OBJECT

public:
  MainWindow(DWidget *parent = 0);
  ~MainWindow();

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void previous();
  void next();

private:
  void slotTheme();
  void initUI();
  void initConnect();
  void bindAnimation();
  void updateModule(const int index);
  void animationHandle();

  BaseModuleWidget *initDesktopModeModule();
  BaseModuleWidget *initWMModeModule();
  BaseModuleWidget *initIconModule();

private:
  int m_index;
  NextButton *m_nextBtn;
  DIconButton *m_previousBtn;
  NextButton *m_doneBtn;
  DWidget *m_current;
  DWidget *m_last;
  QPropertyAnimation *m_currentAni;
  QPropertyAnimation *m_lastAni;
  DWidget *m_fakerWidget;
  QSettings *m_settings;
  WMSwitcherInter *m_displayInter;
  bool isx86;
  bool m_isFirst;
};

#endif // MAINWINDOW_H
