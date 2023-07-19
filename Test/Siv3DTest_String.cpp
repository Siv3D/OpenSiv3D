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

TEST_CASE("String")
{
	SECTION("Constructor")
	{
		REQUIRE(String(5, U'A') == U"AAAAA");
	}

	SECTION("operator bool")
	{
		REQUIRE(!String(U"") == true);
		REQUIRE(!String(U"ABC") == false);
		REQUIRE(static_cast<bool>(String(U"")) == false);
		REQUIRE(static_cast<bool>(String(U"ABC")) == true);
	}
}
