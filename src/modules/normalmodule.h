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

#ifndef NORMALMODULE_H
#define NORMALMODULE_H

#include "../widgets/bottomnavigation.h"
#include "../widgets/navigationbutton.h"
#include "../widgets/closebutton.h"
#include "about.h"
#include "desktopmodemodule.h"
#include "iconmodule.h"
#include "photoslide.h"
#include "support.h"
#include "wmmodemodule.h"
#ifndef DISABLE_VIDEO
#include "videowidget.h"
#endif

#include <QButtonGroup>
#include <QFont>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>
#include <QVBoxLayout>

#include <DFontSizeManager>
#include <DLabel>
#include <DPalette>
#include <DSuggestButton>
#include <DSysInfo>
#include <DWidget>

#include <com_deepin_wmswitcher.h>

using WMSwitcher = com::deepin::WMSwitcher;

DGUI_USE_NAMESPACE
DCORE_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

class ModuleInterface;
class NavigationButton;
class NormalModule : public DWidget
{
    Q_OBJECT
public:
    explicit NormalModule(DWidget *parent = nullptr);
     ~NormalModule() override;
    void keyPressEvent(QKeyEvent *) override;

signals:
    void closeMainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    void updateCurrentWidget(const int index);
    void updataButton(QAbstractButton *btn);

private slots:
    void initTheme(int type);
    void updateLabel();
    void updateInterface(int);

private:
    CloseButton *m_closeFrame;
    QVBoxLayout *m_leftNavigationLayout;
    QVBoxLayout *m_rightContentLayout;
    QButtonGroup *m_buttonGrp;
    QMap<QWidget *, int> m_buttonMap;
    QMap<QAbstractButton *, QString> m_titleMap;
    QMap<QAbstractButton *, QString> m_describeMap;
    QMap<int, QWidget *> m_modules;
    NavigationButton *m_button;
    QWidget *m_currentWidget;
    WMSwitcher *m_wmSwitcher;
    DLabel *m_titleLabel;
    DLabel *m_describe;
    DWidget *m_content;
    int m_index;
    bool isx86;
    bool tab_be_press;
    bool m_bSystemIsServer;
};

#endif  // NORMALMODULE_H
