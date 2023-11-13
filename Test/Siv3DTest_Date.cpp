//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DTest.hpp"

TEST_CASE("Date")
{
	SECTION("format")
	{
		const Date date(2020, 1, 2);
		CHECK(date.format() == U"2020-01-02");
	}

	//BENCHMARK("Date::format()")
	//{
	//	const Date date(2020, 1, 2);
	//	return date.format();
	//};
}
