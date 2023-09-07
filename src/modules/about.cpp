// Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "about.h"

//关于页面 暂时不用
About::About(QWidget *parent)
    : QScrollArea(parent)
{
    DLabel *label = new DLabel;
    label->setWordWrap(true);
    setWidgetResizable(true);
    setFocusPolicy(Qt::NoFocus);
    setFrameStyle(QFrame::NoFrame);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setWidget(label);

    label->setMargin(20);
    label->setOpenExternalLinks(true);
}
