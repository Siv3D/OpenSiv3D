//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include <gtest/gtest.h>

TEST(Optional, null)
{

}

TEST(Optional, ref)
{
	int i = 42;
	s3d::Optional<int&> opt{ i };
	EXPECT_EQ(&*opt, &i);
	EXPECT_EQ(&(opt.value()), &i);
	EXPECT_EQ(43, opt.then([](int&v) {return v = 43; }).value());
	EXPECT_EQ(*opt, 43);
	EXPECT_EQ(i, 43);
}