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
	Println(L"### FormatFloat");
	Println(L"###### FormatFloat (fixed = false)");
	Println(FormatFloat(3.1415, 0));
	Println(FormatFloat(-123.456, 4));
	Println(FormatFloat(0.000000000234, 4));
	Println(FormatFloat(20, 4));
	Println(FormatFloat(123456.7890123, 4));
	Println(FormatFloat(10000000000, 4));
	Println(FormatFloat(5500.00030, 4));
	Println(FormatFloat(3123412341325, 4));
	Println(FormatFloat(DBL_MAX, 4));
	Println(FormatFloat(DBL_TRUE_MIN, 4));
	Println(FormatFloat(std::sqrt(-1), 4));
	Println(FormatFloat(std::numeric_limits<double>::infinity(), 4));
	Println(FormatFloat(-std::numeric_limits<double>::infinity(), 4));

	Println(L"###### FormatFloat (fixed = true)");
	Println(FormatFloat(3.1415, 0, true));
	Println(FormatFloat(-123.456, 4, true));
	Println(FormatFloat(0.000000000234, 4, true));
	Println(FormatFloat(20, 4, true));
	Println(FormatFloat(123456.7890123, 4, true));
	Println(FormatFloat(10000000000, 4, true));
	Println(FormatFloat(5500.00030, 4, true));
	Println(FormatFloat(3123412341325, 4, true));
	Println(FormatFloat(DBL_MAX, 4, true));
	Println(FormatFloat(DBL_TRUE_MIN, 325, true));
	Println(FormatFloat(std::sqrt(-1), 4, true));
	Println(FormatFloat(std::numeric_limits<double>::infinity(), 4, true));
	Println(FormatFloat(-std::numeric_limits<double>::infinity(), 4, true));
}
