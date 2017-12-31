//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# include <Siv3D/Windows.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace detail
	{
		static BOOL CALLBACK EnumResourceNameCallback(HMODULE, LPCWSTR, LPWSTR lpName, LONG_PTR lParam)
		{
			Array<FilePath>& paths = *(Array<FilePath>*)lParam;

			paths.push_back(Unicode::FromWString(lpName));

			return true;
		}

		static Array<FilePath> GetResourceFilePaths()
		{
			Array<FilePath> paths;

			HMODULE hModule = ::GetModuleHandleW(nullptr);

			::EnumResourceNamesW(hModule, L"FILE", detail::EnumResourceNameCallback, (LONG_PTR)&paths);

			paths.sort();

			return paths;
		}
	}

	const Array<FilePath>& EnumResourceFiles()
	{
		const static Array<FilePath> paths = detail::GetResourceFilePaths();

		return paths;
	}

	FilePath Resource(const FilePath& path)
	{
		if (FileSystem::IsResource(path))
		{
			return path;
		}

		return U'/' + path;
	}
}

# elif defined(SIV3D_TARGET_MACOS)

# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace detail
	{
		static Array<FilePath> GetResourceFilePaths()
		{
			const FilePath resourcePath = FileSystem::ModulePath() + U"/Contents/Resources/";
			
			Array<FilePath> paths = FileSystem::DirectoryContents(resourcePath, true);
		
			paths.remove(resourcePath + U"icon.icns");

			paths.remove_if(FileSystem::IsDirectory);

			paths.sort();

			return paths;
		}
	}

	const Array<FilePath>& EnumResourceFiles()
	{
		const static Array<FilePath> paths = detail::GetResourceFilePaths();

		return paths;
	}

	FilePath Resource(const FilePath& path)
	{
		if (FileSystem::IsResource(path))
		{
			return path;
		}

		const FilePath resourcePath = FileSystem::ModulePath() + U"/Contents/Resources/";

		return resourcePath + path;
	}
}

# elif defined (SIV3D_TARGET_LINUX)

# include <Siv3D/Array.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FileSystem.hpp>

namespace s3d
{
	namespace detail
	{
		static Array<FilePath> GetResourceFilePaths()
		{
			const FilePath resourcePath = FileSystem::ModulePath() + U"/resources/";

			Array<FilePath> paths = FileSystem::DirectoryContents(resourcePath, true);

			paths.remove_if(FileSystem::IsDirectory);

			paths.sort();

			return paths;
		}
	}

	const Array<FilePath>& EnumResourceFiles()
	{
		static Array<FilePath> paths = detail::GetResourceFilePaths();

		return paths;
	}

	FilePath Resource(const FilePath& path)
	{
		if (FileSystem::IsResource(path))
		{
			return path;
		}

		const FilePath resourcePath = FileSystem::ModulePath() + U"/resources/";

		return resourcePath + path;
	}
}

# endif
