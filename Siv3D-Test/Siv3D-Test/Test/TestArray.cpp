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
# include <vector>
# include "Siv3DTest.hpp"

void TestArray()
{
	static_assert(sizeof(std::vector<int>) == sizeof(s3d::Array<int>), "");

	s3d::Array<s3d::int32> v1 = { 10,20,30,40,50 };

	for (int i = 0; i < 3; ++i)
	{
		{
			RDTSC r;
			std::vector<int> v(100000, 123);
		}

		{
			RDTSC r;
			s3d::Array<int> v(100000, 123);
		}
	}
}
