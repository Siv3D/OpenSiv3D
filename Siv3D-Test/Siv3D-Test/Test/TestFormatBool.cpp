//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D.hpp>
# include <gtest/gtest.h>

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
