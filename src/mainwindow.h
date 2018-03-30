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

#include <QPropertyAnimation>
#include <QPushButton>
#include <QSettings>

#include <daboutdialog.h>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

class BaseModuleWidget;
class MainWindow : public DAbstractDialog {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private Q_SLOTS:
  void previous();
  void next();

private:
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
  QPushButton *m_nextBtn;
  DImageButton *m_previousBtn;
  QWidget *m_current;
  QWidget *m_last;
  QPropertyAnimation *m_currentAni;
  QPropertyAnimation *m_lastAni;
  QWidget *m_fakerWidget;
  QSettings *m_settings;
};

#endif // MAINWINDOW_H
