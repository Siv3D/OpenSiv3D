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

void TestFormatFloat()
{
	Println(L"### ToString");
	Println(L"###### ToString (fixed = false)");
	Println(ToString(3.1415, 0));
	Println(ToString(-123.456, 4));
	Println(ToString(0.000000000234, 4));
	Println(ToString(20.0, 4));
	Println(ToString(123456.7890123, 4));
	Println(ToString(10000000000.0, 4));
	Println(ToString(5500.00030, 4));
	Println(ToString(3123412341325.0, 4));
	Println(ToString(DBL_MAX, 4));
	Println(ToString(DBL_TRUE_MIN, 4));
	Println(ToString(std::sqrt(-1), 4));
	Println(ToString(std::numeric_limits<double>::infinity(), 4));
	Println(ToString(-std::numeric_limits<double>::infinity(), 4));

	Println(L"###### ToFixed");
	Println(ToFixed(3.1415, 0));
	Println(ToFixed(-123.456, 4));
	Println(ToFixed(0.000000000234, 4));
	Println(ToFixed(20.0, 4));
	Println(ToFixed(123456.7890123, 4));
	Println(ToFixed(10000000000.0, 4));
	Println(ToFixed(5500.00030, 4));
	Println(ToFixed(3123412341325.0, 4));
	Println(ToFixed(DBL_MAX, 4));
	Println(ToFixed(DBL_TRUE_MIN, 325));
	Println(ToFixed(std::sqrt(-1), 4));
	Println(ToFixed(std::numeric_limits<double>::infinity(), 4));
	Println(ToFixed(-std::numeric_limits<double>::infinity(), 4));
}
