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

# include "Siv3DTest.hpp"

# if defined(SIV3D_DO_TEST)

TEST(Types, size)
{
	using namespace s3d;

	ASSERT_EQ(sizeof(int8 ), (size_t)1);
	ASSERT_EQ(sizeof(int16), (size_t)2);
	ASSERT_EQ(sizeof(int32), (size_t)4);
	ASSERT_EQ(sizeof(int64), (size_t)8);

	ASSERT_EQ(sizeof(uint8 ), (size_t)1);
	ASSERT_EQ(sizeof(uint16), (size_t)2);
	ASSERT_EQ(sizeof(uint32), (size_t)4);
	ASSERT_EQ(sizeof(uint64), (size_t)8);

	ASSERT_EQ(sizeof(wchar), sizeof(wchar_t));

# if defined(SIV3D_TARGET_WINDOWS_DESKTOP_X64)

	ASSERT_EQ(sizeof(size_t), (size_t)8);

# elif defined(SIV3D_TARGET_WINDOWS_DESKTOP_X86)

	ASSERT_EQ(sizeof(size_t), (size_t)4);

# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

	ASSERT_EQ(sizeof(size_t), (size_t)8);

# else

	# error	

# endif
}

# endif
