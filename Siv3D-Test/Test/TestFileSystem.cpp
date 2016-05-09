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

# include <Siv3D.hpp>
# include <gtest/gtest.h>

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
