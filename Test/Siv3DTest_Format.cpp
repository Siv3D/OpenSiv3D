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

TEST_CASE("FormatLiteral")
{
	SECTION("Fmt")
	{
		REQUIRE(Fmt(U"")() == U"");
		REQUIRE(Fmt(U"{}")(12345) == U"12345");

		REQUIRE(Fmt(U""sv)() == U"");
		REQUIRE(Fmt(U"{}"sv)(12345) == U"12345");

		REQUIRE(Fmt(String(U""))() == U"");
		REQUIRE(Fmt(String(U"{}"))(12345) == U"12345");
	}

	SECTION("_fmt")
	{
		REQUIRE(U""_fmt() == U"");
		REQUIRE(U"{}"_fmt(12345) == U"12345");
		REQUIRE(U"{}"_fmt(U"OpenSiv3D") == U"OpenSiv3D");
		REQUIRE(U"{}"_fmt(U"あいうえお") == U"あいうえお");
	}

	SECTION("formatter<String>")
	{
		const String s = U"ABCDE";
		REQUIRE(U"{}"_fmt(s) == U"ABCDE");
		REQUIRE(U"{0}"_fmt(s) == U"ABCDE");
		REQUIRE(U"{:<6}"_fmt(s) == U"ABCDE ");
		REQUIRE(U"{:*>10}"_fmt(s) == U"*****ABCDE");
	}
}
