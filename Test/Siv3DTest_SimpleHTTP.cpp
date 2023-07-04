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

TEST_CASE("SimpleHTTP::Get with headers")
{
	const URL url = U"https://httpbin.org/bearer";
	const HashTable<String, String> headers = { { U"Authorization", U"Bearer TOKEN123456abcdef" } };
	const FilePath saveFilePath = U"auth_result.json";
    const auto response = SimpleHTTP::Get(url, headers, saveFilePath);

    REQUIRE(static_cast<bool>(response) == true);
    REQUIRE(response.getStatusLine().rtrimmed() == U"HTTP/1.1 200 OK");
    REQUIRE(FromEnum(response.getStatusCode()) == 200);
}

TEST_CASE("SimpleHTTP::Post with headers")
{
	const URL url = U"https://httpbin.org/post";
	const HashTable<String, String> headers = { { U"Content-Type", U"application/json" } };
	const std::string data = JSON
	{
		{ U"body", U"Hello, Siv3D!" },
		{ U"date", DateTime::Now().format() },
	}.formatUTF8();
	const FilePath saveFilePath = U"post_result.json";
    auto response = SimpleHTTP::Post(url, headers, data.data(), data.size(), saveFilePath);

    REQUIRE(static_cast<bool>(response) == true);
    REQUIRE(response.getStatusLine().rtrimmed() == U"HTTP/1.1 200 OK");
    REQUIRE(FromEnum(response.getStatusCode()) == 200);
}
