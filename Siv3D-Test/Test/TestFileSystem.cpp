//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "Siv3DTest.hpp"

# if defined(SIV3D_DO_TEST)

# if defined(SIV3D_TARGET_WINDOWS)

	# include <filesystem>
	namespace fs = std::experimental::filesystem;

# elif defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

	# include <boost/filesystem.hpp>
	namespace fs = boost::filesystem;

# endif

using namespace s3d;

TEST(FileSystem, Exists)
{
	EXPECT_EQ(FileSystem::Exists(L""), false);
	EXPECT_EQ(FileSystem::Exists(L" "), false);
	EXPECT_EQ(FileSystem::Exists(L"./"), true);
	EXPECT_EQ(FileSystem::Exists(L"../"), true);
	EXPECT_EQ(FileSystem::Exists(L"exa"), false);
	EXPECT_EQ(FileSystem::Exists(L"exa/"), false);
	EXPECT_EQ(FileSystem::Exists(L"./../"), true);
	EXPECT_EQ(FileSystem::Exists(L"example"), true);
	EXPECT_EQ(FileSystem::Exists(L"example/"), true);
	EXPECT_EQ(FileSystem::Exists(L"./example"), true);
	EXPECT_EQ(FileSystem::Exists(L"./example/"), true);
	EXPECT_EQ(FileSystem::Exists(L"example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::Exists(L"example/siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::Exists(L"example/siv3d-kun.png/"), false);
	EXPECT_EQ(FileSystem::Exists(L"./example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::Exists(L"./example/siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::Exists(L"./example/siv3d-kun.png/"), false);
	EXPECT_EQ(FileSystem::Exists(L"./example/../example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::Exists(L"./example/../example/siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::Exists(L"./example/../example/siv3d-kun.png/"), false);

	EXPECT_EQ(FileSystem::Exists(L""), false);
	EXPECT_EQ(FileSystem::Exists(L" "), false);
	EXPECT_EQ(FileSystem::Exists(L".\\"), true);
	EXPECT_EQ(FileSystem::Exists(L"..\\"), true);
	EXPECT_EQ(FileSystem::Exists(L"exa"), false);
	EXPECT_EQ(FileSystem::Exists(L"exa\\"), false);
	EXPECT_EQ(FileSystem::Exists(L".\\..\\"), true);
	EXPECT_EQ(FileSystem::Exists(L"example"), true);
	EXPECT_EQ(FileSystem::Exists(L"example\\"), true);
	EXPECT_EQ(FileSystem::Exists(L".\\example"), true);
	EXPECT_EQ(FileSystem::Exists(L".\\example\\"), true);
	EXPECT_EQ(FileSystem::Exists(L"example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::Exists(L"example\\siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::Exists(L"example\\siv3d-kun.png\\"), false);
	EXPECT_EQ(FileSystem::Exists(L".\\example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::Exists(L".\\example\\siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::Exists(L".\\example\\siv3d-kun.png\\"), false);
	EXPECT_EQ(FileSystem::Exists(L".\\example\\..\\example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::Exists(L".\\example\\..\\example\\siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::Exists(L".\\example\\..\\example\\siv3d-kun.png\\"), false);
}

TEST(FileSystem, IsDirectory)
{
	EXPECT_EQ(FileSystem::IsDirectory(L""), false);
	EXPECT_EQ(FileSystem::IsDirectory(L" "), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"../"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"exa"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"exa/"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./../"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"example"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"example/"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example/"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"example/siv3d-kun.png"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"example/siv3d-kun.png/"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example/siv3d-kun.png"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example/siv3d-kun.png/"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example/../example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example/../example/siv3d-kun.png"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"./example/../example/siv3d-kun.png/"), false);

	EXPECT_EQ(FileSystem::IsDirectory(L""), false);
	EXPECT_EQ(FileSystem::IsDirectory(L" "), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"..\\"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"exa"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"exa\\"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\..\\"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"example"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"example\\"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example\\"), true);
	EXPECT_EQ(FileSystem::IsDirectory(L"example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"example\\siv3d-kun.png"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L"example\\siv3d-kun.png\\"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example\\siv3d-kun.png"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example\\siv3d-kun.png\\"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example\\..\\example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example\\..\\example\\siv3d-kun.png"), false);
	EXPECT_EQ(FileSystem::IsDirectory(L".\\example\\..\\example\\siv3d-kun.png\\"), false);
}

TEST(FileSystem, IsFile)
{
	EXPECT_EQ(FileSystem::IsFile(L""), false);
	EXPECT_EQ(FileSystem::IsFile(L" "), false);
	EXPECT_EQ(FileSystem::IsFile(L"./"), false);
	EXPECT_EQ(FileSystem::IsFile(L"../"), false);
	EXPECT_EQ(FileSystem::IsFile(L"exa"), false);
	EXPECT_EQ(FileSystem::IsFile(L"exa/"), false);
	EXPECT_EQ(FileSystem::IsFile(L"./../"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example/"), false);
	EXPECT_EQ(FileSystem::IsFile(L"./example"), false);
	EXPECT_EQ(FileSystem::IsFile(L"./example/"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example/siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::IsFile(L"example/siv3d-kun.png/"), false);
	EXPECT_EQ(FileSystem::IsFile(L"./example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsFile(L"./example/siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::IsFile(L"./example/siv3d-kun.png/"), false);
	EXPECT_EQ(FileSystem::IsFile(L"./example/../example/siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsFile(L"./example/../example/siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::IsFile(L"./example/../example/siv3d-kun.png/"), false);

	EXPECT_EQ(FileSystem::IsFile(L""), false);
	EXPECT_EQ(FileSystem::IsFile(L" "), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L"..\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L"exa"), false);
	EXPECT_EQ(FileSystem::IsFile(L"exa\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\..\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\example"), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\example\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsFile(L"example\\siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::IsFile(L"example\\siv3d-kun.png\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\example\\siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::IsFile(L".\\example\\siv3d-kun.png\\"), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\example\\..\\example\\siv3d-kun"), false);
	EXPECT_EQ(FileSystem::IsFile(L".\\example\\..\\example\\siv3d-kun.png"), true);
	EXPECT_EQ(FileSystem::IsFile(L".\\example\\..\\example\\siv3d-kun.png\\"), false);
}

TEST(FileSystem, IsResource)
{

}

TEST(FileSystem, FullPath)
{


}

TEST(FileSystem, Extension)
{

}

TEST(FileSystem, FileName)
{

}

TEST(FileSystem, BaseName)
{

}

TEST(FileSystem, DirectoryContents)
{
	{
		Array<FilePath> paths;

		for (auto path : fs::directory_iterator(fs::path(L"./")))
		{
			paths.push_back(FileSystem::FullPath(path.path().wstring()));
		}

		EXPECT_EQ(FileSystem::DirectoryContents(L"./", false), paths);
	}

	{
		Array<FilePath> paths;

		for (auto path : fs::recursive_directory_iterator(fs::path(L"./")))
		{
			paths.push_back(FileSystem::FullPath(path.path().wstring()));
		}

		EXPECT_EQ(FileSystem::DirectoryContents(L"./", true), paths);
	}
}

# endif
