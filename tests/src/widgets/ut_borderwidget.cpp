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

#include "borderwidget.h"
#include "basewidget.h"

#include <gtest/gtest.h>

class ut_borderwidget_test : public ::testing::Test
{
    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

    BorderWidget *m_testModule = nullptr;
};

void ut_borderwidget_test::SetUp()
{
    m_testModule = new BorderWidget();
}

void ut_borderwidget_test::TearDown()
{
    delete m_testModule;
}

TEST_F(ut_borderwidget_test, setPixmap)
{
    ASSERT_TRUE(m_testModule);
    EXPECT_EQ(false,m_testModule->m_checked);
    QString testicon = ":/resources/effective_mode_big@3x.png";
    m_testModule->setPixmap(QPixmap(DHiDPIHelper::loadNxPixmap(testicon)));
    EXPECT_EQ(m_testModule->m_size,m_testModule->m_pixmap.size());
}

TEST_F(ut_borderwidget_test, setChecked)
{
    m_testModule->setChecked(false);
    EXPECT_FALSE(m_testModule->m_checked);
    m_testModule->setChecked(true);
    EXPECT_TRUE(m_testModule->m_checked);
}

TEST_F(ut_borderwidget_test, updateInterface)
{
    float f = 1.0;
    m_testModule->updateInterface(f);
    EXPECT_EQ(m_testModule->m_size,
              m_testModule->m_pixmap.size());
    float f1 = 2.0;
    m_testModule->updateInterface(f);
    EXPECT_EQ(m_testModule->m_size,
              m_testModule->m_pixmap.size());
}

TEST_F(ut_borderwidget_test, paintEvent)
{
    QPaintEvent* event;
    m_testModule->m_checked = false;
    m_testModule->paintEvent(event);

    m_testModule->m_checked = true;
    m_testModule->paintEvent(event);
}

