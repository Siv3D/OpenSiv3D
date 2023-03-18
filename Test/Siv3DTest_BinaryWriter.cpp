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

TEST_CASE("BinaryWriter")
{
	SECTION("empty")
	{
		BinaryWriter writer;
		REQUIRE(writer.isOpen() == false);
		REQUIRE(!writer == true);
		REQUIRE(static_cast<bool>(writer) == false);
		REQUIRE(writer.size() == 0);
		REQUIRE(writer.getPos() == 0);
		REQUIRE(writer.path() == U"");
	}

// Siv3D TODO: Excluded Test Case
# if !SIV3D_PLATFORM(WEB)

	SECTION("invalid file name 1")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/t/");

		BinaryWriter writer(path);
		REQUIRE(writer.isOpen() == false);
		REQUIRE(!writer == true);
		REQUIRE(static_cast<bool>(writer) == false);
		REQUIRE(writer.size() == 0);
		REQUIRE(writer.getPos() == 0);
		REQUIRE(writer.path() == U"");
	}

# endif

# if SIV3D_PLATFORM(WINDOWS)
	
	SECTION("invalid file name 2")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/?.bin");

		BinaryWriter writer(path);
		REQUIRE(writer.isOpen() == false);
		REQUIRE(!writer == true);
		REQUIRE(static_cast<bool>(writer) == false);
		REQUIRE(writer.size() == 0);
		REQUIRE(writer.getPos() == 0);
		REQUIRE(writer.path() == U"");
	}
	
# endif

	SECTION("new directory")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/a1/new.bin");

		BinaryWriter writer(path);
		REQUIRE(writer.isOpen() == true);
		REQUIRE(!writer == false);
		REQUIRE(static_cast<bool>(writer) == true);
		REQUIRE(writer.size() == 0);
		REQUIRE(writer.getPos() == 0);
		REQUIRE(writer.path() == path);
	}
}

TEST_CASE("BinaryWriter::write()")
{
	const Array<uint32> expectedSmall = []
	{
		Array<uint32> buffer(255);

		for (size_t i = 0; i < buffer.size(); ++i)
		{
			buffer[i] = uint32(i + 1);
		}

		return buffer;
	}();

	SECTION("1")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/1.bin");

		BinaryWriter writer(path);
		for (uint32 i : Range(1, 255))
		{
			writer.write(i);
		}
		writer.close();

		BinaryReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.size() == (255 * sizeof(uint32)));
		REQUIRE(reader.path() == path);
		Array<uint32> buffer(reader.size() / sizeof(uint32));
		reader.read(buffer.data(), buffer.size_bytes());
		REQUIRE(buffer == expectedSmall);
	}

	SECTION("2")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/2.bin");

		{
			BinaryWriter writer(path);
			writer.write(expectedSmall.data(), expectedSmall.size_bytes());
		}

		BinaryReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.size() == (255 * sizeof(uint32)));
		REQUIRE(reader.path() == path);
		Array<uint32> buffer(reader.size() / sizeof(uint32));
		reader.read(buffer.data(), buffer.size_bytes());
		REQUIRE(buffer == expectedSmall);
	}
}

TEST_CASE("BinaryWriter::setPos()")
{
	const Array<uint32> expectedSmall = []
	{
		Array<uint32> buffer(255);

		for (size_t i = 0; i < buffer.size(); ++i)
		{
			buffer[i] = uint32(i + 1);
		}

		return buffer;
	}();

	SECTION("1")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/s1.bin");

		BinaryWriter writer(path);
		for ([[maybe_unused]] uint32 i : Range(1, 255))
		{
			writer.write(uint32(0));
		}
		REQUIRE(writer.getPos() == (255 * sizeof(uint32)));
		REQUIRE(writer.size() == (255 * sizeof(uint32)));

		REQUIRE(writer.setPos(0) == true);
		REQUIRE(writer.getPos() == 0);
		REQUIRE(writer.size() == (255 * sizeof(uint32)));

		for (uint32 i : Range(1, 255))
		{
			writer.write(uint32(i));
		}
		REQUIRE(writer.getPos() == (255 * sizeof(uint32)));
		REQUIRE(writer.size() == (255 * sizeof(uint32)));

		writer.close();

		BinaryReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.size() == (255 * sizeof(uint32)));
		REQUIRE(reader.path() == path);
		Array<uint32> buffer(reader.size() / sizeof(uint32));
		reader.read(buffer.data(), buffer.size_bytes());
		REQUIRE(buffer == expectedSmall);
	}
}

TEST_CASE("BinaryWriter::seekToEnd()")
{
	const Array<uint32> expectedSmall = []
	{
		Array<uint32> buffer(255);

		for (size_t i = 0; i < buffer.size(); ++i)
		{
			buffer[i] = uint32(i + 1);
		}

		return buffer;
	}();

	SECTION("1")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/e1.bin");

		BinaryWriter writer(path);
		for (uint32 i : Range(1, 100))
		{
			writer.write(i);
		}
		REQUIRE(writer.getPos() == (100 * sizeof(uint32)));
		REQUIRE(writer.size() == (100 * sizeof(uint32)));

		REQUIRE(writer.setPos(0) == true);
		REQUIRE(writer.getPos() == 0);
		REQUIRE(writer.size() == (100 * sizeof(uint32)));

		REQUIRE(writer.seekToEnd() == (100 * sizeof(uint32)));
		REQUIRE(writer.getPos() == (100 * sizeof(uint32)));
		REQUIRE(writer.size() == (100 * sizeof(uint32)));

		for (uint32 i : Range(101, 255))
		{
			writer.write(i);
		}
		REQUIRE(writer.getPos() == (255 * sizeof(uint32)));
		REQUIRE(writer.size() == (255 * sizeof(uint32)));

		writer.close();

		BinaryReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.size() == (255 * sizeof(uint32)));
		REQUIRE(reader.path() == path);
		Array<uint32> buffer(reader.size() / sizeof(uint32));
		reader.read(buffer.data(), buffer.size_bytes());
		REQUIRE(buffer == expectedSmall);
	}
}

TEST_CASE("BinaryWriter::clear()")
{
	const Array<uint32> expectedSmall = []
	{
		Array<uint32> buffer(255);

		for (size_t i = 0; i < buffer.size(); ++i)
		{
			buffer[i] = uint32(i + 1);
		}

		return buffer;
	}();

	SECTION("1")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/c1.bin");

		BinaryWriter writer(path);
		for (uint32 i : Range(1, 255))
		{
			writer.write(i);
		}
		REQUIRE(writer.getPos() == (255 * sizeof(uint32)));
		REQUIRE(writer.size() == (255 * sizeof(uint32)));
		writer.clear();
		writer.close();

		REQUIRE(FileSystem::Exists(path));
		REQUIRE(FileSystem::FileSize(path) == 0);
	}

	SECTION("2")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/c2.bin");

		BinaryWriter writer(path);
		for ([[maybe_unused]] uint32 i : Range(1, 255))
		{
			writer.write(uint32(0));
		}
		REQUIRE(writer.getPos() == (255 * sizeof(uint32)));
		REQUIRE(writer.size() == (255 * sizeof(uint32)));

		writer.clear();

		REQUIRE(writer.getPos() == 0);
		REQUIRE(writer.size() == 0);

		for (uint32 i : Range(1, 255))
		{
			writer.write(uint32(i));
		}
		REQUIRE(writer.getPos() == (255 * sizeof(uint32)));
		REQUIRE(writer.size() == (255 * sizeof(uint32)));

		writer.close();

		BinaryReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.size() == (255 * sizeof(uint32)));
		REQUIRE(reader.path() == path);
		Array<uint32> buffer(reader.size() / sizeof(uint32));
		reader.read(buffer.data(), buffer.size_bytes());
		REQUIRE(buffer == expectedSmall);
	}
}

TEST_CASE("BinaryWriter::flush()")
{
	const Array<uint32> expectedSmall = []
	{
		Array<uint32> buffer(255);

		for (size_t i = 0; i < buffer.size(); ++i)
		{
			buffer[i] = uint32(i + 1);
		}

		return buffer;
	}();

	SECTION("1")
	{
		const FilePath path = FileSystem::FullPath(U"test/runtime/binarywriter/f1.bin");

		BinaryWriter writer(path);
		for (uint32 i : Range(1, 255))
		{
			writer.write(i);
			writer.flush();
		}
		writer.close();

		BinaryReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.size() == (255 * sizeof(uint32)));
		REQUIRE(reader.path() == path);
		Array<uint32> buffer(reader.size() / sizeof(uint32));
		reader.read(buffer.data(), buffer.size_bytes());
		REQUIRE(buffer == expectedSmall);
	}
}

# if defined(SIV3D_RUN_BENCHMARK)

TEST_CASE("BinaryWriter : benchmark")
{
	Logger.disable();

	BENCHMARK("BinaryWriter | 4 bytes * 16384")
	{
		BinaryWriter writer(U"test/runtime/binarywriter/benckmark/1.bin");

		for (uint32 i = 0; i < 16384; ++i)
		{
			writer.write(i);
		}

		return 0;
	};

	BENCHMARK("std::ofstream | 4 bytes * 16384")
	{
		std::ofstream writer("test/runtime/binarywriter/benckmark/2.bin", std::ios_base::binary);

		for (uint32 i = 0; i < 16384; ++i)
		{
			writer.write((const char*)&i, sizeof(uint32));
		}

		return 0;
	};

	Array<uint32> data(16384);
	std::iota(data.begin(), data.end(), 0);

	BENCHMARK("BinaryWriter | 64 kB * 16")
	{
		BinaryWriter writer(U"test/runtime/binarywriter/benckmark/3.bin");

		for (uint32 i = 0; i < 16; ++i)
		{
			writer.write(data.data(), data.size_bytes());
		}

		return 0;
	};

	BENCHMARK("std::ofstream | 64 kB * 16")
	{
		std::ofstream writer("test/runtime/binarywriter/benckmark/4.bin", std::ios_base::binary);

		for (uint32 i = 0; i < 16; ++i)
		{
			writer.write((const char*)data.data(), data.size_bytes());
		}

		return 0;
	};

	Logger.enable();
}

# endif
