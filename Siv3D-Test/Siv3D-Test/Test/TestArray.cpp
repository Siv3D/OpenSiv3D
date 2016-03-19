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

# include "Siv3DTest.hpp"

void TestArray()
{
	using namespace s3d;

	{
		static_assert(sizeof(Array<int32>) == sizeof(std::vector<s3d::int32>), "");

		Array<int32> vi = { 10, 20, 30, 40, 50 };

		for (int i = 0; i < 3; ++i)
		{
			{
				RDTSC r;
				std::vector<int> v(100000, 123);
			}

			{
				RDTSC r;
				Array<int> v(100000, 123);
			}
		}
	}

	{
		const Array<int32> v = { 1,2,3,4,5 };

		Println(L"[operator <<]---");
		Println((Array<int32>{100, 200, 300} << 1 << 2 << 3).join(L", "));

		Println(L"[all]---");
		Println(Array<int32>{}.all());
		Println(v.all());
		Println(Array<bool>{false, false, false}.all());
		Println(Array<double>{-0.4, 0.5, 1.2}.all([](auto v) { return v > 0.0; }));
	}




	{
		static_assert(sizeof(Array<bool>) == sizeof(std::basic_string<bool>), "");

		Array<bool> vb = { true, true, false, false, true };

		for (int i = 0; i < 3; ++i)
		{
			{
				RDTSC r;
				std::vector<bool> v(100000, true);
			}

			{
				RDTSC r;
				Array<bool> v(100000, true);
			}
		}
	}
}
