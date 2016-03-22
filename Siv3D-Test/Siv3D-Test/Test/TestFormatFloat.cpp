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
	Log(L"### ToString");
	Log(L"###### ToString");
	Log(ToString(3.1415, 0));
	Log(ToString(-123.456, 4));
	Log(ToString(0.000000000234, 4));
	Log(ToString(20.0, 4));
	Log(ToString(123456.7890123, 4));
	Log(ToString(10000000000.0, 4));
	Log(ToString(5500.00030, 4));
	Log(ToString(3123412341325.0, 4));
	Log(ToString(std::numeric_limits<double>::max(), 4));
	Log(ToString((4.9406564584124654e-324), 4));
	Log(ToString(std::sqrt(-1), 4));
	Log(ToString(std::numeric_limits<double>::infinity(), 4));
	Log(ToString(-std::numeric_limits<double>::infinity(), 4));

	Log(L"###### ToFixed");
	Log(ToFixed(3.1415, 0));
	Log(ToFixed(-123.456, 4));
	Log(ToFixed(0.000000000234, 4));
	Log(ToFixed(20.0, 4));
	Log(ToFixed(123456.7890123, 4));
	Log(ToFixed(10000000000.0, 4));
	Log(ToFixed(5500.00030, 4));
	Log(ToFixed(3123412341325.0, 4));
	Log(ToFixed(std::numeric_limits<double>::max(), 4));
	Log(ToFixed((4.9406564584124654e-324), 325));
	Log(ToFixed(std::sqrt(-1), 4));
	Log(ToFixed(std::numeric_limits<double>::infinity(), 4));
	Log(ToFixed(-std::numeric_limits<double>::infinity(), 4));
}
