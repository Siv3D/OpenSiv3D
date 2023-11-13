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

TEST_CASE("EvalOpt")
{
	SECTION("Simple")
	{
		REQUIRE(EvalOpt(U"1+2") == 3.0);
		REQUIRE(EvalOpt(U"2-1") == 1.0);
		REQUIRE(EvalOpt(U"2*3") == 6.0);
		REQUIRE(EvalOpt(U"3/2") == 1.5);
	}

	SECTION("With WhiteSpace")
	{
		REQUIRE(EvalOpt(U" 1+2") == 3.0);
		REQUIRE(EvalOpt(U"1 +2") == 3.0);
		REQUIRE(EvalOpt(U"1+2 ") == 3.0);
		REQUIRE(EvalOpt(U"1+ 2") == 3.0);
		REQUIRE(EvalOpt(U"1 + 2") == 3.0);
	}

	SECTION("Invalid")
	{
		REQUIRE(EvalOpt(U"@") == none);
	}
}
