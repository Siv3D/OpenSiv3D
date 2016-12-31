//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DTest.hpp"

# if defined(SIV3D_DO_TEST)

using namespace s3d;
using namespace s3d::Math;

TEST(Fmod, Fmod)
{
	EXPECT_EQ(Math::Fmod(2, 2), 0);
	EXPECT_EQ(Math::Fmod(2, 2.5f), 2.0);
	EXPECT_EQ(Math::Fmod(2, 2.5), 2.0);

	EXPECT_EQ(Math::Fmod(2.5f, 2), 0.5);
	EXPECT_EQ(Math::Fmod(2.5f, 2.0f), 0.5f);
	EXPECT_EQ(Math::Fmod(2.5f, 2.0), 0.5);

	EXPECT_EQ(Math::Fmod(2.5, 2), 0.5);
	EXPECT_EQ(Math::Fmod(2.5, 2.0f), 0.5);
	EXPECT_EQ(Math::Fmod(2.5, 2.0), 0.5);

	EXPECT_EQ(Math::Fmod(Point(2, 3), Point(2, 3)), Point(0, 0));
	EXPECT_EQ(Math::Fmod(Point(2, 3), Float2(2.2f, 3.3f)), Float2(2.0f, 3.0f));
	EXPECT_EQ(Math::Fmod(Point(2, 3), Vec2(2.2, 3.3)), Vec2(2.0f, 3.0f));

	EXPECT_EQ(Math::Fmod(Float2(2, 3), Point(2, 3)), Point(0, 0));
	EXPECT_EQ(Math::Fmod(Float2(2, 3), Float2(2.2f, 3.3f)), Float2(2.0f, 3.0f));
	EXPECT_EQ(Math::Fmod(Float2(2, 3), Vec2(2.2, 3.3)), Vec2(2.0f, 3.0f));

	EXPECT_EQ(Math::Fmod(Vec2(2, 3), Point(2, 3)), Point(0, 0));
	EXPECT_EQ(Math::Fmod(Vec2(2, 3), Float2(2.2f, 3.3f)), Float2(2.0f, 3.0f));
	EXPECT_EQ(Math::Fmod(Vec2(2, 3), Vec2(2.2, 3.3)), Vec2(2.0f, 3.0f));
}

# endif
