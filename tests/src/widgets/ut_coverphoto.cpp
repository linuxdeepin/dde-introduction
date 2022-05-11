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

#include "coverphoto.h"

#include <gtest/gtest.h>

class ut_coverphoto_test : public ::testing::Test
{
    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

    CoverPhoto *m_testModule = nullptr;
};

void ut_coverphoto_test::SetUp()
{
    m_testModule = new CoverPhoto();
}

void ut_coverphoto_test::TearDown()
{
    delete m_testModule;
}

TEST_F(ut_coverphoto_test, setPixmap)
{
    ASSERT_TRUE(m_testModule);
    QPixmap pixmap;
    m_testModule->setPixmap(pixmap);
}

TEST_F(ut_coverphoto_test, paintEvent)
{
    QPaintEvent *event;
    m_testModule->paintEvent(event);
}
