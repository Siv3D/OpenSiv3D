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

TEST_CASE("FileSystem")
{
	Console << U"FileSystem:";
	Console << (U"Volume\t: {}"_fmt(FileSystem::VolumePath(U"./")));
	Console << (U"Initial\t: {}"_fmt(FileSystem::InitialDirectory()));
	Console << (U"Module\t: {}"_fmt(FileSystem::ModulePath()));
	Console << (U"Current\t: {}"_fmt(FileSystem::CurrentDirectory()));
	Console << (U"Full  \t: {}"_fmt(FileSystem::FullPath(U"./")));
	{
		const auto path = FileSystem::NativePath(U"./");
	# if SIV3D_PLATFORM(WINDOWS)
		Console << (U"Native\t: {}"_fmt(Unicode::FromWstring(path)));
	# else
		Console << (U"Native\t: {}"_fmt(Unicode::Widen(path)));
	# endif
	}
	Console << (U"Parent\t: {}"_fmt(FileSystem::ParentPath(U"./")));
	Console << (U"Parent\t: {}"_fmt(FileSystem::ParentPath(U"./", 1)));
	Console << (U"Parent\t: {}"_fmt(FileSystem::ParentPath(U"./", 2)));

	const FilePath modulePath = FileSystem::ModulePath();
	REQUIRE(FileSystem::Exists(modulePath) == true);
	
# if SIV3D_PLATFORM(MACOS)
	REQUIRE(FileSystem::IsFile(modulePath) == false);
	REQUIRE(FileSystem::IsDirectory(modulePath) == true);
# else
	REQUIRE(FileSystem::IsFile(modulePath) == true);
	REQUIRE(FileSystem::IsDirectory(modulePath) == false);
# endif
	
	REQUIRE(FileSystem::IsResource(modulePath) == false);

	Console << (U"Size\t: {}"_fmt(FileSystem::Size(modulePath)));
	Console << (U"F Size\t: {}"_fmt(FileSystem::FileSize(modulePath)));
	Console << (U"Size\t: {}"_fmt(FileSystem::Size(U"./")));
	Console << (U"Creatio\t: {}"_fmt(FileSystem::CreationTime(modulePath)));
	Console << (U"Write\t: {}"_fmt(FileSystem::WriteTime(modulePath)));
	Console << (U"Access\t: {}"_fmt(FileSystem::AccessTime(modulePath)));
	Console << (U"DirCon\t: {}"_fmt(FileSystem::DirectoryContents(U"./")));


	Console << (U"Desktop\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Desktop)));
	Console << (U"Documents\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Documents)));
	Console << (U"LocalAppData\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::LocalAppData)));
	Console << (U"Pictures\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Pictures)));
	Console << (U"Music\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Music)));
	Console << (U"Videos\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Videos)));
	Console << (U"Caches\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Caches)));
	Console << (U"Movies\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::Movies)));
	Console << (U"SystemFonts\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::SystemFonts)));
	Console << (U"LocalFonts\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::LocalFonts)));
	Console << (U"UserFonts\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::UserFonts)));
	Console << (U"UserProfile\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::UserProfile)));
	Console << (U"ProgramFiles\t: {}"_fmt(FileSystem::GetFolderPath(SpecialFolder::ProgramFiles)));

}

TEST_CASE("FileSystem::ChangeCurrentDirectory()")
{
	const FilePath current = FileSystem::CurrentDirectory();
	const FilePath target = FileSystem::CurrentDirectory() + U"test/";
	REQUIRE(FileSystem::ChangeCurrentDirectory(target) == true);
	REQUIRE(FileSystem::CurrentDirectory() == target);
	REQUIRE(FileSystem::ChangeCurrentDirectory(current) == true);
}

TEST_CASE("FileSystem::CreateDirectories()")
{
	const FilePath target = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/a1/b1/c1/";
	REQUIRE(FileSystem::Exists(target) == false);
	REQUIRE(FileSystem::CreateDirectories(target) == true);
	REQUIRE(FileSystem::Exists(target) == true);
}

TEST_CASE("FileSystem::CreateParentDirectories()")
{
	SECTION("by file")
	{
		const FilePath target = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/a2/b2/c2/";
		const FilePath targetFile = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/a2/b2/c2/test.txt";
		REQUIRE(FileSystem::Exists(target) == false);
		REQUIRE(FileSystem::CreateParentDirectories(targetFile) == true);
		REQUIRE(FileSystem::Exists(target) == true);
	}

	SECTION("by directory")
	{
		const FilePath target = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/a3/b3/";
		const FilePath targetFile = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/a3/b3/c3/";
		REQUIRE(FileSystem::Exists(target) == false);
		REQUIRE(FileSystem::CreateParentDirectories(targetFile) == true);
		REQUIRE(FileSystem::Exists(target) == true);
	}
}

TEST_CASE("FileSystem::Copy()")
{
	SECTION("file")
	{
		const FilePath targetFile = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/empty.txt";

		REQUIRE(FileSystem::Exists(targetFile) == false);
		REQUIRE(FileSystem::Copy(U"test/text/empty.txt", targetFile, CopyOption::Default) == true);
		REQUIRE(FileSystem::Exists(targetFile) == true);
		REQUIRE(FileSystem::Remove(targetFile) == true);
	}

	SECTION("directory")
	{
		const FilePath targetDirectory = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/text/";

		REQUIRE(FileSystem::Exists(targetDirectory) == false);
		REQUIRE(FileSystem::Copy(U"test/text/", targetDirectory, CopyOption::Default) == true);
		REQUIRE(FileSystem::Exists(targetDirectory) == true);
		REQUIRE(FileSystem::Size(U"test/text/") == FileSystem::Size(targetDirectory));
		REQUIRE(FileSystem::Remove(targetDirectory) == true);
	}
}

TEST_CASE("FileSystem::Remove()")
{
	SECTION("file")
	{
		const FilePath targetFile = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/remove/empty.txt";

		REQUIRE(FileSystem::Exists(targetFile) == false);
		REQUIRE(FileSystem::Copy(U"test/text/empty.txt", targetFile, CopyOption::Default) == true);
		REQUIRE(FileSystem::Exists(targetFile) == true);
		REQUIRE(FileSystem::Remove(targetFile) == true);
		REQUIRE(FileSystem::Exists(targetFile) == false);
	}

	SECTION("directory")
	{
		const FilePath targetDirectory = FileSystem::CurrentDirectory() + U"test/runtime/filesystem/remove/text/";

		REQUIRE(FileSystem::Exists(targetDirectory) == false);
		REQUIRE(FileSystem::Copy(U"test/text/", targetDirectory, CopyOption::Default) == true);
		REQUIRE(FileSystem::Exists(targetDirectory) == true);
		REQUIRE(FileSystem::Size(U"test/text/") == FileSystem::Size(targetDirectory));
		REQUIRE(FileSystem::Remove(targetDirectory) == true);
		REQUIRE(FileSystem::Exists(targetDirectory) == false);
	}
}