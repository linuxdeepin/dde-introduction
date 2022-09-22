// Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-only

#ifndef UT_PHOTOSLIDE_H
#define UT_PHOTOSLIDE_H

#include "gtest/gtest.h"
// #include <QTest>
#include <QObject>

class ut_photoslide_test : public QObject, public::testing::Test
{
    Q_OBJECT
public:
    ut_photoslide_test();
};

#endif // UT_PHOTOSLIDE_H
