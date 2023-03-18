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

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4566)

TEST_CASE("TextReader")
{
	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.encoding() == TextEncoding::Default);
		REQUIRE(reader.path() == U"");
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.encoding() == TextEncoding::Default);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF8_NO_BOM);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF8_WITH_BOM);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF16LE);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF16BE);
		REQUIRE(reader.path() == path);
	}
}

TEST_CASE("TextReader::readChar() | SHORT")
{
	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}
}

TEST_CASE("TextReader::readChar() | LONG")
{
	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}
}

TEST_CASE("TextReader::readChar(char32&) | SHORT")
{
	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'S');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'i');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'v');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'3');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'D');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'S');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'i');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'v');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'3');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'D');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'S');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'i');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'v');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'3');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'D');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}
}

TEST_CASE("TextReader::readChar(char32&) | LONG")
{
	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}
}

TEST_CASE("TextReader::readLine() | SHORT")
{
	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"Siv3D");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"Siv3D");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"Siv3D");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"Siv3D");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}
}

TEST_CASE("TextReader::readLine() | LONG")
{
	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"あいうえお");
		REQUIRE(reader.readLine() == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine() == U"ABC");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"AB");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"A");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"あいうえお");
		REQUIRE(reader.readLine() == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine() == U"ABC");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"AB");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"A");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"あいうえお");
		REQUIRE(reader.readLine() == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine() == U"ABC");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"AB");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"A");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == U"あいうえお");
		REQUIRE(reader.readLine() == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine() == U"ABC");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"AB");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == U"A");
		REQUIRE(reader.readLine() == U"");
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}
}

TEST_CASE("TextReader::readLine(String&) | SHORT")
{
	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"Siv3D");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"Siv3D");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"Siv3D");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"Siv3D");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}
}

TEST_CASE("TextReader::readLine(String&) | LONG")
{
	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"あいうえお");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"ABC");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"AB");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"A");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"あいうえお");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"ABC");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"AB");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"A");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"あいうえお");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"ABC");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"AB");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"A");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"あいうえお");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"𩸽齟齬😎🙊");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"ABC");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"AB");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"A");
		REQUIRE(reader.readLine(line) == true);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
		REQUIRE(reader.readLine(line) == false);
		REQUIRE(line == U"");
	}
}

TEST_CASE("TextReader::readLines() | SHORT")
{
	const Array<String> expected = { U"Siv3D" };

	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		String line;
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}
}

TEST_CASE("TextReader::readLines() | LONG")
{
	const Array<String> expected =
	{
		U"あいうえお",
		U"𩸽齟齬😎🙊",
		U"ABC",
		U"",
		U"AB",
		U"",
		U"A",
		U"",
	};

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readLines() == expected);
		REQUIRE(reader.readLines() == Array<String>{});
		REQUIRE(reader.readLines() == Array<String>{});
	}
}

TEST_CASE("TextReader::readLines(Array<String>&) | SHORT")
{
	const Array<String> expected = { U"Siv3D" };

	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}
}

TEST_CASE("TextReader::readLines(Array<String>&) | LONG")
{
	const Array<String> expected =
	{
		U"あいうえお",
		U"𩸽齟齬😎🙊",
		U"ABC",
		U"",
		U"AB",
		U"",
		U"A",
		U"",
	};

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		Array<String> lines;
		REQUIRE(reader.readLines(lines) == true);
		REQUIRE(lines == expected);
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
		REQUIRE(reader.readLines(lines) == false);
		REQUIRE(lines == Array<String>{});
	}
}

TEST_CASE("TextReader::readAll() | SHORT")
{
	const String expected = U"Siv3D";

	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}
}

TEST_CASE("TextReader::readAll() | LONG")
{
	const String expected = U"あいうえお\n𩸽齟齬😎🙊\nABC\n\nAB\n\nA\n\n";

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readAll() == expected);
		REQUIRE(reader.readAll() == U"");
		REQUIRE(reader.readAll() == U"");
	}
}

TEST_CASE("TextReader::readAll(String&) | SHORT")
{
	const String expected = U"Siv3D";

	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/nonexist.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}
}

TEST_CASE("TextReader::readAll(String&) | LONG")
{
	const String expected = U"あいうえお\n𩸽齟齬😎🙊\nABC\n\nAB\n\nA\n\n";

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		String s;
		REQUIRE(reader.readAll(s) == true);
		REQUIRE(s == expected);
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
		REQUIRE(reader.readAll(s) == false);
		REQUIRE(s == U"");
	}
}

SIV3D_DISABLE_MSVC_WARNINGS_POP()
