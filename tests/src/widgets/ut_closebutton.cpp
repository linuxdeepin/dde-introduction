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

#include "closebutton.h"

#include <gtest/gtest.h>

class ut_closebutton_test : public ::testing::Test
{
    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

    CloseButton *m_testModule = nullptr;
};

void ut_closebutton_test::SetUp()
{
    m_testModule = new CloseButton();
}

void ut_closebutton_test::TearDown()
{
    delete m_testModule;
}

TEST_F(ut_closebutton_test, keyPressEvent)
{
    ASSERT_TRUE(m_testModule);
    EXPECT_EQ(51,m_testModule->width());
    EXPECT_EQ(51,m_testModule->height());
    EXPECT_FALSE(m_testModule->beFocused);
    QKeyEvent keyEvent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier);
    m_testModule->keyPressEvent(&keyEvent);
}

TEST_F(ut_closebutton_test, paintEvent)
{
    QPaintEvent event(QRect(0,0,m_testModule->width(),m_testModule->height()));
    m_testModule->beFocused = true;
    m_testModule->paintEvent(&event);
}

TEST_F(ut_closebutton_test, mousePressEvent)
{
    QMouseEvent *event = new QMouseEvent(QEvent::Type::MouseButtonPress, QPointF(100, 100),
                                         Qt::MouseButton::LeftButton, Qt::MouseButton::LeftButton,
                                         Qt::KeyboardModifier::NoModifier);
    m_testModule->mousePressEvent(event);
    delete event;
}
