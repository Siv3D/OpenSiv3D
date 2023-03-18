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
# include <fstream>

TEST_CASE("BinaryReader")
{
	SECTION("default")
	{
		BinaryReader reader;
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == U"");

		reader.close();
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == U"");
	}

	SECTION("Nonexist")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/nonexist.bin");
		BinaryReader reader(path);
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == U"");

		reader.close();
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == U"");
	}

	SECTION("empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/empty.bin");
		BinaryReader reader(path);
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == path);

		reader.close();
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == U"");
	}

	SECTION("small")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.size() == 255);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == path);

		reader.close();
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == U"");
	}

	SECTION("large")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/large.bin");
		BinaryReader reader(path);
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(!reader == false);
		REQUIRE(static_cast<bool>(reader) == true);
		REQUIRE(reader.size() == 130'064);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == path);

		reader.close();
		REQUIRE(reader.supportsLookahead() == true);
		REQUIRE(reader.isOpen() == false);
		REQUIRE(!reader == true);
		REQUIRE(static_cast<bool>(reader) == false);
		REQUIRE(reader.size() == 0);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.path() == U"");
	}
}

TEST_CASE("BinaryReader::read(size)")
{
	std::array<uint8, 255> expectedSmall;
	for (size_t i = 0; i < expectedSmall.size(); ++i)
	{
		expectedSmall[i] = uint8(i + 1);
	}

	SECTION("small | 1 byte / read")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		std::array<uint8, 255> buffer;

		for (auto& byte : buffer)
		{
			reader.read(byte);
		}

		REQUIRE(buffer == expectedSmall);
		REQUIRE(reader.getPos() == 255);

		uint8 unused = 0;
		REQUIRE(reader.read(unused) == false);
	}

	SECTION("small | 255 bytes / read")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		std::array<uint8, 255> buffer;
		REQUIRE(reader.read(buffer) == true);
		REQUIRE(buffer == expectedSmall);
		REQUIRE(reader.getPos() == 255);

		uint8 unused = 0;
		REQUIRE(reader.read(unused) == false);

		reader.close();
		REQUIRE(reader.read(buffer) == false);
	}

	Array<uint32> expectedLarge(32516);
	for (size_t i = 0; i < expectedLarge.size(); ++i)
	{
		expectedLarge[i] = uint32((i+1) * 123456);
	}

	SECTION("large | (32516*4) bytes / read")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/large.bin");
		BinaryReader reader(path);

		Array<uint32> buffer(reader.size() / sizeof(uint32));
		REQUIRE(reader.read(buffer.data(), buffer.size_bytes()) == (32516 * sizeof(uint32)));
		REQUIRE(buffer == expectedLarge);
		REQUIRE(reader.getPos() == (32516 * sizeof(uint32)));

		uint8 unused = 0;
		REQUIRE(reader.read(unused) == false);

		reader.close();
		REQUIRE(reader.read(buffer.data(), buffer.size()) == 0);
	}
}

TEST_CASE("BinaryReader::read(pos, size)")
{
	std::array<uint8, 255> expectedSmall;
	for (size_t i = 0; i < expectedSmall.size(); ++i)
	{
		expectedSmall[i] = uint8(i + 1);
	}

	SECTION("small")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		std::array<uint8, 255> buffer;
		REQUIRE(reader.read(&buffer[100], 100, 100) == 100);
		REQUIRE(reader.getPos() == 200);
		REQUIRE(reader.read(&buffer[0], 0, 50) == 50);
		REQUIRE(reader.getPos() == 50);
		REQUIRE(reader.read(&buffer[200], 200, 60) == 55);
		REQUIRE(reader.getPos() == 255);
		REQUIRE(reader.read(&buffer[50], 50, 50) == 50);
		REQUIRE(reader.getPos() == 100);
		REQUIRE(buffer == expectedSmall);

		reader.close();
		REQUIRE(reader.read(&buffer[100], 100, 100) == 0);
	}
}

TEST_CASE("BinaryReader::lookahead(size)")
{
	std::array<uint8, 255> expectedSmall;
	for (size_t i = 0; i < expectedSmall.size(); ++i)
	{
		expectedSmall[i] = uint8(i + 1);
	}

	SECTION("small | 255 bytes / read")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		std::array<uint8, 255> buffer;
		REQUIRE(reader.lookahead(buffer) == true);
		REQUIRE(buffer == expectedSmall);
		REQUIRE(reader.getPos() == 0);

		uint8 unused = 0;
		REQUIRE(reader.read(unused) == true);

		reader.close();
		REQUIRE(reader.lookahead(buffer) == false);
	}
}

TEST_CASE("BinaryReader::lookahead(pos, size)")
{
	std::array<uint8, 255> expectedSmall;
	for (size_t i = 0; i < expectedSmall.size(); ++i)
	{
		expectedSmall[i] = uint8(i + 1);
	}

	SECTION("small")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		std::array<uint8, 255> buffer;
		REQUIRE(reader.lookahead(&buffer[100], 100, 100) == 100);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.lookahead(&buffer[0], 0, 50) == 50);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.lookahead(&buffer[200], 200, 60) == 55);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.lookahead(&buffer[50], 50, 50) == 50);
		REQUIRE(reader.getPos() == 0);
		REQUIRE(buffer == expectedSmall);

		reader.close();
		REQUIRE(reader.lookahead(&buffer[100], 100, 100) == 0);
	}
}

TEST_CASE("BinaryReader::getPos()")
{
	SECTION("small")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		
		std::array<uint8, 255> buffer;
		REQUIRE(reader.getPos() == 0);
		REQUIRE(reader.read(&buffer[0], 1) == 1);
		REQUIRE(reader.getPos() == 1);
		REQUIRE(reader.read(&buffer[200], 200, 60) == 55);
		REQUIRE(reader.getPos() == 255);
		REQUIRE(reader.setPos(999) == false);
		REQUIRE(reader.getPos() == 255);
		REQUIRE(reader.lookahead(&buffer[100], 100, 100) == 100);
		REQUIRE(reader.getPos() == 255);
		REQUIRE(reader.setPos(-999) == false);
		REQUIRE(reader.getPos() == 255);
		REQUIRE(reader.setPos(50) == true);
		REQUIRE(reader.getPos() == 50);

		reader.close();
		REQUIRE(reader.getPos() == 0);
	}
}

TEST_CASE("BinaryReader::setPos()")
{
	std::array<uint8, 255> expectedSmall;
	for (size_t i = 0; i < expectedSmall.size(); ++i)
	{
		expectedSmall[i] = uint8(i + 1);
	}

	SECTION("small")
	{
		const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
		BinaryReader reader(path);
		
		uint8 byte = 0;
		REQUIRE(reader.read(byte) == true);
		REQUIRE(byte == 1);
		REQUIRE(reader.setPos(0) == true);
		REQUIRE(reader.read(byte) == true);
		REQUIRE(byte == 1);
		REQUIRE(reader.setPos(254) == true);
		REQUIRE(reader.read(byte) == true);
		REQUIRE(byte == 255);
		REQUIRE(reader.read(byte) == false);
		REQUIRE(reader.setPos(127) == true);
		REQUIRE(reader.read(byte) == true);
		REQUIRE(byte == 128);
		REQUIRE(reader.setPos(254) == true);
		REQUIRE(reader.read(byte) == true);
		REQUIRE(byte == 255);
		REQUIRE(reader.setPos(0) == true);
		REQUIRE(reader.read(byte) == true);
		REQUIRE(byte == 1);

		REQUIRE(reader.setPos(0) == true);
		std::array<uint8, 255> buffer;
		REQUIRE(reader.read(buffer) == true);
		REQUIRE(buffer == expectedSmall);
	}
}

TEST_CASE("BinaryReader::skip()")
{
	std::array<uint8, 255> expectedSmall;
	for (size_t i = 0; i < expectedSmall.size(); ++i)
	{
		expectedSmall[i] = uint8(i + 1);
	}

	const FilePath path = FileSystem::FullPath(U"test/binary/small.bin");
	BinaryReader reader(path);
	std::array<uint8, 255> buffer;

	REQUIRE(reader.skip(100) == 100);
	REQUIRE(reader.getPos() == 100);
	REQUIRE(reader.read(&buffer[100], 100) == 100);
	REQUIRE(reader.getPos() == 200);

	REQUIRE(reader.skip(-200) == 0);
	REQUIRE(reader.getPos() == 0);
	REQUIRE(reader.read(&buffer[0], 50) == 50);
	REQUIRE(reader.getPos() == 50);

	REQUIRE(reader.skip(150) == 200);
	REQUIRE(reader.getPos() == 200);
	REQUIRE(reader.read(&buffer[200], 60) == 55);
	REQUIRE(reader.getPos() == 255);

	REQUIRE(reader.skip(1) == 255);
	REQUIRE(reader.getPos() == 255);

	REQUIRE(reader.skip(-800) == 0);
	REQUIRE(reader.getPos() == 0);
	REQUIRE(reader.read(&buffer[50], 50, 50) == 50);
	REQUIRE(reader.getPos() == 100);
	REQUIRE(buffer == expectedSmall);

	reader.close();
	REQUIRE(reader.skip(100) == 0);
}

# if defined(SIV3D_RUN_BENCHMARK)

TEST_CASE("BinaryReader : benchmark")
{
	Logger.disable();

	BENCHMARK("BinaryReader | 4096 bytes / read")
	{
		BinaryReader reader(U"test/binary/large.bin");
		uint8 buffer[4096];
		size_t bytes = reader.size();
		while (bytes)
		{
			size_t readBytes = Min(bytes, std::size(buffer));
			reader.read(buffer, readBytes);
			bytes -= readBytes;
		}

		return 0;
	};

	BENCHMARK("std::ifstream | 4096 bytes / read")
	{
		std::ifstream reader("test/binary/large.bin", std::ios_base::binary);
		uint8 buffer[4096];
		size_t bytes = FileSystem::FileSize(U"test/binary/large.bin");
		while (bytes)
		{
			size_t readBytes = Min(bytes, std::size(buffer));
			reader.read((char*)buffer, readBytes);
			bytes -= readBytes;
		}

		return 0;
	};

	BENCHMARK("BinaryReader | 128 bytes / read")
	{
		BinaryReader reader(U"test/binary/large.bin");
		uint8 buffer[128];
		size_t bytes = reader.size();
		while (bytes)
		{
			size_t readBytes = Min(bytes, std::size(buffer));
			reader.read(buffer, readBytes);
			bytes -= readBytes;
		}

		return 0;
	};

	BENCHMARK("std::ifstream | 128 bytes / read")
	{
		std::ifstream reader("test/binary/large.bin", std::ios_base::binary);
		uint8 buffer[128];
		size_t bytes = FileSystem::FileSize(U"test/binary/large.bin");
		while (bytes)
		{
			size_t readBytes = Min(bytes, std::size(buffer));
			reader.read((char*)buffer, readBytes);
			bytes -= readBytes;
		}

		return 0;
	};

	BENCHMARK("BinaryReader | 4 bytes / read")
	{
		BinaryReader reader(U"test/binary/large.bin");
		uint8 buffer[4];
		size_t bytes = reader.size();
		while (bytes)
		{
			size_t readBytes = Min(bytes, std::size(buffer));
			reader.read(buffer, readBytes);
			bytes -= readBytes;
		}

		return 0;
	};

	BENCHMARK("std::ifstream | 4 bytes / read")
	{
		std::ifstream reader("test/binary/large.bin", std::ios_base::binary);
		uint8 buffer[4];
		size_t bytes = FileSystem::FileSize(U"test/binary/large.bin");
		while (bytes)
		{
			size_t readBytes = Min(bytes, std::size(buffer));
			reader.read((char*)buffer, readBytes);
			bytes -= readBytes;
		}

		return 0;
	};

	Logger.enable();
}

# endif
