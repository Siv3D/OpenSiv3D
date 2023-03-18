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

# include <Siv3D/Script.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	using namespace AngelScript;

	static bool FileSystemIsResourcePath(const String& path) noexcept
	{
		return FileSystem::IsResourcePath(path);
	}

	static bool FileSystemExists(const String& path) noexcept
	{
		return FileSystem::Exists(path);
	}

	static bool FileSystemIsDirectory(const String& path) noexcept
	{
		return FileSystem::IsDirectory(path);
	}

	static bool FileSystemIsFile(const String& path) noexcept
	{
		return FileSystem::IsFile(path);
	}

	static bool FileSystemIsResource(const String& path) noexcept
	{
		return FileSystem::IsResource(path);
	}

	static String FileSystemFullPath(const String& path) noexcept
	{
		return FileSystem::FullPath(path);
	}

	static String FileSystemExtension(const String& path) noexcept
	{
		return FileSystem::Extension(path);
	}

	static String FileSystemFileName(const String& path) noexcept
	{
		return FileSystem::FileName(path);
	}

	static String FileSystemBaseName(const String& path) noexcept
	{
		return FileSystem::BaseName(path);
	}

	static String FileSystemParentPath(const String& path, size_t level) noexcept
	{
		return FileSystem::ParentPath(path, level);
	}

	static String FileSystemParentPath2(const String& path, size_t level, String& baseFullPath) noexcept
	{
		return FileSystem::ParentPath(path, level, baseFullPath);
	}

	static String FileSystemVolumePath(const String& path) noexcept
	{
		return FileSystem::VolumePath(path);
	}

	static bool FileSystemIsEmptyDirectory(const String& path) noexcept
	{
		return FileSystem::IsEmptyDirectory(path);
	}

	static int64 FileSystemSize(const String& path) noexcept
	{
		return FileSystem::Size(path);
	}

	static int64 FileSystemFileSize(const String& path) noexcept
	{
		return FileSystem::FileSize(path);
	}




	static const String& FileSystemInitialDirectory() noexcept
	{
		return FileSystem::InitialDirectory();
	}

	static const String& FileSystemModulePath() noexcept
	{
		return FileSystem::ModulePath();
	}

	static String FileSystemCurrentDirectory() noexcept
	{
		return FileSystem::CurrentDirectory();
	}

	static bool FileSystemChangeCurrentDirectory(const String& path) noexcept
	{
		return FileSystem::ChangeCurrentDirectory(path);
	}

	static const String& FileSystemGetFolderPath(int32 specialFolder) noexcept
	{
		return FileSystem::GetFolderPath(ToEnum<SpecialFolder>(static_cast<uint8>(specialFolder)));
	}

	static String FileSystemTemporaryDirectoryPath() noexcept
	{
		return FileSystem::TemporaryDirectoryPath();
	}

	static String FileSystemUniqueFilePath(const String& directory) noexcept
	{
		return FileSystem::UniqueFilePath(directory);
	}

	static String FileSystemRelativePath(const String& path, const String& start) noexcept
	{
		return FileSystem::RelativePath(path, start);
	}

	static bool FileSystemCreateDirectories(const String& path) noexcept
	{
		return FileSystem::CreateDirectories(path);
	}

	static bool FileSystemCreateParentDirectories(const String& path) noexcept
	{
		return FileSystem::CreateParentDirectories(path);
	}

	static bool FileSystemCopy(const String& from, const String& to, int32 copyOption) noexcept
	{
		return FileSystem::Copy(from, to, ToEnum<CopyOption>(static_cast<uint8>(copyOption)));
	}

	//static bool FileSystemRemove(const String& path, bool allowUndo) noexcept
	//{
	//	return FileSystem::Remove(path, AllowUndo{ allowUndo });
	//}

	//static bool FileSystemRemoveContents(const String& path, bool allowUndo) noexcept
	//{
	//	return FileSystem::Remove(path, AllowUndo{ allowUndo });
	//}

	//static bool FileSystemRename(const String& from, const String& to) noexcept
	//{
	//	return FileSystem::Rename(from, to);
	//}


	void RegisterFileSystem(asIScriptEngine* engine)
	{
		[[maybe_unused]] int32 r = 0;

		r = engine->SetDefaultNamespace("FileSystem"); assert(r >= 0);
		{
			r = engine->RegisterGlobalFunction("bool IsResourcePath(const String& in)", asFUNCTION(FileSystemIsResourcePath), asCALL_CDECL); assert(r >= 0);			
			r = engine->RegisterGlobalFunction("bool Exists(const String& in)", asFUNCTION(FileSystemExists), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool IsDirectory(const String& in)", asFUNCTION(FileSystemIsDirectory), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool IsFile(const String& in)", asFUNCTION(FileSystemIsFile), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool IsResource(const String& in)", asFUNCTION(FileSystemIsResource), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String FullPath(const String& in)", asFUNCTION(FileSystemFullPath), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String Extension(const String& in)", asFUNCTION(FileSystemExtension), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String FileName(const String& in)", asFUNCTION(FileSystemFileName), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String BaseName(const String& in)", asFUNCTION(FileSystemBaseName), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String ParentPath(const String& in, size_t level = 0)", asFUNCTION(FileSystemParentPath), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String ParentPath(const String& in, size_t level, String& out baseFullPath)", asFUNCTION(FileSystemParentPath2), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String VolumePath(const String& in)", asFUNCTION(FileSystemVolumePath), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool IsEmptyDirectory(const String& in)", asFUNCTION(FileSystemIsEmptyDirectory), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int64 Size(const String& in)", asFUNCTION(FileSystemSize), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("int64 FileSize(const String& in)", asFUNCTION(FileSystemFileSize), asCALL_CDECL); assert(r >= 0);
		

			r = engine->RegisterGlobalFunction("const String& InitialDirectory()", asFUNCTION(FileSystemInitialDirectory), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("const String& ModulePath()", asFUNCTION(FileSystemModulePath), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String CurrentDirectory()", asFUNCTION(FileSystemCurrentDirectory), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool ChangeCurrentDirectory(const String& in)", asFUNCTION(FileSystemChangeCurrentDirectory), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("const String& GetFolderPath(SpecialFolder)", asFUNCTION(FileSystemGetFolderPath), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String TemporaryDirectoryPath()", asFUNCTION(FileSystemTemporaryDirectoryPath), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String UniqueFilePath(const String& in = TemporaryDirectoryPath())", asFUNCTION(FileSystemUniqueFilePath), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("String RelativePath(const String& in, const String& in = CurrentDirectory())", asFUNCTION(FileSystemRelativePath), asCALL_CDECL); assert(r >= 0);
			
			r = engine->RegisterGlobalFunction("bool CreateDirectories(const String& in)", asFUNCTION(FileSystemCreateDirectories), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool CreateParentDirectories(const String& in)", asFUNCTION(FileSystemCreateParentDirectories), asCALL_CDECL); assert(r >= 0);
			r = engine->RegisterGlobalFunction("bool Copy(const String& in, const String& in, CopyOption = CopyOption::Default)", asFUNCTION(FileSystemCopy), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
