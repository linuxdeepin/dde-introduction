// Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef UT_WMMODEMODULE_H
#define UT_WMMODEMODULE_H

#include "gtest/gtest.h"
// #include <QTest>
#include <QObject>

class ut_wmmodemodule_test : public QObject, public::testing::Test
{
    Q_OBJECT
public:
    ut_wmmodemodule_test();
};

#endif // UT_WMMODEMODULE_H
