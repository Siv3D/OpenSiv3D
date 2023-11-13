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

