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

TEST_CASE("TextWriter::write()")
{
	const String expected = U"あいうえお\n𩸽齟齬😎🙊\nABC\n\nAB\n\nA\n\n";

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/textwriter/w1/utf8_no_bom.txt");
		TextWriter writer(path, TextEncoding::UTF8_NO_BOM);
		writer.write(expected);
		writer.close();
		
		TextReader reader(path);
		REQUIRE(reader.encoding() == TextEncoding::UTF8_NO_BOM);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/textwriter/w1/utf8_with_bom.txt");
		TextWriter writer(path, TextEncoding::UTF8_WITH_BOM);
		writer.write(expected);
		writer.close();

		TextReader reader(path);
		REQUIRE(reader.encoding() == TextEncoding::UTF8_WITH_BOM);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/textwriter/w1/utf16_le.txt");
		TextWriter writer(path, TextEncoding::UTF16LE);
		writer.write(expected);
		writer.close();

		TextReader reader(path);
		REQUIRE(reader.encoding() == TextEncoding::UTF16LE);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/textwriter/w1/utf16_be.txt");
		TextWriter writer(path, TextEncoding::UTF16BE);
		writer.write(expected);
		writer.close();

		TextReader reader(path);
		REQUIRE(reader.encoding() == TextEncoding::UTF16BE);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
	}
}
