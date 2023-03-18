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

TEST_CASE("TextEncoding")
{
	SECTION("GetTextEncoding")
	{
		REQUIRE(Unicode::GetTextEncoding(U"test/text/empty.txt") == TextEncoding::UTF8_NO_BOM);
		REQUIRE(Unicode::GetTextEncoding(U"test/text/utf8_no_bom.txt") == TextEncoding::UTF8_NO_BOM);
		REQUIRE(Unicode::GetTextEncoding(U"test/text/utf8_with_bom.txt") == TextEncoding::UTF8_WITH_BOM);
		REQUIRE(Unicode::GetTextEncoding(U"test/text/utf16_le.txt") == TextEncoding::UTF16LE);
		REQUIRE(Unicode::GetTextEncoding(U"test/text/utf16_be.txt") == TextEncoding::UTF16BE);
	}

	SECTION("GetBOMSize")
	{
		REQUIRE(Unicode::GetBOMSize(TextEncoding::Unknown) == 0);
		REQUIRE(Unicode::GetBOMSize(TextEncoding::UTF8_NO_BOM) == 0);
		REQUIRE(Unicode::GetBOMSize(TextEncoding::UTF8_WITH_BOM) == 3);
		REQUIRE(Unicode::GetBOMSize(TextEncoding::UTF16LE) == 2);
		REQUIRE(Unicode::GetBOMSize(TextEncoding::UTF16BE) == 2);
	}
}
