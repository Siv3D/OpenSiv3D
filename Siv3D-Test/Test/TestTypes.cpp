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

TEST(Types, size)
{
	ASSERT_EQ(sizeof(s3d::int8 ), 1);
	ASSERT_EQ(sizeof(s3d::int16), 2);
	ASSERT_EQ(sizeof(s3d::int32), 4);
	ASSERT_EQ(sizeof(s3d::int64), 8);

	ASSERT_EQ(sizeof(s3d::uint8 ), 1);
	ASSERT_EQ(sizeof(s3d::uint16), 2);
	ASSERT_EQ(sizeof(s3d::uint32), 4);
	ASSERT_EQ(sizeof(s3d::uint64), 8);

	ASSERT_EQ(sizeof(s3d::wchar), sizeof(wchar_t));
}
