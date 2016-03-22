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

using namespace s3d;

void TestArrayInt32()
{
	Log(L"###### Array<int32>");

	static_assert(sizeof(Array<int32>) == sizeof(std::vector<s3d::int32>), "");

	for (int i = 0; i < 3; ++i)
	{
		{
			RDTSC r;
			std::vector<int32> v(100000, 123);
		}

		{
			RDTSC r;
			Array<int32> v(100000, 123);
		}
	}

	const Array<int32> v = { 1, 2, 3, 4, 5 };

	Log(L"######### Array<int32>::operator <<");
	Log((Array<int32>{ 100, 200, 300 } << 1 << 2 << 3).join(L", "));

	Log(L"######### Array<int32>::all");
	Log(Array<int32>{}.all());
	Log(Array<int32>{}.all([](auto n) { return n < 10; }));
	Log(v.all());
	Log(v.all([](auto n) { return n < 10; }));
}

void TestArrayString()
{
	Log(L"###### Array<String>");
}

void TestArrayBool()
{
	Log(L"###### Array<bool>");

	static_assert(sizeof(Array<bool>) == sizeof(std::basic_string<bool>), "");

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

	const Array<bool> v = { true, true, false, false, true };
}

void TestArray__m128()
{
	Log(L"###### Array<__m128>");
}

void TestArray()
{
	Log(L"### Array");
	TestArrayInt32();
	TestArrayString();
	TestArrayBool();
	TestArray__m128();
}
