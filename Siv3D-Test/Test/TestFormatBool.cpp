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

TEST(FormatBool, ToString)
{
	EXPECT_EQ(ToString(true),							L"true");
	EXPECT_EQ(ToString(true, LetterCase::Lower),		L"true");
	EXPECT_EQ(ToString(true, LetterCase::Upper),		L"TRUE");
	EXPECT_EQ(ToString(true, LetterCase::Capitalized),	L"True");

	EXPECT_EQ(ToString(false),							L"false");
	EXPECT_EQ(ToString(false, LetterCase::Lower),		L"false");
	EXPECT_EQ(ToString(false, LetterCase::Upper),		L"FALSE");
	EXPECT_EQ(ToString(false, LetterCase::Capitalized),	L"False");
}

# endif
