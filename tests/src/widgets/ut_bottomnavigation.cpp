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

#include "bottomnavigation.h"

#include <gtest/gtest.h>

class ut_bottomnavigation_test : public ::testing::Test
{
    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

    BottomNavigation *m_testModule = nullptr;
};

void ut_bottomnavigation_test::SetUp()
{
    m_testModule = new BottomNavigation();
}

void ut_bottomnavigation_test::TearDown()
{
    delete m_testModule;
}

TEST_F(ut_bottomnavigation_test, onButtonClicked)
{
    ASSERT_TRUE(m_testModule);
    EXPECT_TRUE(m_testModule->m_buttons.size() > 0);
    m_testModule->onButtonClicked();
}


TEST_F(ut_bottomnavigation_test, eventFilter)
{
    QObject *watched;
    QEvent event(QEvent::Enter);
    m_testModule->eventFilter(watched,&event);
    EXPECT_EQ(Qt::PointingHandCursor,m_testModule->cursor());

    QEvent event1(QEvent::Leave);
    m_testModule->eventFilter(watched,&event1);
    EXPECT_EQ(Qt::ArrowCursor,m_testModule->cursor());

}
