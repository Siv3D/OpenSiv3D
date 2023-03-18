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

# define CATCH_CONFIG_RUNNER
# include "Siv3DTest.hpp"
# include <unordered_map>

void Siv3DTest()
{
	Console.open();
	
	{
# if SIV3D_PLATFORM(WEB)
		Catch::Session().run();
# else
		FileSystem::Remove(U"test/");
	
		FileSystem::Copy(U"../../Test/test/", U"./test/");

		Catch::Session().run();

		FileSystem::Remove(U"test/");
# endif
	}
}

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

TEST_CASE("HashTable")
{
	SECTION("Lookup (std::unordered_map)")
	{
		std::unordered_map<String, int32> table;
		for (auto c : Range(U'A', U'Z'))
		{
			table.emplace(String(8, c), c);
		}

		CHECK(table[U"AAAAAAAA"_s] + table[U"BBBBBBBB"_s] + table[U"CCCCCCCC"_s] + table[U"ZZZZZZZZ"_s] == (U'A' + U'B' + U'C' + U'Z'));
		CHECK(table[U"AAAAAAAA"] + table[U"BBBBBBBB"] + table[U"CCCCCCCC"] + table[U"ZZZZZZZZ"] == (U'A' + U'B' + U'C' + U'Z'));
		//CHECK(table.contains(U"ABC"_s) + table.contains(U"BBBBBBBB"_s) + table.contains(U"ABC"_s) + table.contains(U"ZZZZZZZZ"_s) == 2);
		//CHECK(table.contains(U"ABC") + table.contains(U"BBBBBBBB") + table.contains(U"ABC") + table.contains(U"ZZZZZZZZ") == 2);

		//BENCHMARK("table[U\"...\"_s]")
		//{
		//	return table[U"AAAAAAAA"_s] + table[U"BBBBBBBB"_s] + table[U"CCCCCCCC"_s] + table[U"ZZZZZZZZ"_s];
		//};

		//BENCHMARK("table.contains(U\"...\"_s)")
		//{
		//	return table.contains(U"ABC"_s) + table.contains(U"BBBBBBBB"_s) + table.contains(U"ABC"_s) + table.contains(U"ZZZZZZZZ"_s);
		//};

		//BENCHMARK("table[U\"...\"]")
		//{
		//	return table[U"AAAAAAAA"] + table[U"BBBBBBBB"] + table[U"CCCCCCCC"] + table[U"ZZZZZZZZ"];
		//};

		//BENCHMARK("table.contains(U\"...\")")
		//{
		//	return table.contains(U"ABC") + table.contains(U"BBBBBBBB") + table.contains(U"ABC") + table.contains(U"ZZZZZZZZ");
		//};
	}

	SECTION("Lookup")
	{
		HashTable<String, int32, phmap::priv::hash_default_hash<String>, phmap::priv::hash_default_eq<String>> table;
		for (auto c : Range(U'A', U'Z'))
		{
			table.emplace(String(8, c), c);
		}

		CHECK(table[U"AAAAAAAA"_s] + table[U"BBBBBBBB"_s] + table[U"CCCCCCCC"_s] + table[U"ZZZZZZZZ"_s] == (U'A' + U'B' + U'C' + U'Z'));
		CHECK(table[U"AAAAAAAA"] + table[U"BBBBBBBB"] + table[U"CCCCCCCC"] + table[U"ZZZZZZZZ"] == (U'A' + U'B' + U'C' + U'Z'));
		CHECK(table.contains(U"ABC"_s) + table.contains(U"BBBBBBBB"_s) + table.contains(U"ABC"_s) + table.contains(U"ZZZZZZZZ"_s) == 2);
		CHECK(table.contains(U"ABC") + table.contains(U"BBBBBBBB") + table.contains(U"ABC") + table.contains(U"ZZZZZZZZ") == 2);

		//BENCHMARK("table[U\"...\"_s]")
		//{
		//	return table[U"AAAAAAAA"_s] + table[U"BBBBBBBB"_s] + table[U"CCCCCCCC"_s] + table[U"ZZZZZZZZ"_s];
		//};

		//BENCHMARK("table.contains(U\"...\"_s)")
		//{
		//	return table.contains(U"ABC"_s) + table.contains(U"BBBBBBBB"_s) + table.contains(U"ABC"_s) + table.contains(U"ZZZZZZZZ"_s);
		//};

		//BENCHMARK("table[U\"...\"]")
		//{
		//	return table[U"AAAAAAAA"] + table[U"BBBBBBBB"] + table[U"CCCCCCCC"] + table[U"ZZZZZZZZ"];
		//};

		//BENCHMARK("table.contains(U\"...\")")
		//{
		//	return table.contains(U"ABC") + table.contains(U"BBBBBBBB") + table.contains(U"ABC") + table.contains(U"ZZZZZZZZ");
		//};
	}

	SECTION("Heterogeneous Lookup")
	{
		HashTable<String, int32> table;
		for (auto c : Range(U'A', U'Z'))
		{
			table.emplace(String(8, c), c);
		}

		CHECK(table[U"AAAAAAAA"_s] + table[U"BBBBBBBB"_s] + table[U"CCCCCCCC"_s] + table[U"ZZZZZZZZ"_s] == (U'A' + U'B' + U'C' + U'Z'));
		CHECK(table[U"AAAAAAAA"] + table[U"BBBBBBBB"] + table[U"CCCCCCCC"] + table[U"ZZZZZZZZ"] == (U'A' + U'B' + U'C' + U'Z'));
		CHECK(table[U"AAAAAAAA"_sv] + table[U"BBBBBBBB"_sv] + table[U"CCCCCCCC"_sv] + table[U"ZZZZZZZZ"_sv] == (U'A' + U'B' + U'C' + U'Z'));

		CHECK(table.contains(U"ABC"_s) + table.contains(U"BBBBBBBB"_s) + table.contains(U"ABC"_s) + table.contains(U"ZZZZZZZZ"_s) == 2);
		CHECK(table.contains(U"ABC") + table.contains(U"BBBBBBBB") + table.contains(U"ABC") + table.contains(U"ZZZZZZZZ") == 2);
		CHECK(table.contains(U"ABC"_sv) + table.contains(U"BBBBBBBB"_sv) + table.contains(U"ABC"_sv) + table.contains(U"ZZZZZZZZ"_sv) == 2);

		//BENCHMARK("table[U\"...\"_s]")
		//{
		//	return table[U"AAAAAAAA"_s] + table[U"BBBBBBBB"_s] + table[U"CCCCCCCC"_s] + table[U"ZZZZZZZZ"_s];
		//};

		//BENCHMARK("table.contains(U\"...\"_s)")
		//{
		//	return table.contains(U"ABC"_s) + table.contains(U"BBBBBBBB"_s) + table.contains(U"ABC"_s) + table.contains(U"ZZZZZZZZ"_s);
		//};

		//BENCHMARK("table[U\"...\"]")
		//{
		//	return table[U"AAAAAAAA"] + table[U"BBBBBBBB"] + table[U"CCCCCCCC"] + table[U"ZZZZZZZZ"];
		//};

		//BENCHMARK("table.contains(U\"...\")")
		//{
		//	return table.contains(U"ABC") + table.contains(U"BBBBBBBB") + table.contains(U"ABC") + table.contains(U"ZZZZZZZZ");
		//};

		//BENCHMARK("table[U\"...\"_sv]")
		//{
		//	return table[U"AAAAAAAA"_sv] + table[U"BBBBBBBB"_sv] + table[U"CCCCCCCC"_sv] + table[U"ZZZZZZZZ"_sv];
		//};

		//BENCHMARK("table.contains(U\"...\"_sv)")
		//{
		//	return table.contains(U"ABC"_sv) + table.contains(U"BBBBBBBB"_sv) + table.contains(U"ABC"_sv) + table.contains(U"ZZZZZZZZ"_sv);
		//};
	}
}
