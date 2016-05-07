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

TEST(Types, size)
{
	using namespace s3d;

	ASSERT_EQ(sizeof(int8 ), 1);
	ASSERT_EQ(sizeof(int16), 2);
	ASSERT_EQ(sizeof(int32), 4);
	ASSERT_EQ(sizeof(int64), 8);

	ASSERT_EQ(sizeof(uint8 ), 1);
	ASSERT_EQ(sizeof(uint16), 2);
	ASSERT_EQ(sizeof(uint32), 4);
	ASSERT_EQ(sizeof(uint64), 8);

	ASSERT_EQ(sizeof(wchar), sizeof(wchar_t));

	# if   defined (SIV3D_TARGET_WINDOWS_DESKTOP_X64)
		ASSERT_EQ(sizeof(size_t), 8);
	# elif defined (SIV3D_TARGET_WINDOWS_DESKTOP_X86)
		ASSERT_EQ(sizeof(size_t), 4);
	# elif defined (SIV3D_TARGET_OSX)
		ASSERT_EQ(sizeof(size_t), 8);
	# else
	# error	
	# endif
}
