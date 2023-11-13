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

TEST_CASE("Unicode")
{
	SECTION("Narrow")
	{
		REQUIRE(Unicode::Narrow(U"") == "");
		REQUIRE(Unicode::Narrow(U"OpenSiv3D") == "OpenSiv3D");
		REQUIRE(Unicode::Narrow(U"あいうえお") == "あいうえお");
	}

	SECTION("ToWstring")
	{
		REQUIRE(Unicode::ToWstring(U"") == L"");
		REQUIRE(Unicode::ToWstring(U"OpenSiv3D") == L"OpenSiv3D");
		REQUIRE(Unicode::ToWstring(U"あいうえお") == L"あいうえお");
	}

	SECTION("ToUTF8")
	{
		const std::u8string_view u0 = u8"OpenSiv3D";
		const std::u8string_view u1 = u8"あいうえお";
		const std::string s0(u0.begin(), u0.end());
		const std::string s1(u1.begin(), u1.end());
		REQUIRE(Unicode::ToUTF8(U"") == "");
		REQUIRE(Unicode::ToUTF8(U"OpenSiv3D") == s0);
		REQUIRE(Unicode::ToUTF8(U"あいうえお") == s1);
	}

	SECTION("ToUTF16")
	{
		REQUIRE(Unicode::ToUTF16(U"") == u"");
		REQUIRE(Unicode::ToUTF16(U"OpenSiv3D") == u"OpenSiv3D");
		REQUIRE(Unicode::ToUTF16(U"あいうえお") == u"あいうえお");
	}

	SECTION("ToUTF32")
	{
		REQUIRE(Unicode::ToUTF32(U"") == U"");
		REQUIRE(Unicode::ToUTF32(U"OpenSiv3D") == U"OpenSiv3D");
		REQUIRE(Unicode::ToUTF32(U"あいうえお") == U"あいうえお");
	}
}
