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
using namespace std::literals;

TEST(Base64, Encode)
{
	EXPECT_EQ(Base64::Encode("ABCDEF"s), L"QUJDREVG");
}

# endif
