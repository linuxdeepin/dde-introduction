/*
* Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
*
* Author:     zhangyunfeng <zhangyunfeng@uniontech.com>
* Maintainer: zhangyunfeng <zhangyunfeng@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "previousbutton.h"

#include <gtest/gtest.h>

class ut_previousbutton_test : public ::testing::Test
{
    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

    previousButton *m_testModule = nullptr;
};

void ut_previousbutton_test::SetUp()
{
    m_testModule = new previousButton();
}

void ut_previousbutton_test::TearDown()
{
    delete m_testModule;
}

TEST_F(ut_previousbutton_test, keyPressEvent)
{
    ASSERT_TRUE(m_testModule);
    EXPECT_EQ(36,m_testModule->width());
    EXPECT_EQ(36,m_testModule->height());

    QKeyEvent keyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier);
    m_testModule->keyPressEvent(&keyEvent);

    QKeyEvent keyEvent1(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier);
    m_testModule->keyPressEvent(&keyEvent1);

    QKeyEvent keyEvent2(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier);
    m_testModule->keyPressEvent(&keyEvent2);

    QKeyEvent keyEvent3(QEvent::KeyPress,Qt::Key_End,Qt::NoModifier);
    m_testModule->keyPressEvent(&keyEvent3);
}
