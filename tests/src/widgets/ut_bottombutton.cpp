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

#include "bottombutton.h"

#include <gtest/gtest.h>

class ut_bottombutton_test : public ::testing::Test
{
    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

    BottomButton *m_testModule = nullptr;
};

void ut_bottombutton_test::SetUp()
{
    m_testModule = new BottomButton();
}

void ut_bottombutton_test::TearDown()
{
    delete m_testModule;
}

TEST_F(ut_bottombutton_test, paintEvent)
{
    ASSERT_TRUE(m_testModule);
    //当前页面的大小对比
    EXPECT_EQ(85,m_testModule->width());
    EXPECT_EQ(30,m_testModule->height());
    QPaintEvent* event;
    m_testModule->paintEvent(event);
}

TEST_F(ut_bottombutton_test, setText)
{
    m_testModule->setText("test bottom button");
    EXPECT_EQ("test bottom button",m_testModule->m_text);
}

TEST_F(ut_bottombutton_test, setRect)
{
    m_testModule->setRect(QRect(0,0,m_testModule->width(),m_testModule->height()));
    EXPECT_EQ(QRect(0,0,m_testModule->width(),m_testModule->height()),m_testModule->m_rect);
}
