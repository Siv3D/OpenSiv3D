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
# include "Siv3DTest.hpp"

void TestArray()
{
	{
		static_assert(sizeof(s3d::Array<s3d::int32>) == sizeof(std::vector<s3d::int32>), "");

		s3d::Array<s3d::int32> vi = { 10, 20, 30, 40, 50 };

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

	{
		static_assert(sizeof(s3d::Array<bool>) == sizeof(std::basic_string<bool>), "");

		s3d::Array<bool> vb = { true, true, false, false, true };

		for (int i = 0; i < 3; ++i)
		{
			{
				RDTSC r;
				std::vector<bool> v(100000, true);
			}

			{
				RDTSC r;
				s3d::Array<bool> v(100000, true);
			}
		}
	}
}
